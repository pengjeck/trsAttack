/**
 * Created by pj on 17-5-26.
 */
const request = require('request')
// let data = require('/home/pj/pro/js/trsapp/src/store/modules/testTarget.json')
let data = {'fizz': 'buzz'}
let url = 'http://localhost:9081/pretreatment/alignment/StaticAlignment'
// console.log(JSON.stringify(data))
// let url = 'http://httpbin.org/post'
request.post({
  url: url,
  headers: {'content-type': 'application/x-www-form-urlencoded'},
  json: JSON.stringify(data),
  data: JSON.stringify(data)
}, function (error, response, body) {
  console.log(error)
  if (!error && response.statusCode === 200) {
    console.log(body)
  }
})
