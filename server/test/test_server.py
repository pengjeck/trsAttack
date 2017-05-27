# --coding: utf-8--
# BY pj
# Date: 17-4-28
import json
import requests
from urllib.parse import urljoin

base_url = "http://localhost:9080/"


def get_variable_name(file_name="/home/pj/pro/secure/platform/test/variable.txt"):
    out_file = "/home/pj/pro/secure/platform/test/out.txt"
    with open(file_name, 'r') as rf, open(out_file, 'w') as wf:
        while True:
            line = rf.readline()
            if not line or len(line) == 0:
                break

            out = line.split(" ")
            wf.write(out[1][:-1] + "\n")
    return


def post_method(address, data):
    assert isinstance(data, dict)
    url = urljoin(base=base_url, url=address)
    data_str = json.dumps(data)
    r = requests.post(url, data=data_str)
    if r.status_code != 200:
        print("error code:", r.status_code)
        return

    print(r.text)


pretreatment_alignment_FFT = "/pretreatment/alignment/FFT"
pretreatment_alignment_StaticAlignment = "/pretreatment/alignment/StaticAlignment"
pretreatment_alignment_DTW = "/pretreatment/alignment/DTW"
pretreatment_alignment_POC = "/pretreatment/alignment/POC"
attack_analysis_DPA = "/attack/analysis/DPA"

data1 = {
    "Align": "FFT",
    "OriginalPoints": 8,
    "traces": [
        [1, 2, 3, 4, 5, 6, 7, 8],
        [3, 4, 6, 7, 8, 9, 0, 1]
    ]
}

data2 = {
    "Align": "StaticAlignment",
    "RangeOffset": 0,
    "Start_Point": 0,
    "TotalPoints": 8,
    "refer_trace": [8, 3, 4, 3, 2, 4, 1, 3],
    "traces": [
        [1, 2, 3, 4, 5, 6, 7, 8],
        [3, 4, 6, 7, 8, 9, 0, 1]
    ]
}

data3 = {
    "Align": "DTW",
    "refer_trace": [8, 3, 4, 3, 2, 4, 1, 3],
    "traces": [
        [1, 2, 3, 4, 5, 6, 7, 8],
        [3, 4, 6, 7, 8, 9, 0, 1]
    ]
}

data4 = {
    "Align": "POC",
    "refer_trace": [8, 3, 4, 3, 2, 4, 1, 3],
    "OriginalPoints": 8,
    "traces": [
        [1, 2, 3, 4, 5, 6, 7, 8],
        [3, 4, 6, 7, 8, 9, 0, 1]
    ]
}

data5 = {
    "Points": 8,
    "Waves": 1,
    "addRoundKey": ["0123456789ABCDEF"],
    "traces": [
        [-1, 2, -3, 4, -5, 6, 2, 1]
    ]
}

# get_variable_name()
# post_method(pretreatment_alignment_FFT, data1)
# post_method(pretreatment_alignment_StaticAlignment, data2)
post_method(attack_analysis_DPA, data5)
# post_method(pretreatment_alignment_POC, data4)
