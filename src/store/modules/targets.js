/**
 * Created by pj on 17-5-19.
 */
import TraceData from '../../util/traceData'
// const testTraceData = require('./testTarget.json')

export default {
  namespace: true,
  state: {
    targets: []
  },
  mutations: {
    PushTarget (state, target) {
      if (!(target instanceof TraceData)) {
        throw new TypeError('target should be TraceData instance')
      }
      state.targets.push(target)
    },
    RemoveTarget (state, filename) {
      state.targets = state.targets.filter((target) => {
        return target.filename !== filename
      })
    }
  },
  actions: {},
  getters: {
    AllTarget: (state) => {
      return state.targets
    },
    Target: (state) => (targetFilename) => {
      return state.targets.filter((target) => {
        return target.filename === targetFilename
      })
    },
    Traces: (state) => (targetFilename) => {
      return state.Target(targetFilename).traces
    },
    SampleRanage: (state) => (targetFilename) => {
      return state.Target(targetFilename).sampleRange
    },
    TraceRange: (state) => (targetFilename) => {
      return state.Target(targetFilename).traceRange
    }
  }
}
