<style>
</style>

<template>
  <div>
    <Row type="flex"
         :gutter="16">
      <i-col span="12">
        <dpa-card></dpa-card>
      </i-col>
      <i-col span="12">
        <cpa-card></cpa-card>
      </i-col>
      <i-col span="12">
        <mia-card></mia-card>
      </i-col>
    </Row>
  </div>
</template>


<!-- chart id： 命名格式为：
[文件名]-[处理过程]-[处理方法]  // 这个chart id 必须是全局唯一的
filename_processName_processMethod
 -->
<script>
  import Modal from '../../../node_modules/iview/src/components/modal/modal'
  // region >>>>>> import modals >>>>>>
  import dpaCard from './dpa/dpaCard.vue'
  import cpaCard from './cpa/cpaCard.vue'
  import miaCard from './mia/miaCard.vue'
  const {dialog} = require('electron').remote
  import ICol from '../../../node_modules/iview/src/components/grid/col'
  // endregion <<<<<< import modals <<<<<<

  export default {
    data () {
      return {
        preProcess: 'preProcess',
        methodNames: {
          StaticAlignment: 'StaticAlignment',
          FFT: 'FFT',
          DTW: 'DTW',
          POC: 'POC'
        }
      }
    },
    components: {
      ICol,
      Modal,
      dpaCard,
      cpaCard,
      miaCard
    },
    computed: {
      process: function () {
        return this.$store.getters.Process(this.preProcess)
      },
      rowHeight: function () {
        return this.$store.state.interfaceConfig.appHeight / 2
      },
      target: function () {
        try {
          return this.$store.getters.Target(this.$store.state.activeTabName)[0]
        } catch (e) {
          dialog.showErrorBox('error', '内部错误')
        }
      }
    },
    methods: {
    }
  }
</script>
