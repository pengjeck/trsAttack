// import TraceData from './traceData'
// import SingleTrace from './singleTrace'

function TraceData (filename = null, traceNum = 0, sampleNum = 0) {
  /**
   * 文件名
   * @type {string}
   */
  this.filename = filename
  // ---------------------- 头部信息 ---------------------
  this.traceRange = [0, 0]  // [a, b) => [0, 0] => [0, 0) => nothing
  this.sampleRange = [0, 0] // [a, b)
  /**
   * trace的数量
   * @type {number}
   */
  this.traceNum = 0
  /**
   * 每条曲线的样本个数
   * @type {number}
   */
  this.sampleNum = 0
  /**
   * 样本数据的类型
   *  true: integer
   *  false: float
   * @type {boolean}
   */
  this.sampleType = true
  /**
   * 加密的数据的长度
   * @type {number}
   */
  this.cryDataLen = 0
  /**
   * 样本数据的长度
   * @type {number}
   */
  this.sampleDataLen = 1
  this.titleSpaceLen = 0
  /**
   * 曲线全局的名称
   * @type {null}
   */
  this.globalTitle = 'trace'
  /**
   * x轴的名称
   * @type {null}
   */
  this.labelX = 'x'
  /**
   * y轴的名称
   * @type {null}
   */
  this.labelY = 'y'
  /**
   * x轴一单元的尺度
   * @type {number}
   */
  this.scaleX = 0.0
  /**
   * y轴一单元的尺度
   * @type {number}
   */
  this.scaleY = 0.0
  /**
   * x的偏移
   * @type {number}
   */
  this.xOffset = 0
  /**
   * 描述
   * @type {null}
   */
  this.description = null

  // ------------------- 头部信息 end --------------------

  /**
   * 文件头部的长度
   * @type {number}
   */
  this.fHeaderLen = 0

  // --- 曲线 ---

  /**
   * 曲线 （元素为singleTrace类型）
   * @type {Array}
   */
  this.traces = []

  // --- 控制显示 ----
  this.show = false

  /**
   * 设置必备一些参数
   * @param filename
   * @param traceNum
   * @param sampleNum
   * @param traces
   * @param traceRange
   * @param sampleRange
   */
  let setCompulsory = function (filename, traceNum, sampleNum, traces, traceRange, sampleRange) {
    if (filename === null ||
      traceNum === null ||
      sampleNum === null ||
      traces === null ||
      traceRange === null ||
      sampleRange === null) {
      throw new TypeError('filename, traceNum, sampleNum, ' +
        'traces, traceRange and sampleRange can not be null')
    }

    if (traceNum === 0) {
      throw new EvalError('traceNum should be 0')
    }
    if (sampleNum === 0) {
      throw new EvalError('sampleNum should be 0')
    }
    if (traces.length === 0) {
      throw new EvalError('trace length should equal to zero')
    }
    if (traceRange[1] - traceRange[0] !== traces.length) {
      throw new EvalError('traceRange div should equal to traces.length')
    }
    for (let trace in traces) {
      if (trace.length !== sampleRange[1] - sampleRange[0]) {
        throw new EvalError('sampleRange div should equal to trace.length')
      }
    }
    // check over
    this.filename = filename
    this.traceNum = traceNum
    this.sampleNum = sampleNum
    this.traces = traces
    this.traceRange = traceRange
    this.sampleRange = sampleRange
  }

  /**
   * 计算曲线的长度
   * @returns {*}
   */
  let SingleTraceLen = function () {
    return this.titleSpaceLen + this.cryDataLen + this.sampleDataLen * this.sampleNum
  }

  let GetTraces = function () {
    return this.traces
  }

  let SetTraces = function (traces) {
    for (let trace in traces) {
      if (!(trace instanceof SingleTrace)) {
        throw new EvalError('trace should be SingleTrace instance')
      }
    }
    this.traces = traces
  }

  /**
   * 将该对象中很多的traces转换为json数组
   * @returns {Array}
   */
  let ToSingleTracesJson = function () {
    let jsonTraces = []
    this.traces.forEach((value) => {
      jsonTraces.push(value.toJson())
    })
    return jsonTraces
  }
}

function SingleTrace () {
  this.samples = []
  this.cryData = ''
  this.traceTitle = ''
  this.traceIndex = ''
  this.sampleBegIndex = 0

  /**
   * 获取sample的个数
   */
  let getSampleNum = function () {
    return this.samples.length
  }

  /**
   * 转成json的数据格式
   */
  let toJson = function () {
    return {
      'samples': this.samples,
      'cryData': this.cryData,
      'traceTitle': this.traceTitle,
      'traceIndex': this.traceIndex,
      'sampleBegIndex': this.sampleBegIndex,
      'sampleEndIndex': this.sampleEndIndex
    }
  }
}

function byte2binary (n) {
  if (n < 0 || n > 255 || n % 1 !== 0) {
    throw new Error(n + ' does not fit in a byte')
  }
  return ('000000000' + n.toString(2)).substr(-8)
}

/**
 * Created by pj on 17-4-9.
 */
const fs = require('fs')

/**
 * 读取头文件
 * @param path
 */
function readHeader (path) {
  // 检测文件是否有问题
  fs.stat(path, function (err, stat) {
    if (err === null) {
      if (!stat.isFile()) {
        throw new MediaError('file do not exists')
      }
    } else {
      throw new MediaError('file do not exists')
    }
  })
  var fd = fs.openSync(path, 'r')
  let traceData = new TraceData()
  traceData.filename = path
  let stopFlag = false
  let stepSize = 2
  /*
   * state 在这里表明处理字符时的状态。
   *  =0 正在处理tag and length
   *  =1 正在处理内容
   */
  let stepStatus = 0
  let stepTag = 0

  function opTagAndLength () {
    let buffer = Buffer.alloc(stepSize)
    fs.readSync(fd, buffer, 0, stepSize, traceData.fHeaderLen)
    traceData.fHeaderLen += stepSize
    stepTag = buffer.readInt8(0)
    stepSize = buffer.readInt8(1)
    if (stepTag === 95 && stepSize === 0) {
      stopFlag = true
    }
    stepStatus = 1
  }

  function opInfo () {
    let buffer = Buffer.alloc(stepSize)
    fs.readSync(fd, buffer, 0, stepSize, traceData.fHeaderLen)
    traceData.fHeaderLen += stepSize
    // assert(bytesLen === stepSize)
    if (stepTag === 65 ||
      stepTag === 66 ||
      stepTag === 68 ||
      stepTag === 69 ||
      stepTag === 72) {
      /*
       * convert to int;
       */
      let result = 0
      if (stepTag === 68) {
        result = buffer.readInt16LE(0)
      } else if (stepTag === 69) {
        result = buffer.readInt8(0)
      } else {
        result = buffer.readInt32LE(0)
      }
      switch (stepTag) {
        case 65:
          traceData.traceNum = result
          break
        case 66:
          traceData.sampleNum = result
          break
        case 68:
          traceData.cryDataLen = result
          break
        case 69:
          traceData.titleSpaceLen = result
          break
        case 72:
          traceData.xOffset = result
          break
        default:
          break
      }
    } else if (stepTag === 70 ||
      stepTag === 71 ||
      stepTag === 73 ||
      stepTag === 74) {
      /*
       * convert to string
       */
      let result = buffer.toString()
      switch (stepTag) {
        case 70:
          traceData.globalTitle = result
          break
        case 71:
          traceData.description = result
          break
        case 73:
          traceData.labelX = result
          break
        case 74:
          traceData.labely = result
          break
        default:
          break
      }
    } else if (stepTag === 67) {
      /*
       * convert to binary string
       */
      let result = byte2binary(buffer.readInt8(0))
      traceData.sampleType = result[3] !== '1'
      if (result[7] === '1') {
        traceData.sampleDataLen = 1
      } else if (result[6] === '1') {
        traceData.sampleDataLen = 2
      } else if (result[5] === '1') {
        traceData.sampleDataLen = 4
      }
    } else if (stepTag === 75 || stepTag === 76) {
      /*
       * convert to float
       */
      let result = buffer.readFloatLE(0)
      switch (stepTag) {
        case 75:
          traceData.scaleX = result
          break
        case 76:
          traceData.scaleY = result
          break
        default:
          break
      }
    } else if (stepTag === 68) {

    }
    stepStatus = 0
    stepSize = 2
  }

  while (true) {
    switch (stepStatus) {
      case 0:
        opTagAndLength()
        break
      case 1:
        opInfo()
        break
    }
    if (stopFlag) {
      // traceData.fHeaderLen += 2
      break
    }
    // traceData.fHeaderLen += stepSize
  }
  return traceData
}

/**
 * 解析读取出来的原始曲线（不包括头文件）
 * @param rawSingleTraceData
 * @param titleSpaceLen
 * @param cryDataLen
 * @param sampleType
 * @param sampleDataLen
 * @returns {SingleTrace}
 */
function readSingleTraceData (rawSingleTraceData, titleSpaceLen, cryDataLen,
                              sampleType, sampleDataLen) {
  let singleTrace = new SingleTrace()
  singleTrace.traceTitle = rawSingleTraceData.slice(0, cryDataLen)
  singleTrace.cryData = rawSingleTraceData.slice(cryDataLen, titleSpaceLen)
  let index = titleSpaceLen + cryDataLen
  while (true) {
    /**
     * if is integer
     */
    let out = null
    if (sampleType) {
      switch (sampleDataLen) {
        case 1:
          out = rawSingleTraceData.readInt8(index)
          break
        case 2:
          out = rawSingleTraceData.readInt16LE(index)
          break
        case 4:
          out = rawSingleTraceData.readInt32LE(index)
          break
        default:
          console.log('error')
          break
      }
    } else {
      switch (cryDataLen) {
        case 1:
          console.log('can not do this')
          break
        case 2:
          console.log('can not do this')
          break
        case 4:
          out = rawSingleTraceData.readFloatLE(index)
          break
        default:
          console.log('error')
          break
      }
    }
    singleTrace.samples.push(out)
    index += sampleDataLen
    if (index === rawSingleTraceData.length) {
      break
    }
  }
  return singleTrace
}

/**
 * 读取多条traces
 * @param traceData
 * @param begIndex
 * @param endIndex
 * @returns {*}
 */
function readMultiTrace (traceData, begIndex, endIndex) {
  if (!(traceData instanceof TraceData)) {
    throw new TypeError('params header should be TraceData instanceof')
  }
  if (begIndex > endIndex) {
    throw new EvalError('begIndex should smaller than endIndex')
  }
  if (begIndex === endIndex) {
    return traceData
  }
  let fd = fs.openSync(traceData.filename, 'r')

  let singleTraceLen = traceData.titleSpaceLen + traceData.cryDataLen +
    traceData.sampleDataLen * traceData.sampleNum

  let position = begIndex * singleTraceLen + traceData.fHeaderLen
  let buffer = Buffer.alloc(singleTraceLen)
  for (let i = begIndex; i < endIndex; i++) {
    fs.readSync(fd, buffer, 0, singleTraceLen, position)
    position += singleTraceLen
    let singleTrace = readSingleTraceData(buffer,
      traceData.titleSpaceLen,
      traceData.cryDataLen,
      traceData.sampleType,
      traceData.sampleDataLen)
    singleTrace.traceIndex = i
    traceData.traces.push(singleTrace)
  }
  return traceData
}
//
// module.exports.readMultiTrace = readMultiTrace
// module.exports.readHeader = readHeader
let path = '/home/pj/pro/js/trsapp/data/AES_Tang100.trs'
let header = readHeader(path)
let content = readMultiTrace(header, 0, 2)
console.log(content)
