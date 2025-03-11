import sys
import split_ip_address


def end_point(input_addr,input_submask):

    in_addr = increment_ip_addr(input_addr) #input IP address and split it
    in_mask = increment_ip_addr(input_submask) #input submask and split it
    solution = ['0', '0', '0', '0'] #calculate the domain using the IP address and submask 
    count = 0 #count the number of zeros  
  
    for i in range(0, 4, 1):
        binary_submask = format(int(in_mask[i]), 'b').zfill(8)
        # format():integer string convert to binary string ; zfill(n):return a string of length n
        for n in range(0, 8, 1):
            if binary_submask[n] == '0': #if character=0,count++
                count = count + 1
        
        solution[i] = str((int(in_addr[i])) & (int(in_mask[i]))) #IP address and submask do and

        if i==3:
            solution[3] = str(int(solution[3]) + (2**count)-2) 
            if int(solution[3]) >= 255:
                solution[3] = '254'
        else:
            solution[i] = str(int(solution[i]) + (2**count)-1)
            if int(solution[i]) > 255:
                solution[i] = '255'
        '''
        solution[i]:the first IP address can be used
        IP address overflow handling 
        '''

    out_addr= '.'.join(solution) #output border IP address

    return out_addr, count
