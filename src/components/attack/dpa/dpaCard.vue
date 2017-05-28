<style>

</style>

<template>
  <div>
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
        :id="filename + '_' + attack + '_' + methodName"
        class="chart"
        :style="{height: (rowHeight - 20) + 'px'}">
      </div>
    </Card>

    <dpa-modal
      @cancel="cancel"
      @error="error"
      @success="success">
    </dpa-modal>
  </div>
</template>

<script>
  import dpaModal from './dpaModal.vue'

  export default {
    data () {
      return {
        attack: 'attack',
        methodName: 'DPA',
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
          this.attack,
          this.methodName)
      },
      rowHeight: function () {
        return this.$store.state.interfaceConfig.appHeight / 2 - 20
      }
    },
    methods: {
      runPreProcessMethod () {
        this.$store.commit('SetMethodConfigModalVisual',
          [this.attack, this.methodName, true])
      },
      cancel () {
        this.buttonVisible = true
      },
      error (message) {
        this.$Message.info(message)
        this.buttonVisible = true
      },
      success () {
        this.buttonVisible = false
      }
    },
    components: {
      dpaModal
    }
  }
</script>
