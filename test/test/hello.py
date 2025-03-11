#!/usr/bin/python3
from flask import Flask
from flask import render_template

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('abc.html')

@app.route('/user/<username>')
def username(username):
    return 'i am ' + 'AAA'
    
@app.route('/age/<int:age>')
def userage(age):
    return 'i am ' + str(20) + ' years old'

if __name__ == '__main__':
    app.debug = True
    app.run()
