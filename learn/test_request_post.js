/**
 * Created by pj on 17-5-26.
 */
const request = require('request')
// let data = require('/home/pj/pro/js/trsapp/src/store/modules/testTarget.json')
// let data = {
//   fizz: 'buzz'
// }
// const sample_str_target = require('./sample_str_target')
let data1 = {
  Align: 'FFT',
  OriginalPoints: 8,
  traces: [
    [1, 2, 3, 4, 5, 6, 7, 8],
    [3, 4, 6, 7, 8, 9, 0, 1]
  ]
}

let data2 = {
  Align: 'StaticAlignment',
  RangeOffset: 0,
  Start_Point: 0,
  TotalPoints: 8,
  refer_trace: [8, 3, 4, 3, 2, 4, 1, 3],
  traces: [
    [1, 2, 3, 4, 5, 6, 7, 8],
    [3, 4, 6, 7, 8, 9, 0, 1]
  ]
}

let data3 = {
  Align: 'DTW',
  refer_trace: [8, 3, 4, 3, 2, 4, 1, 3],
  traces: [
    [1, 2, 3, 4, 5, 6, 7, 8],
    [3, 4, 6, 7, 8, 9, 0, 1]
  ]
}

let data4 = {
  Align: 'POC',
  refer_trace: [8, 3, 4, 3, 2, 4, 1, 3],
  OriginalPoints: 8,
  traces: [
    [1, 2, 3, 4, 5, 6, 7, 8],
    [3, 4, 6, 7, 8, 9, 0, 1]
  ]
}

let data5 = {
  points: 16,
  waves: 3,
  addRoundKey: [
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
    [22, 3, 4, 5, 53, 76, 245, 132, 44, 55, 66, 77, 3, 5, 66, 7],
    [16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
  ],
  traces: [
    [-1.3, 2.1, -3.4, 4.8, 5.0, -6.3, 7.2, -8.1, 3.0, 2.2, -5.5, -7.2, 3.8, 2.6, 5.9, -1.5],
    [-3, 2, 3, 6, -5, 0, 4, -2, 6, -3, 2, 6, -3, 6, -3, -6],
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 0, 1, 2]
  ]
}

let staticAlignmentUrl = 'http://localhost:5000/preProcess/alignment/StaticAlignment'
let fftUrl = 'http://localhost:5000/preProcess/alignment/FFT'
let dtwUrl = 'http://localhost:5000/preProcess/alignment/DTW'
let pocUrl = 'http://localhost:5000/preProcess/alignment/POC'
let dpaUrl = 'http://localhost:5000/attack/analysis/DPA'
let cpaUrl = 'http://localhost:5000/attack/analysis/CPA'

// console.log(JSON.stringify(data))
// let url = 'http://httpbin.org/post'
request.post({
  url: dpaUrl,
  json: JSON.stringify(data5)
  // data: JSON.stringify(data)
}, function (error, response, body) {
  if (!error && response.statusCode === 200) {
    console.log(body)
  }
})
