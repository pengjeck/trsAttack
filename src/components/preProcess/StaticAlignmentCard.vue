<style>

</style>

<template>
  <div style="margin-bottom: 5px;">
    <Card :style="{height: rowHeight + 'px'}">
      <div v-show="buttonVisible"
           style="text-align:center;">
        <Button type="ghost"
                icon="grid"
                shape="circle"
                size="large"
                @click="runPreProcessMethod">
          {{ methodName }}
        </Button>
      </div>
      <div
        :id="filename + '_' + preProcess + '_' + methodName"
        class="chart"
        :style="{height: (rowHeight - 20) + 'px'}">
      </div>
    </Card>

    <static-alignment-modal
      @cancel="cancel"></static-alignment-modal>
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
      },
      rowHeight: function () {
        return this.$store.state.interfaceConfig.appHeight / 2 - 20
      }
    },
    methods: {
      runPreProcessMethod () {
        this.$store.commit('SetMethodConfigModalVisual',
          [this.preProcess, this.methodName, true])
        this.buttonVisible = false
      },
      cancel () {
        this.buttonVisible = true
      }
    },
    components: {
      StaticAlignmentModal
    }
  }
</script>
