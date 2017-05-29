<style>
</style>

<template>
  <Modal
    :closable="false"
    :mask-closable="false"
    v-model="StaticAlignmentModalVisual"
    title="StaticAlignment配置">
    <row-number-input illustrate="偏移量"
                      :inputNumberRange="targetSampleRange"
                      ref="rangeOffset">
    </row-number-input>
    <row-number-input illustrate="起始点"
                      :inputNumberRange="targetSampleRange"
                      ref="startPoint">
    </row-number-input>
    <row-number-input illustrate="总点数"
                      :inputNumberRange="targetSampleRange"
                      ref="totalPoints">
    </row-number-input>
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
  import rowNumberInput from '../../basic/rowNumberInput.vue'
  let request = require('request')
  import { HOST } from '../../../util/localConfig'
  const {dialog} = require('electron').remote
  import { urlAddSubPath } from '../../../util/url'
  import hash from 'object-hash'
  import { queryProcessData, saveProcessData } from '../../../util/opFile'
  export default {
    components: {
      rowNumberInput
    },
    data () {
      return {
        preProcess: 'preProcess',
        methodName: 'staticAlignment'
      }
    },
    computed: {
      targetSampleRange: function () {
        // 不是使用原来的数据，使用一个拷贝避免内部对数据进行修改
        return [this.target.sampleRange[0], this.target.sampleRange[1]]
      },
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
      // 长文件名的hash值
      filenameHash: function () {
        return hash(this.$store.state.activeTabName)
      },
      // 查找是否可见
      StaticAlignmentModalVisual: function () {
        return this.$store.getters.MethodConfigModalShow(this.preProcess, this.methodName)
      }
    },
    methods: {
      confirm: function () {
        try {
          let data = {
            rangeOffset: this.$refs.rangeOffset.getInputNumber(),
            startPoint: this.$refs.startPoint.getInputNumber(),
            totalPoints: this.$refs.totalPoints.getInputNumber(),
            referTrace: this.target.traces[this.$refs.referTraceIndex.getInputNumber() - this.target.traceRange[0]].samples,
            traces: this.target.traces.map(trace => trace.samples)
          }
          let filename = hash(data)
          let content = queryProcessData(this.preProcess,
            this.methodName,
            this.filenameHash,
            filename)
          if (content !== null) {
            // 如果找到经过该项处理的文件
            this.$store.commit('PaintLines', [
              this.target.filename,
              this.preProcess,
              this.methodName,
              content.traces
            ]) // 画图
            this.$store.commit('SetMethodConfigModalVisual',
              [this.preProcess, this.methodName, false])
          } else {
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
                  // 写入key5
                  content.keys = upperThis.target.traces.map(trace => trace.cryData)
                  // 存的返回的数据：用于下一次的查询
                  saveProcessData(upperThis.preProcess,
                    upperThis.methodName,
                    upperThis.filenameHash,
                    filename,
                    content)
                  // 存储返回的数据，用于攻击
                  saveProcessData(upperThis.preProcess,
                    upperThis.methodName,
                    upperThis.filenameHash,
                    upperThis.$store.state.interfaceConfig.recentFilename,
                    content
                  )
                  upperThis.$store.commit('SetMethodConfigModalVisual',
                    [upperThis.preProcess, upperThis.methodName, false])
                } else {
                  upperThis.$emit('error',
                    '网络|服务器内部错误\n' + error + '\n' + response.statusCode)
                  upperThis.$store.commit('SetMethodConfigModalVisual',
                    [upperThis.preProcess, upperThis.methodName, false])
                }
              })
          }
        } catch (e) {
          this.$emit('error', e.message)
          this.$store.commit('SetMethodConfigModalVisual',
            [this.preProcess, this.methodName, false])
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
