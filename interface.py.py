import cffi
import sys
import traceback

ffi = cffi.FFI()
ffi.cdef(file('interface.h').read())

# Hold references to objects to prevent garbage collection.
noGCDict = {}

# Add two numbers.
# This function was copied from the PyPy example.
@ffi.callback("double (double, double)")
def add_numbers(x, y):
    return x + y

# Convert input buffer to repr(buffer).
@ffi.callback("char *(char*, int)")
def dump_buffer(buffer, buffer_len):
    try:
        # First attempt to access data in buffer.
        # Using the ffi/lib objects:
        # http://cffi.readthedocs.org/en/latest/using.html#using-the-ffi-lib-objects
        # One char at time, Looks inefficient.
        #data = ''.join([buffer[i] for i in xrange(buffer_len)])

        # Second attempt.
        # FFI Interface:
        # http://cffi.readthedocs.org/en/latest/using.html#ffi-interface
        # Works but doc says "str() gives inconsistent results".
        #data = str( ffi.buffer(buffer, buffer_len) )

        # Convert C buffer to Python str.
        # Doc says [:] is recommended instead of str().
        data = ffi.buffer(buffer, buffer_len)[:]

        # The goal is to return repr(data)
        # but it has to be converted to a C buffer.
        result = ffi.new('char []', repr(data))

        # Save reference to data so it's not freed until released by C program.
        noGCDict[ffi.addressof(result)] = result

        return result
    except:
        print >>sys.stderr, traceback.format_exc()
        return ffi.NULL

# Release object so that Python can reclaim the memory.
@ffi.callback("int (char*)")
def release_object(ptr):
    try:
        del noGCDict[ptr]
        return 0
    except:
        print >>sys.stderr, traceback.format_exc()
        return 1

def fill_api(ptr):
    global api
    api = ffi.cast("struct API*", ptr)

    api.add_numbers = add_numbers
    api.dump_buffer = dump_buffer
    api.release_object = release_object
