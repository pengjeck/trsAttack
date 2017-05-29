/**
 * Created by pj on 17-5-19.
 */

import echarts from 'echarts'
import { paintLines, paintTraces, paintRibbons } from '../../util/paint'
// import Json2SingleTraces from '../../util/singleTrace'
// const {dialog} = require('electron').remote
// electron about
// import { ipcRenderer } from 'electron'

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
            configModalShow: true,
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
          staticAlignment: {
            name: '静态对齐',
            configModalShow: false,
            charts: {}
          },
          FFT: {
            name: '快速傅里叶变换',
            configModalShow: false,
            charts: {}
          },
          DTW: {
            name: 'DTW',
            configModalShow: false,
            charts: {}
          },
          POC: {
            name: 'POC',
            configModalShow: false,
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
            configModalShow: false,
            charts: {}
          },
          CPA: {
            name: 'CPA',
            configModalShow: false,
            charts: {}
          },
          MIA: {
            name: 'MIA',
            configModalShow: false,
            charts: {}
          },
          TA: {
            name: 'TA',
            configModalShow: false,
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
    PaintTarget (state, params) {
      let processName = params[0]
      let methodName = params[1]
      let target = params[2]  // a target
      try {
        if ((!state.processes[processName].methods[methodName].charts.hasOwnProperty(target.filename)) ||
          state.processes[processName].methods[methodName].charts[target.filename] === null) {
          let div = document.getElementById(
            target.filename + '_' + processName + '_' + methodName
          )
          state.processes[processName].methods[methodName].charts[target.filename] = echarts.init(div)
        }
        paintTraces(state.processes[processName].methods[methodName].charts[target.filename], // chart
          target.traces,   // traces
          target.labelX, target.labelY,
          target.scaleX, target.scaleY,
          methodName)
      } catch (e) {
        throw e
      }
    },
    PaintTraces (state, params) {
      let filename = params[0]
      let processName = params[1]
      let methodName = params[2]
      let traces = params[3] // singeTrace Object array
      try {
        if ((!state.processes[processName].methods[methodName].charts.hasOwnProperty(filename)) ||
          state.processes[processName].methods[methodName].charts[filename] === null) {
          let div = document.getElementById(
            filename + '_' + processName + '_' + methodName
          )
          state.processes[processName].methods[methodName].charts[filename] = echarts.init(div)
        }
        paintTraces(state.processes[processName].methods[methodName].charts[filename],
          traces,
          '', '',  // labelx, labely
          1, 1, // scalex, scaley
          methodName)
      } catch (e) {
        throw e
      }
    },
    PaintLines (state, params) {
      let filename = params[0]   // 为了获取需要绘图的对象
      let processName = params[1]
      let methodName = params[2]
      let lines = params[3] // (int/float) array array
      try {
        if ((!state.processes[processName].methods[methodName].charts.hasOwnProperty(filename)) ||
          state.processes[processName].methods[methodName].charts[filename] === null) {
          let div = document.getElementById(
            filename + '_' + processName + '_' + methodName
          )
          state.processes[processName].methods[methodName].charts[filename] = echarts.init(div)
        }
        paintLines(state.processes[processName].methods[methodName].charts[filename],
          lines,
          '', '',  // labelx, labely
          1, 1, // scalex, scaley
          methodName)
      } catch (e) {
        throw e
      }
    },
    PaintRibbon (state, params) {
      let container = params[0] // 容器
      let lines = params[1]
      try {
        paintRibbons(container, lines)
      } catch (e) {
        throw e
      }
    },
    /**
     * 设置可见性
     * @param state
     * @param params
     * @constructor
     */
    SetMethodConfigModalVisual (state, params) {
      let processName = params[0]
      let methodName = params[1]
      state.processes[processName].methods[methodName].configModalShow = params[2]
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
    MethodConfigModalShow: (state, getters) => (processName, methodName) => {
      return getters.Method(processName, methodName).configModalShow
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
