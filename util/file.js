/**
 * Created by pj on 17-5-17.
 */
const fs = require('fs')
const crypto = require('crypto')

/**
 * 计算文件的md5值
 * @param filePath: 文件路径
 * @param callback: 回调函数
 */
function calMD5 (filePath, callback) {
  let md5sum = crypto.createHash('md5')
  let stream = fs.createReadStream(filePath)
  stream.on('data', function (chunk) {
    md5sum.update(chunk)
  })

  stream.on('end', function () {
    let str = md5sum.digest('hex').toUpperCase()
    callback(str)
  })
}

/**
 * 保存json数据
 * @param Data
 * @param filePath
 */
function saveJson (Data, filePath) {
  // convert data to string
  let json = JSON.stringify(Data)
  // write data
  fs.writeFile(filePath, json, 'utf8')
}

module.exports.saveJson = saveJson
