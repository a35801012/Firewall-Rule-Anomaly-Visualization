#...上略...#
@app.route('/test')  
def test_index():  
    return render_template('base.html')  
  
  
@app.route('/login')  
def login():  
    return 'Here is Login'  
  
  
@app.route('/logout')  
def logout():  
    return 'Here is Logout'  
  
  
@app.route('/userinfo')  
def userinfo():  
    return 'Here is UserINFO'

