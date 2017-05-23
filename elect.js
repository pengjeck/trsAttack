/**
 * Created by pj on 17-5-17.
 */

const {
  app, BrowserWindow,
  globalShortcut, dialog, ipcMain
} = require('electron')
const {saveJson} = require('./util/file')
const fs = require('fs')

let mainWindow = null

const url = 'http://localhost:8080'
// let url = 'file:///home/pj/pro/js/webapp/util/test.html'
// let url = '/home/pj/pro/js/webapp/index.html'
function createWindow () {
  mainWindow = new BrowserWindow({
    icon: '/home/pj/pro/js/webapp/src/assets/logo.png'
  })
  mainWindow.loadURL(url)
  mainWindow.maximize()  // 最大化窗口
  mainWindow.webContents.openDevTools()
  mainWindow.on('closed', function () {
    mainWindow = null
  })
}

/**
 * 目录结构大概是：
 *    ./data(dir)
 *      processName(dir)
 *         methodName(dir)
 *            dataName(file)
 */
/**
 * 创建dir
 * @param dir
 */
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
// >>>>>>>>>>>> ipc main >>>>>>>>>>>>

ipcMain.on('testIpcRenderer', (event, args) => {
  console.log(args)
})

ipcMain.on('chooseFileType', (event, args) => {
  console.log('get')
})

/**
 * queryProcessData:查找数据
 *  找到则返回数据
 *  没找到则返回空数据
 */
ipcMain.on('queryProcessData', (event, args) => {
  let processName = args['processName']
  let methodName = args['methodName']
  let filename = args['filename']
  let totalPath = getProcessDataPath(processName, methodName, filename)
  if (fs.existsSync(totalPath)) {
    event.returnValue = JSON.parse(fs.readFileSync(totalPath, 'utf8'))
  } else {
    event.returnValue = null
  }
})

/**
 * saveProcessData：保存数据
 */
ipcMain.on('saveProcessData', (event, args) => {
  let processName = args['processName']
  let methodName = args['methodName']
  let filename = args['filename']
  beforeSaveProcessData(processName, methodName)
  let totalPath = getProcessMethodPath(processName, methodName)
  let traces = args['traces'] // 传递过来的数据
  if (fs.existsSync(totalPath)) {
    filename = totalPath + '/' + filename
    saveJson(traces, filename)
  }
})

// <<<<<<<<<<<< ipc main end <<<<<<<<<<<<

app.on('ready', function () {
  let result = globalShortcut.register('F5', () => {
    mainWindow.reload()
  })
  if (!result) {
    dialog.showErrorBox('error', 'cannot register global shortcut')
  }
  result = globalShortcut.register('F12', () => {
    mainWindow.webContents.openDevTools()
  })
  if (!result) {
    dialog.showErrorBox('error', 'cannot register global shortcut')
  }

  createWindow()
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
})

app.on('window-all-closed', function () {
  app.quit()
})
