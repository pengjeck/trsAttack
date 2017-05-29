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

    <cpa-modal
      @cancel="cancel"
      @error="error"
      @success="success">
    </cpa-modal>
    <template v-if="showModalVisible">
      <cpa-show-modal
        :visible="true"
        :content="showContent"
        :filename="filename">
      </cpa-show-modal>
    </template>
  </div>
</template>

<script>
  import cpaModal from './cpaModal.vue'
  import cpaShowModal from './cpaShowModal.vue'
  export default {
    data () {
      return {
        attack: 'attack',
        methodName: 'CPA',
        showModalVisible: false,
        buttonVisible: true,
        showContent: null // 不知道会不会出问题
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
        this.$store.commit('SetMethodConfigModalVisual',
          [this.attack, this.methodName, false]) // 关闭配置窗口
        this.buttonVisible = true
      },
      success (content) {
        this.buttonVisible = false
        this.$store.commit('SetMethodConfigModalVisual',
          [this.attack, this.methodName, false]) // 关闭配置窗口
        this.showContent = content
        this.showModalVisible = true
      }
    },
    components: {
      cpaModal,
      cpaShowModal
    }
  }
</script>
