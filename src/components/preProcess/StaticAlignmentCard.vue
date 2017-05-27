<style>

</style>

<template>
  <div>
    <Card>
      <div v-show="buttonVisible"
        style="text-align:center;">
        <Button type="ghost"
                icon="grid"
                shape="circle"
                size="large"
                @click="runPreProcessMethod()">
          {{ methodName }}
        </Button>
      </div>
      <div
        :id="filename + '_' + preProcess + '_' + methodName"
        class="chart">
      </div>
    </Card>

    <static-alignment-modal></static-alignment-modal>
  </div>
</template>

<script>
  //  import { is2Exp } from '../../util/baseic'
  //  const {dialog} = require('electron').remote
  import StaticAlignmentModal from './StaticAlignmentModal.vue'

  export default {
    data () {
      return {
        preProcess: 'preProcess',
        methodName: 'staticAlignment',
        buttonVisible: true
      }
    },
    computed: {
      filename: function () {
        return this.$store.state.activeTabName
      },
      // 判断是否已经执行完毕
      finished: function () {
        return this.$store.getters.HasChart(this.filename,
          this.preProcess,
          this.methodName)
      }
    },
    methods: {
      runPreProcessMethod () {
        this.$store.commit('SetMethodConfigModalVisual',
          [this.preProcess, this.methodName, true])
        this.buttonVisible = false
      }
    },
    components: {
      StaticAlignmentModal
    }
  }
</script>
