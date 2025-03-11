#!/usr/bin/python3
import subprocess
import time
import json
import re
from flask import Flask, request, render_template
app = Flask(__name__)
# print(RX)
# print(RY)
# print(col)

@app.route("/")
def index():
	return render_template('index.html')

@app.route("/submit", methods=['POST'])
def submit():
	if request.method == 'POST':
		with open("getip.txt",mode="w") as file:	
			data=file.write(request.values['ip']+':'+request.values['port']+':')
			file.close()
		subprocess.call("./client")
		fff = open(r'ifcon.txt')
		ifcon = fff.read(1)
	
	if ifcon=='0':	
		addr = [request.values['ip'],request.values['port']]
		fop = open(r'anomaly.txt')
		RX=[]
		RY=[]
		col=[]
		anom=[]
		xsip=[]
		xdip=[]
		ysip=[]        
		ydip=[]
		xpro=[]
		ypro=[]
		# S=[]	S.append(1)
		for line in fop:
			a=(re.split(',|\n',line)[0])
			b=(re.split(',|\n',line)[1])
			c=(re.split(',|\n',line)[2])
			d=(re.split(',|\n',line)[3])
			e=(re.split(',|\n',line)[4])
			f=(re.split(',|\n',line)[5])
			g=(re.split(',|\n',line)[6])
			h=(re.split(',|\n',line)[7])
			i=(re.split(',|\n',line)[8])
			j=(re.split(',|\n',line)[9])
			RX.append(a)
			RY.append(b)
			col.append(c)
			anom.append(d)
			xsip.append(e)
			xdip.append(f)
			ysip.append(g)
			ydip.append(h)
			xpro.append(i)
			ypro.append(j)		   
				# data=['R1&R2','R1&R3','R1&R3']
				# col=['red','yellow','blue']
			leng=len(RX)
			subprocess.Popen("datause.py", shell=True)
			a1=render_template('tset2.html')     
	elif ifcon=='1':
		a1=render_template('indexerr.html')
	else:
		a1=render_template('err.html')
	return a1
if __name__ == '__main__':
	app.run(host="127.0.0.1", port=80, debug=True)
