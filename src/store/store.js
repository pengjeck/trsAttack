/**
 * Created by pj on 17-5-19.
 */
import Vue from 'vue'
import Vuex from 'vuex'
import mutations from './mutations'
import getters from './getters'
import actions from './actions'

import targets from './modules/targets'
import processes from './modules/processes'
import TraceData from '../util/traceData'
const interfaceConfig = require('./interfaceConfig.json')
Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    selectedTarget: new TraceData(),
    activeMenuName: 'rowTrace',  // processName
    activeTabName: null, // select filename
    selectModalVisual: false,
    interfaceConfig: interfaceConfig,
    // for test
    items: [
      {name: 'pj1', age: '123'},
      {name: 'pj2', age: '34'}
    ]
  },
  modules: {
    targets: targets,
    processes: processes
  },
  mutations,
  actions,
  getters: getters
})
