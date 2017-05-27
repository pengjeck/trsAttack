<style>
  .chart {
    height: 100%;
    width: 100%;
  }

  .chart-init {
    height: 100%;
    width: 100%;
  }

  .chart-loading {
    height: 100%;
    width: 100%;
  }
</style>

<template>
  <div>
    <Row type="flex"
         :gutter="16">
      <i-col span="12">
        <static-alignment-card>
        </static-alignment-card>
      </i-col>
      <i-col span="12">
        <poc-card></poc-card>
      </i-col>
      <i-col span="12">
        <fft-card></fft-card>
      </i-col>
      <i-col span="12">
        <dtw-card></dtw-card>
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
  import fftCard from './fftCard.vue'
  import dtwCard from './dtwCard.vue'
  import pocCard from './pocCard.vue'
  import StaticAlignmentCard from './StaticAlignmentCard.vue'
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
      StaticAlignmentCard,
      fftCard,
      dtwCard,
      pocCard
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
