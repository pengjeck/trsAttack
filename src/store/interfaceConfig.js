const electron = require('electron')

export default {
  appHeight: electron.screen.getPrimaryDisplay().size.height - 120
}
