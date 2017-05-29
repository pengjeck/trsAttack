const electron = require('electron')
let pid = new Date() - 0  // 只执行一次
console.log('pid:' + pid)
export default {
  appHeight: electron.screen.getPrimaryDisplay().size.height - 120,
  recentFilename: pid.toString()
}
