/**
 * 一个target，其实就是trace数据的聚合，这个对象里面包括文件的头部信息，
 * 文件解析处理的数据等。
 */
import SingleTrace from './singleTrace'
import hash from 'object-hash'
const path = require('path')

export default class TraceData {
  constructor (filename = null, traceNum = 0, sampleNum = 0) {
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
    this.scaleX = 1.0
    /**
     * y轴一单元的尺度
     * @type {number}
     */
    this.scaleY = 1.0
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
    this.tracesHash = null
    // --- 控制显示 ----
    this.show = false
  }

  /**
   * 设置必备一些参数
   * @param filename
   * @param traceNum
   * @param sampleNum
   * @param traces
   * @param traceRange
   * @param sampleRange
   */
  setCompulsory (filename, traceNum, sampleNum, traces, traceRange, sampleRange) {
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
    // 这段代码是错误的
    // for (let trace in traces) {
    //   if (trace.length !== sampleRange[1] - sampleRange[0]) {
    //     throw new EvalError('sampleRange div should equal to trace.length')
    //   }
    // }
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
  SingleTraceLen = () => {
    return this.titleSpaceLen + this.cryDataLen + this.sampleDataLen * this.sampleNum
  }

  SetTraceHash = () => {
    if (this.traces.length !== 0) {
      this.tracesHash = hash(this.traces)
    }
  }

  GetShortFileName = () => {
    return path.basename(this.filename)
  }

  GetTraces = () => {
    return this.traces
  }
  SetTraces = (traces) => {
    for (let trace in traces) {
      if (!(trace instanceof SingleTrace)) {
        throw new EvalError('trace should be SingleTrace instance')
      }
    }

    this.traces = traces
  }

  /**
   * data中取出来的每条曲线的样本的数量
   * @return {number}
   */
  GetInSampleNum = () => {
    return this.sampleRange[1] - this.sampleRange[0]
  }
  /**
   * data中取出来的曲线的数量
   * @returns {number}
   * @constructor
   */
  GetInTraceNum = () => {
    return this.traceRange[1] - this.traceRange[0]
  }

  /**
   * 将该对象中很多的traces转换为json数组
   * @returns {Array}
   */
  ToSingleTracesJson = () => {
    let jsonTraces = []
    this.traces.forEach((value) => {
      jsonTraces.push(value.toJson())
    })
    return jsonTraces
  }
}
