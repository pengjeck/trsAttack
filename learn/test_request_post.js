/**
 * Created by pj on 17-5-26.
 */
const request = require('request')
// let data = require('/home/pj/pro/js/trsapp/src/store/modules/testTarget.json')
// let data = {
//   fizz: 'buzz'
// }
const sample_str_target = require('./sample_str_target')
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

let staticAlignmentUrl = 'http://localhost:5000/preProcess/alignment/StaticAlignment'
let fftUrl = 'http://localhost:5000/preProcess/alignment/FFT'
let dtwUrl = 'http://localhost:5000/preProcess/alignment/DTW'
let pocUrl = 'http://localhost:5000/preProcess/alignment/POC'
// console.log(JSON.stringify(data))
// let url = 'http://httpbin.org/post'
request.post({
  url: staticAlignmentUrl,
  json: JSON.stringify(sample_str_target)
  // data: JSON.stringify(data)
}, function (error, response, body) {
  if (!error && response.statusCode === 200) {
    console.log(body)
  }
})
