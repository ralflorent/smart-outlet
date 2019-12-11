from flask import Flask, request, jsonify
from flask_mysqldb import MySQL


app = Flask(__name__)

app.config["MYSQL_HOST"] = "localhost"
app.config["MYSQL_USER"] = "root"
app.config["MYSQL_PASSWORD"] = "1234"
app.config["MYSQL_DB"] = "smart_outlet"

mysql = MySQL(app)


# GET request to check the outlets status 
@app.route('/api/outlet/status')
def check_outlet_status():
    response = {"data": []}
    cur = mysql.connection.cursor()
    cur.execute("SELECT * from connections WHERE outlet = 1 ORDER BY updatedOn DESC")
    data_outlet_1 = cur.fetchone()
    query_dict = {
        "outlet": data_outlet_1[1],
        "state": data_outlet_1[2],
        "updatedOn": data_outlet_1[3]
        }
    response["data"].append(query_dict)
    cur.execute("SELECT * from connections WHERE outlet = 2 ORDER BY updatedOn DESC")
    data_outlet_2 = cur.fetchone()
    query_dict = {
        "outlet": data_outlet_2[1],
        "state": data_outlet_2[2],
        "updatedOn": data_outlet_2[3]
    }
    response["data"].append(query_dict)
    cur.close()
    return (jsonify(response))

# GET request to check the outlets status 
@app.route('/api/outlet/statusino')
def check_outlet_statusino():
    response = {"data": []}
    cur = mysql.connection.cursor()
    cur.execute("SELECT * from connections WHERE outlet = 1 ORDER BY updatedOn DESC")
    data_outlet_1 = cur.fetchone()
    query_dict = {
        "outlet": data_outlet_1[1],
        "state": data_outlet_1[2]
        }
    response["data"].append(query_dict)
    cur.execute("SELECT * from connections WHERE outlet = 2 ORDER BY updatedOn DESC")
    data_outlet_2 = cur.fetchone()
    query_dict = {
        "outlet": data_outlet_2[1],
        "state": data_outlet_2[2]
    }
    response["data"].append(query_dict)
    cur.close()
    return (jsonify(response))

# POST request to update the oulets status
@app.route('/api/outlet/update', methods=['POST'])
def update_outlet_request():
    data = request.json # returns dictionary
    outlet = int(data["outlet"])
    state = int(data["state"])
    cur = mysql.connection.cursor()
    cur.execute("INSERT INTO connections(outlet, state, updatedOn) VALUES (%s, %s, NOW())", (outlet, state))
    mysql.connection.commit()
    cur.execute("SELECT * from connections WHERE outlet = {} ORDER BY updatedOn DESC".format(outlet))
    data = cur.fetchone()
    # convert tuple response to dictionary
    response = {key[0]: value for key, value in zip(cur.description, data)}
    cur.close()
    return(jsonify(response))


# GET request to the historical data 
@app.route('/api/outlet/history')
def get_historical_data():
    response = {"data": []}
    cur = mysql.connection.cursor()
    cur.execute("SELECT * from connections")
    data = cur.fetchall()
    cur.close()
    # convert results to dictionary
    for result in data:
        query_result = {key[0]: value for key, value in zip(cur.description, result)}
        response["data"].append(query_result)
    return(jsonify(response))