# This file create a Flask allowed-HTTP server to get data from ESP8266 and send to HTTPS server. 
# If your server accept HTTP, you can ignore this

from flask import Flask, request, jsonify
import requests

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    temperature = request.form.get('temperature')
    humidity = request.form.get('humidity')
    
    if temperature is None or humidity is None:
        return jsonify({'error': 'Temperature and humidity are required.'}), 400

    url = 'https://bfb-pbl7.xyz/weather'
    json_data = {'temp': temperature, 'humidity': humidity}

    try:
        response = requests.post(url, json=json_data)
        response.raise_for_status()  # Raises an HTTPError for bad responses
        return jsonify(response.json()), response.status_code
    except requests.exceptions.RequestException as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
