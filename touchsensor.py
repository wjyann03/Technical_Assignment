from flask import Flask, request

app = Flask(__name__)

@app.route('/sensor/data', methods=['POST'])
def post():
    touch = request.form.get("touch")
    print(f"Received touch: {touch}")
    if touch == "detected":
        return 'Sensor sentuh mendeteksi sentuhan', 200
    else:
        return 'Data tidak valid', 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
