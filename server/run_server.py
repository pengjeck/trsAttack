# --coding: utf-8--
# BY pj
# Date: 17-5-27
import subprocess

from flask import Flask, request, jsonify

app = Flask(__name__)


@app.route("/preProcess/alignment/staticAlignment", methods=['POST'])
def pre_process_alignment_static():
    argv_1 = request.get_json(force=True)
    p = subprocess.run(['bin/runStaticAlignment', argv_1], stdout=subprocess.PIPE)
    return jsonify(p.stdout.decode())


@app.route("/preProcess/alignment/FFT", methods=['POST'])
def pre_process_alignment_fft():
    argv_1 = request.get_json(force=True)
    p = subprocess.run(['bin/runFFT', argv_1], stdout=subprocess.PIPE)
    if p.returncode != 0:
        print(p.stdout.decode())
    return jsonify(p.stdout.decode())


@app.route("/preProcess/alignment/DTW", methods=['POST'])
def pre_process_alignment_dtw():
    argv_1 = request.get_json(force=True)
    p = subprocess.run(['bin/runDTW', argv_1], stdout=subprocess.PIPE)
    if p.returncode != 0:
        print(p.stdout.decode())
    return jsonify(p.stdout.decode())


@app.route("/preProcess/alignment/POC", methods=['POST'])
def pre_process_alignment_poc():
    argv_1 = request.get_json(force=True)
    p = subprocess.run(['bin/runPOC', argv_1], stdout=subprocess.PIPE)
    return jsonify(p.stdout.decode())


@app.route("/attack/analysis/DPA", methods=['POST'])
def attack_analysis_dpa():
    argv_1 = request.get_json(force=True)
    p = subprocess.run(['bin/runDPA', argv_1], stdout=subprocess.PIPE)
    if p.returncode != 0:
        print(p.stdout.decode())
    return jsonify(p.stdout.decode())


@app.route("/attack/analysis/CPA", methods=['POST'])
def attack_analysis_cpa():
    argv_1 = request.get_json(force=True)
    p = subprocess.run(['bin/runCPA', argv_1], stdout=subprocess.PIPE)
    if p.returncode != 0:
        print(p.stdout.decode())
    return jsonify(p.stdout.decode())


if __name__ == "__main__":
    app.run()
