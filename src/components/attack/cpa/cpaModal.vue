<style>
  .header4-text {
    font-size: 14px;
    font-weight: bold;
    text-align: center;
  }
</style>

<template>
  <div>
    <Modal
      :closable="false"
      :mask-closable="false"
      v-model="StaticAlignmentModalVisual"
      title="请选择预处理方法：">
      <Select v-model="preProcessMethodName" style="width:200px">
        <!-- 对齐 -->
        <Option-group label="alignment">
          <Option v-for="item in alignmentMethodList" :value="item.value" :key="item">
            {{ item.label }}
          </Option>
        </Option-group>
        <!-- location -->
        <Option-group label="location">
          <Option v-for="item in locationMethodList" :value="item.value" :key="item">
            {{ item.label }}
          </Option>
        </Option-group>
      </Select>
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
  </div>
</template>

<script>
  import rowNumberInput from '../../basic/rowNumberInput.vue'
  let request = require('request')
  import { HOST } from '../../../util/localConfig'
  const {dialog} = require('electron').remote
  import { urlAddSubPath } from '../../../util/url'
  import { queryProcessData, saveProcessData } from '../../../util/opFile'
  import hash from 'object-hash'
  export default {
    components: {
      rowNumberInput
    },
    data () {
      return {
        preProcess: 'preProcess',
        attack: 'attack',
        preProcessMethodName: '',
        methodName: 'CPA',
        alignmentMethodList: [
          {
            value: 'staticAlignment',
            label: 'staticAlignment'
          },
          {
            value: 'FFT',
            label: 'FFT'
          },
          {
            value: 'POC',
            label: 'POC'
          },
          {
            value: 'DTW',
            label: 'DTW'
          }
        ],
        locationMethodList: []
      }
    },
    computed: {
      target: function () {
        try {
          return this.$store.getters.Target(this.$store.state.activeTabName)[0]
        } catch (e) {
          dialog.showErrorBox('error', '内部错误')
        }
      },
      filenameHash: function () {
        return hash(this.$store.state.activeTabName)
      },
      filename: function () {
        return this.$store.state.activeTabName
      },
      // 查找是否可见
      StaticAlignmentModalVisual: function () {
        return this.$store.getters.MethodConfigModalShow(this.attack,
          this.methodName)
      }
    },
    methods: {
      confirm: function () {
        try {
          let recentFilename = this.$store.state.interfaceConfig.recentFilename
          let content = queryProcessData(this.preProcess,
            this.methodName,
            this.filenameHash,
            recentFilename)   // 获取到相应的文件
          if (content !== null) {
            // 如果找到经过该项处理的文件, 开始执行攻击方法
            // content就是经过预处理之后的文件
            let data = {
              points: content.traces[0].length,
              waves: content.traces.length,
              addRoundKey: content.keys,
              traces: content.traces
            }
            let attackedFilename = hash(data)
            let attackedContent = queryProcessData(this.attack,
              this.methodName,
              this.filenameHash,
              attackedFilename)
            if (attackedContent !== null) {
              this.$emit('success', [
                this.filename,
                this.attack,
                this.methodName,
                attackedContent
              ]) // 发送给主进程
            } else {
              let url = urlAddSubPath(HOST, this.attack)
              url = urlAddSubPath(url, 'analysis')
              url = urlAddSubPath(url, this.methodName)
              let options = {
                url: url,
                json: JSON.stringify(data)
              }
              let upperThis = this
              request.post(options, function (error, response, body) {
                if (!error && response.statusCode === 200) {
                  let attackedContent = JSON.parse(body)
                  // 存储处理之后的数据
                  saveProcessData(upperThis.attack,
                    upperThis.methodName,
                    upperThis.filenameHash,
                    hash(data),
                    attackedContent)
                  upperThis.$emit('success', [
//                    upperThis.filename,
//                    upperThis.attack,
//                    upperThis.methodName,
                    attackedContent
                  ])
                } else {
                  upperThis.$emit('error',
                    '网络|服务器内部错误\n' + error + '\n' + response.statusCode)
                  upperThis.$store.commit('SetMethodConfigModalVisual',
                    [upperThis.preProcess, upperThis.methodName, false])
                }
              })
              this.$store.commit('SetMethodConfigModalVisual',
                [this.preProcess, this.methodName, false])
            }
          } else {
            // 没有找到相应的文件，说明在此前没有执行相应的操作
            this.$Message.info('请执行预处理操作:' + this.preProcessMethodName)
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
