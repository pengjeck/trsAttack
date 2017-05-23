/**
 * Created by pj on 17-5-19.
 */

import echarts from 'echarts'
import paintLines from '../../util/paint'
import Json2SingleTraces from '../../util/singleTrace'
const {dialog} = require('electron').remote
// electron about
import { ipcRenderer } from 'electron'

export default {
  namespace: true,
  state: {
    /**
     * processName:
     *   methodName:
     *     charts:
     *       filename:
     *         charts: 对应的chart对象
     *           data_md5: 数据存储的位置
     */
    processes: {
      rowTrace: {
        name: '原始曲线',
        index: 0,
        iconType: 'ios-barcode',
        methods: {
          rowTrace: {
            name: '原始曲线',
            charts: {
              // 每个文件对应的charts
            }
          }
        }
      },
      preProcess: {
        name: '预处理',
        index: 1,
        iconType: 'funnel',
        methods: {
          StaticAlignment: {
            name: '静态对齐',
            charts: {}
          },
          FFT: {
            name: '快速傅里叶变换',
            charts: {}
          },
          DTW: {
            name: 'DTW',
            charts: {}
          },
          POC: {
            name: 'POC',
            charts: {}
          }
        }
      },
      attack: {
        name: '攻击',
        index: 2,
        iconType: 'hammer',
        methods: {
          DPA: {
            name: '差分',
            charts: {}
          },
          CPA: {
            name: 'CPA',
            charts: {}
          },
          MIA: {
            name: 'MIA',
            charts: {}
          },
          TA: {
            name: 'TA',
            charts: {}
          }
        }
      },
      assess: {
        name: '评价',
        index: 3,
        iconType: 'stats-bars',
        methods: {
          t_test: {
            name: 'T检验',
            charts: {}
          },
          k_rank: {
            name: 'k_rank',
            charts: {}
          }
        }
      },
      report: {
        name: '报告',
        index: 4,
        iconType: 'document-text',
        methods: {
          report: {
            name: 'report',
            charts: {}
          }
        }
      }
    }
  },
  mutations: {
    /***
     * 设置charts
     * @param state
     * @param processName
     * @param methodName
     * @param filename
     * @param chartObj
     * @constructor
     */
    SetChart (state, processName, methodName, filename, chartObj) {
      state.processes[processName].methods[methodName].charts[filename] = chartObj
    },
    /**
     * 删除文件的时候删除和该文件有关的所有的charts
     * @param state
     * @param filename
     * @constructor
     */
    DeleteChartsWithFiles (state, filename) {
      for (let processName in state.processes) {
        for (let methodName in state.processes[processName].methods) {
          for (let existsFilename in state.processes[processName].methods[methodName].charts) {
            if (filename === existsFilename) {
              // 删除掉已经存在的，不然下次不会重新绘图的。
              delete state.processes[processName].methods[methodName].charts[existsFilename]
            }
          }
        }
      }
    },
    /**
     * 绘图
     * @param state
     * @param params
     * @constructor
     */
    Paint (state, params) {
      let processName = params[0]
      let methodName = params[1]
      let target = params[2]
      try {
        if ((!state.processes[processName].methods[methodName].charts.hasOwnProperty(target.filename)) ||
          state.processes[processName].methods[methodName].charts[target.filename] === null) {
          let div = document.getElementById(
            target.filename + '_' + processName + '_' + methodName
          )
          state.processes[processName].methods[methodName].charts[target.filename] = echarts.init(div)
        }
        paintLines(state.processes[processName].methods[methodName].charts[target.filename],
          target.traces,
          target.labelX, target.labelY,
          target.scaleX, target.scaleY,
          methodName)
      } catch (e) {
        throw e
      }
    },
    /**
     * 发送http请求
     * @param methodName
     */
    processRequest (methodName) {
      let data = ipcRenderer.sendSync('queryProcessData', {
        processName: 'preProcess',
        methodName: methodName,
        filename: this.targetTraceHash
      })
      // yes I have found the data
      if (data !== null) {
        this.Paint(methodName, data)
      } else {
        // TODO: 填上url
        this.$http.get().then(response => {
          let data = response.body
          let jsondata = JSON.parse(data)
          // 处理之后的数据
          let traces = Json2SingleTraces(jsondata)
          this.Paint(methodName, traces)
          // save to file
          ipcRenderer.send('saveProcessData', {
            processName: 'preProcess',
            methodName: methodName,
            filename: this.targetTraceHash + '.json',
            traces: traces
          })
        }, response => {
          dialog.showErrorBox('网络错误', '无法连接到服务器，请稍后. \n' + response)
        })
      }
    }
  },
  getters: {
    /**
     * 判断是否有对应的chart
     * @param state
     * @constructor
     */
    HasChart: (state) => (processName, methodName, filename) => {
      try {
        return state.processes[processName].methods[methodName].charts.hasOwnProperty(filename)
      } catch (e) {
        return false
      }
    },
    /**
     * get all process
     * @param state
     * @returns {state.processes|{rowTrace, preProcess, attack, assess, report}}
     * @constructor
     */
    Processes (state) {
      return state.processes
    },
    /**
     * get process from processes
     * @param state
     * @param getters
     * @constructor
     */
    Process: (state, getters) => (processName) => {
      if (state.processes.hasOwnProperty(processName)) {
        return state.processes[processName]
      } else {
        throw new EvalError('you have wrong processName')
      }
    },
    /**
     * get process Name with Index
     * @param state
     * @param getters
     * @constructor
     */
    ProcessNameWithIndex: (state, getters) => (processIndex) => {
      if (processIndex < 0 || processIndex >= state.processes.length) {
        throw new RangeError('processIndex out of range')
      }
      for (let processName in state.processes) {
        if (state.processes[processName].index === processIndex) {
          return processName
        }
      }
      return ''
    },
    /**
     * get method in a process
     * @param state
     * @param getters
     * @constructor
     */
    Method: (state, getters) => (processName, methodName) => {
      let process = getters.Process(processName)
      if (process.methods.hasOwnProperty(methodName)) {
        return process.methods[methodName]
      } else {
        throw new EvalError('you have wrong methodName')
      }
    },
    /**
     * get processIndex
     * @param state
     * @param getters
     * @constructor
     */
    ProcessIndex: (state, getters) => (processName) => {
      let process = getters.Process(processName)
      if (process.hasOwnProperty('index')) {
        return process['index']
      } else {
        return -1
      }
    }
  }
}