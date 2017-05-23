// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import Vuex from 'vuex'
import store from './store/store'
// import App from './App.vue'
import trsapp from './trsapp.vue'
// import test from './test.vue'
import router from './router'
import iView from 'iview'
import 'iview/dist/styles/iview.css'
import VueResource from 'vue-resource'

// import ElementUI from 'element-ui'
// import 'element-ui/lib/theme-default/index.css'

// Vue.config.productionTip = false
Vue.use(iView)
// Vue.use(ElementUI)
Vue.use(VueResource)
Vue.use(Vuex)

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  store,
  // template: '<test/>',
  // components: { test }
  template: '<trsapp/>',
  components: { trsapp }
})
