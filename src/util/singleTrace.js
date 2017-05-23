export default class SingleTrace {
  /**
   * 构造函数
   */
  constructor (samples = [],
               traceIndex,
               traceTitle = '',
               cryData = '',
               sampleBegIndex = 0) {
    this.samples = samples
    this.cryData = cryData
    this.traceTitle = traceTitle
    this.traceIndex = traceIndex
    this.sampleBegIndex = sampleBegIndex
  }

  /**
   * 获取sample的个数
   */
  getSampleNum = () => {
    return this.samples.length
  }

  /**
   * 转成json的数据格式
   */
  toJson = () => {
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

/**
 * 将数据转为了singleTrace数据类型
 * @param rowSingleTrace
 * @returns {SingleTrace}
 * @constructor
 */
export function Json2SingleTrace (rowSingleTrace) {
  return new SingleTrace(rowSingleTrace['samples'],
    rowSingleTrace['traceIndex'],
    rowSingleTrace['traceTitle'],
    rowSingleTrace['cryData'],
    rowSingleTrace['sampleBegIndex'])
}

/**
 * 将json数据转换为singleTraces数据
 * @param rowContent
 * @returns {Array}
 * @constructor
 */
export function Json2SingleTraces (rowContent) {
  let traces = []
  rowContent['traces'].forEach((rowSingleTrace) => {
    traces.push(Json2SingleTrace(rowSingleTrace))
  })
  return traces
}
