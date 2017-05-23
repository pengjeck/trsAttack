from flask import Flask
from flask import request, Response
from flask_cors import CORS, cross_origin
from flask import jsonify
import time
import json

app = Flask(__name__)
CORS(app)


@app.route('/upload', methods=['GET', 'POST', 'OPTIONS'])
def upload_file():
    print("get request")
    if request.method == 'POST':
        print(request.files)
        time.sleep(1)
        return 'right'
    else:
        print('error')
        return "error"


@app.route('/upload/query', methods=['GET', 'POST'])
def upload_query():
    print(request.args)
    filename = request.args['filename']
    begTraceIndex = int(request.args['begTraceIndex'])
    endTraceIndex = int(request.args['endTraceIndex'])
    begSampleIndex = int(request.args['begSampleIndex'])
    endSampleIndex = int(request.args['endSampleIndex'])
    result = {
        'traces': [
            {
                'cryData': "out",
                'samples': [3, 4, 5, 2, 1, 5, 9, 0],
                'traceTitle': "title" + str(begTraceIndex),
                'traceIndex': begTraceIndex
            },
            {
                'cryData': "out",
                'samples': [2, 3, 5, 6, 7, 2, 1, 3],
                'traceTitle': "title" + str(begTraceIndex + 1),
                'traceIndex': begTraceIndex + 1
            }
        ]
    }
    print(json.dumps(result))
    return json.dumps(result)


@app.route('/')
def hello_world():
    return 'Hello World!'

if __name__ == '__main__':
    app.run()
