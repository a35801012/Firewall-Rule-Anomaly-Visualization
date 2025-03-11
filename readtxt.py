import os

# the input file
fin = open("anomaly.txt", "rt")
# the output file which stores result
fout = open("f2.txt", "wt")
# iteration for each line in the input file

for line in fin:
	# replacing the string and write to output file
	
	fout.write(line.replace('yellow', '#fb9a99'))
	
#closing the input and output files

fin = open("f2.txt", "rt")
# the output file which stores result
fout = open("f3.txt", "wt")
# iteration for each line in the input file

for line in fin:
	# replacing the string and write to output file
	
	fout.write(line.replace('lightskyblue', '#a6cee3'))
	
fin = open("f3.txt", "rt")
# the output file which stores result
fout = open("f4.txt", "wt")
# iteration for each line in the input file

for line in fin:
	# replacing the string and write to output file
	
	fout.write(line.replace('/16', ',255.255.0.0'))

fin = open("f4.txt", "rt")
# the output file which stores result
fout = open("jsdata.txt", "wt")
# iteration for each line in the input file

for line in fin:
	# replacing the string and write to output file
	
	fout.write(line.replace('/0', ',0.0.0.0'))
fin.close()
fout.close()

fileTest = r"C:\Users\1234\Desktop\f2.txt"
os.remove(fileTest)
fileTest = r"C:\Users\1234\Desktop\f3.txt"
os.remove(fileTest)
fileTest = r"C:\Users\1234\Desktop\f4.txt"
os.remove(fileTest)

