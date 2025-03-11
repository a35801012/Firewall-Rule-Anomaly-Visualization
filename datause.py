import sys
import csv
import socket
import struct
import pandas as pd


def increment_ip_addr(ip_addr): #split IP address
    ip_arr = ip_addr.split('.')
    return ip_arr

def cidr_to_netmask(cidr):
    network, net_bits = cidr.split('/')
    host_bits = 32 - int(net_bits)
    netmask = socket.inet_ntoa(struct.pack('!I', (1 << 32) - (1 << host_bits)))
    return network, netmask

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

    return out_addr


with open('aly.txt', 'r') as f:
    content = f.readlines()
    with open('Unprocesseddata.csv', 'w+',  newline = '') as csvFile:
        csvWriter = csv.writer(csvFile, delimiter = ' ')
        for elem in content:
            csvWriter.writerow([elem.strip()])

header_list = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S"]
df = pd.read_csv('Unprocesseddata.csv', names=header_list)


df['F']=df['F'].str.replace(r'/.*', '')
df['G']=df['G'].str.replace(r'/.*', '')
df['J']=df['J'].str.replace(r'/.*', '')
df['L']=df['L'].str.replace(r'/.*', '')
df['M']=df['M'].str.replace(r'/.*', '')
df['P']=df['P'].str.replace(r'/.*', '')


df_H = df.H.to_list()
times = len(df_H)
for i in range(0, times, 1):
    df_H[i] = cidr_to_netmask(df_H[i])
    df['H'] = end_point(df_H[i][0],df_H[i][1])

df_I = df.I.to_list()
times = len(df_I)
for i in range(0, times, 1):
    df_I[i] = cidr_to_netmask(df_I[i])
    df['I'] = end_point(df_I[i][0],df_I[i][1])

df_K = df.K.to_list()
times = len(df_K)
for i in range(0, times, 1):
    df_K[i] = cidr_to_netmask(df_K[i])
    df['K'] = end_point(df_K[i][0],df_K[i][1])

df_N = df.N.to_list()
times = len(df_N)
for i in range(0, times, 1):
    df_N[i] = cidr_to_netmask(df_N[i])
    df['N'] = end_point(df_N[i][0],df_N[i][1])

df_O = df.O.to_list()
times = len(df_O)

for i in range(0, times, 1):
    df_O[i] = cidr_to_netmask(df_O[i])
    df['O'] = end_point(df_O[i][0],df_O[i][1])


df_Q = df.Q.to_list()
times = len(df_Q)
for i in range(0, times, 1):
    df_Q[i] = cidr_to_netmask(df_Q[i])
    df['Q'] = end_point(df_Q[i][0],df_Q[i][1])
    
df.to_csv("jsdata.csv")

df = pd.read_csv('jsdata.csv')
first_column = df.columns[0]
df = df.drop([first_column], axis=1)
df.to_csv('jsdata.csv', header=False ,index=False)


print(df)
