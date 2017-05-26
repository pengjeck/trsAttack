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
    <Row type="flex" :gutter="16" style="height: 480px;">
      <i-col
        span="12"
        v-for="(methodValue, methodName) in process.methods"
        :key="methodName">
        <Card
          v-if="methodValue.charts[targetFilename] !== undefined">
          <div
            :id="targetFilename + '-' + preProcess + '-' + methodName"
            class="chart">
          </div>
        </Card>
        <Card
          v-else
          class="chart-init">
          <div style="text-align:center;">
            <Button type="ghost"
                    icon="grid"
                    shape="circle"
                    size="large"
                    @click="runPreProcessMethod(methodName)">
              {{ methodName }}
            </Button>
          </div>
        </Card>
      </i-col>
    </Row>

    <static-alignment-modal></static-alignment-modal>
  </div>
</template>


<!-- chart id： 命名格式为：
[文件名]-[处理过程]-[处理方法]  // 这个chart id 必须是全局唯一的
filename-process_name-process_method
 -->
<script>
  const {dialog} = require('electron').remote
  import Modal from '../../../node_modules/iview/src/components/modal/modal'
  import { is2Exp } from '../../util/baseic'
  // region >>>>>> import modals >>>>>>
  import StaticAlignmentModal from './StaticAlignmentModal.vue'
  import FFTModal from './FFTModal.vue'
  import DTWModal from './DTWModal.vue'
  import POCModal from './POCModal.vue'
  // endregion <<<<<< import modals <<<<<<

  export default {
    components: {
      Modal,
      StaticAlignmentModal,
      FFTModal,
      DTWModal,
      POCModal
    },
    computed: {
      process: function () {
        return this.$store.getters.Process(this.preProcess)
      },
      height: function () {
        return 400
      },
      target: function () {
        try {
          return this.$store.getters.Target(this.$store.state.activeTabName)[0]
        } catch (e) {
          dialog.showErrorBox('error', '内部错误')
        }
      },
      targetFilename: function () {
        return this.$store.state.activeTabName
      }
    },
    methods: {
      runPreProcessMethod (methodName) {
        if (methodName === this.methodNames.FFT ||
          methodName === this.methodNames.POC) {
          if (!is2Exp(this.target.GetInSampleNum())) {
            dialog.showErrorBox('error', '数据错误，' +
              methodName + '方法只支持样本数为2的n次方的曲线')
            return
          }
        }
        this.$store.commit('SetMethodConfigModalVisual', [this.preProcess, methodName, true])
      }
    },
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
    }
  }
</script>
