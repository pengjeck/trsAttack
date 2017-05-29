<style></style>
<template>
  <!--取消默认关闭
    取消罩层关闭
    允许滚动
    宽度最大化
    -->
  <Modal
    :closable="false"
    :mask-closable="false"
    v-model="visible"
    :width="modalWidth"
    :scrollable="true"
    title="CPA处理结果">
    <Row type="flex">
      <i-col span="8"
             v-for="(item, index) in content.result[0]"
             :key="index">
        <Card :style="{height: rowHeight + 'px'}">
          <div
            :id="filename + '_' + attack + '_' + methodName + '_' + index"
            :style="{height: (rowHeight - 20) + 'px'}">
          </div>
        </Card>
      </i-col>
    </Row>

    <div slot="footer">
      <Button icon="close-round" @click="shutdown">
        <span>关闭</span>
      </Button>
    </div>
  </Modal>
</template>

<script>
  import ICol from '../../../../node_modules/iview/src/components/grid/col'
  const electron = require('electron')
  export default {
    components: {ICol},
    props: {
      visible: {
        type: Boolean,
        required: true
      },
      content: {
        type: Object,
        required: true
      },
      filename: {
        type: String,
        required: true
      }
    },
    data () {
      return {
        attack: 'attack',
        methodName: 'CPA'
      }
    },
    computed: {
      rowHeight: function () {
        return this.$store.state.interfaceConfig.appHeight / 2 - 20
      },
      modalWidth: function () {
        return electron.screen.getPrimaryDisplay().size.width - 120
      }
    },
    methods: {
      shutdown: function () {
        this.$emit('shutdown')
      }
    }
  }
</script>
