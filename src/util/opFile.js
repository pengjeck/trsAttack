/**
 * Created by pj on 17-5-17.
 */
const fs = require('fs')
const crypto = require('crypto')
const {app, dialog} = require('electron').remote

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
 * @param Data json格式的数据
 * @param filePath
 */
function saveJson (Data, filePath) {
  // convert data to string
  let json = JSON.stringify(Data)
  // write data
  fs.writeFile(filePath, json, 'utf8')
}

function createDir (dir) {
  let totalDir = app.getAppPath() + '/' + dir
  try {
    if (!fs.existsSync(totalDir)) {
      fs.mkdirSync(totalDir)
    }
  } catch (e) {
    dialog.showErrorBox('错误', '程序初始化失败\n' + e.message)
  }
}

function beforeSaveProcessData (processName, methodName) {
  createDir('data')
  createDir('data/' + processName)
  createDir('data/' + processName + '/' + methodName)
}

function getProcessDataPath (processName, methodName, filename) {
  return app.getAppPath() + '/data' + '/' + processName + '/' + methodName + '/' + filename
}

function getProcessMethodPath (processName, methodName) {
  return app.getAppPath() + '/data' + '/' + processName + '/' + methodName
}

/**
 * 查找文件
 * @param processName
 * @param methodName
 * @param filename
 */
function queryProcessData (processName, methodName, filename) {
  let totalPath = getProcessDataPath(processName, methodName, filename)
  if (fs.existsSync(totalPath)) {
    return JSON.parse(fs.readFileSync(totalPath, 'utf8'))
  } else {
    return null
  }
}
/**
 *
 * @param processName
 * @param methodName
 * @param filename
 * @param data
 */
function saveProcessData (processName, methodName, filename, data) {
  beforeSaveProcessData(processName, methodName)
  let totalPath = getProcessMethodPath(processName, methodName)
  if (fs.existsSync(totalPath)) {
    filename = totalPath + '/' + filename
    saveJson(data, filename)
  } else {
    throw new MediaError('文件存储错误')
  }
}

export { calMD5, queryProcessData, saveProcessData }
