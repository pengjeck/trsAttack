<style>
</style>

<template>
  <Modal
    :closable="false"
    :mask-closable="false"
    v-model="StaticAlignmentModalVisual"
    :title="methodName + '配置'">
    <row-number-input illustrate="基准曲线"
                      :inputNumberRange="targetTraceRange"
                      ref="referTraceIndex">
    </row-number-input>
    <div slot="footer">
      <Button icon="close-round" @click="abolish">
        <span>取消</span>
      </Button>
      <Button type="primary"
              icon="checkmark-round"
              @click="confirm">
        <span>确认</span>
      </Button>
    </div>
  </Modal>
</template>

<script>
  import rowNumberInput from '../basic/rowNumberInput.vue'
  import Button from '../../../node_modules/iview/src/components/button/button'
  let request = require('request')
  import { HOST } from '../../util/localConfig'
  const {dialog} = require('electron').remote
  import { urlAddSubPath } from '../../util/url'
  export default {
    components: {
      Button,
      rowNumberInput
    },
    data () {
      return {
        preProcess: 'preProcess',
        methodName: 'DTW'
      }
    },
    computed: {
      targetTraceRange: function () {
        return [this.target.traceRange[0], this.target.traceRange[1] - 1]
      },
      target: function () {
        try {
          return this.$store.getters.Target(this.$store.state.activeTabName)[0]
        } catch (e) {
          dialog.showErrorBox('error', '内部错误')
        }
      },
      // 查找这个配置内容是否可见
      StaticAlignmentModalVisual: function () {
        return this.$store.getters.MethodConfigModalShow(this.preProcess, this.methodName)
      }
    },
    methods: {
      confirm: function () {
        try {
          let data = {
            referTrace: this.target.traces[this.$refs.referTraceIndex.getInputNumber() - this.target.traceRange[0]].samples,
            traces: this.target.traces.map(trace => trace.samples)
          }
          let url = urlAddSubPath(HOST, this.preProcess)
          url = urlAddSubPath(url, 'alignment')
          url = urlAddSubPath(url, this.methodName)
          let options = {
            url: url,
            json: JSON.stringify(data)
          }
          let upperThis = this
          request.post(options,
            function (error, response, body) {
              if (!error && response.statusCode === 200) {
                let content = JSON.parse(body)
                // 对象复制
//              let targetForPaint = Object.assign({}, upperThis.target)
//              targetForPaint.traces = content.traces
                upperThis.$store.commit('PaintLines', [
                  upperThis.target.filename,
                  upperThis.preProcess,
                  upperThis.methodName,
                  content.traces
                ])
                upperThis.$store.commit('SetMethodConfigModalVisual',
                  [upperThis.preProcess, upperThis.methodName, false])
                upperThis.$emit('success')
              } else {
                upperThis.$emit('error',
                  '网络|服务器内部错误\n' + error + '\n' + response.statusCode)
                upperThis.$store.commit('SetMethodConfigModalVisual',
                  [upperThis.preProcess, upperThis.methodName, false])
              }
            })
        } catch (e) {
          this.$emit('error', e.message)
        }
      },
      abolish: function () {
        this.$store.commit('SetMethodConfigModalVisual',
          [this.preProcess, this.methodName, false])
        this.$emit('cancel')
      }
    }
  }
</script>
