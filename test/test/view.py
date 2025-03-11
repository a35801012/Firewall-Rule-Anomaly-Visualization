#!/usr/bin/python3
from flask import Flask, render_template
app = Flask(__name__)

@app.route('/')  
def test_index():  
    return render_template('login.html')  
  
  
@app.route('/login')  
def login():  
    return 'Here is Login'  
  
  
@app.route('/logout')  
def logout():  
    return 'Here is Logout'  
  
  
@app.route('/userinfo')  
def userinfo():  
    return 'Here is UserINFO'

if __name__ == '__main__':
    app.debug = True
    app.run()
