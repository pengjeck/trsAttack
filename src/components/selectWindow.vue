<style>

  .header4-text {
    font-size: 14px;
    font-weight: bold;
    text-align: center;
  }

</style>

<template>
  <Modal v-model="visual" :closable="false" :mask-closable="false">
    <p slot="header" style="color:gray;text-align:center;font-size:20px;">
      <Icon type="information-circled"></Icon>
      <span>{{ selectedTarget['filename'] }}</span>
    </p>

    <!-- ---------------------- 配置内容 ---------------------- -->
    <div>
      <Row>
        <i-col span="8">
          <span class="header4-text">
            曲线选择(0-{{ selectedTarget['traceNum'] - 1}}):
          </span>
        </i-col>
        <i-col span="16">
          <Input-number
            :max="traceRange[1]"
            :min="0"
            v-model="traceRange[0]">
          </Input-number>
          到
          <Input-number
            :max="selectedTarget['traceNum'] - 1"
            :min="0"
            v-model="traceRange[1]">
          </Input-number>
        </i-col>
      </Row>
    </div>
    <div style="margin-top: 5px">
      <Row>
        <i-col span="8">
          <span class="header4-text">
            样本区间(0-{{ selectedTarget['sampleNum'] - 1}}):
          </span>
        </i-col>
        <i-col span="16">
          <Input-number
            :max="sampleRange[1]"
            :min="0"
            v-model="sampleRange[0]">
          </Input-number>
          到
          <Input-number
            :max="selectedTarget['sampleNum'] - 1"
            :min="1"
            v-model="sampleRange[1]">
          </Input-number>
        </i-col>
      </Row>
    </div>
    <div slot="footer">
      <Button icon="close-round" @click="closeModal">
        <span>取消</span>
      </Button>
      <Button type="primary"
              icon="checkmark-round"
              @click="selectConfirm">
        <span>确认</span>
      </Button>
    </div>
  </Modal>
</template>

<script>
  import InputNumber from '../../node_modules/iview/src/components/input-number/input-number'
  import Row from '../../node_modules/iview/src/components/grid/row'
  import ICol from '../../node_modules/iview/src/components/grid/col'
  const fs = require('fs')
  import TraceData from '../util/traceData'
  import SingleTrace from '../util/singleTrace'
  import { readMultiTrace } from '../util/decode'
  export default {
    components: {
      ICol,
      Row,
      InputNumber
    },
    computed: {
      selectedTarget: function () {
//        console.log(this.$store.getters.selectedTarget)
        return this.$store.getters.selectedTarget
      },
      visual: function () {
        return this.$store.state.selectModalVisual
      }
    },
    data () {
      return {
        traceRange: [0, 1],
        sampleRange: [0, 1]
      }
    },
    methods: {
      /**
       * 取消上传
       */
      closeModal () {
        this.$store.state.selectedTaraget = new TraceData()
        this.traceRange = [0, 1]
        this.sampleRange = [0, 1]
        this.$store.state.selectModalVisual = false
      },
      selectConfirm () {
        if (this.selectedTarget.GetShortFileName().split('.')[1] === 'txt') {
          // txt 文件
          let samples = fs.readFileSync(this.selectedTarget.filename, 'utf-8')
            .split('\n').map(line => {
              return line.split(' ').slice(this.sampleRange[0], this.sampleRange[1])
            })
          let roundKeys = fs.readFileSync(this.selectedTarget.roundKeyFilename, 'utf-8')
            .split('\n').map(line => {
              return line.split(' ')
            })
          let traces = [] // array<singleTarget>
          for (let i = 0; i < 2; i++) {
            let trace = new SingleTrace(samples[i].map(item => {
              return parseInt(item)
            }))
            trace.cryData = roundKeys[i].map(byte => parseInt('0x' + byte))
            trace.traceIndex = i
            traces.push(trace)
          }
          let target = this.$store.state.selectedTarget
          target.traces = traces
          target.traceRange = this.traceRange
          target.sampleRange = this.sampleRange
          target.show = true
          this.$store.state.activeTabName = target.filename
          this.$store.commit('PushTarget', target) // 提交，插入新的数据
          this.$nextTick(function () {
            this.$store.commit('PaintTarget', [
              'rowTrace', 'rowTrace', target
            ])
          })
          this.$store.state.selectedTarget = new TraceData()
          this.$store.state.selectModalVisual = false
        } else {
          // trs 文件
          let target = readMultiTrace(this.$store.state.selectedTarget,
            this.traceRange[0],
            this.traceRange[1],
            this.sampleRange[0],
            this.sampleRange[1])
          target.traceRange = this.traceRange
          target.sampleRange = this.sampleRange
          target.show = true
          this.$store.state.activeTabName = target.filename
          this.$store.commit('PushTarget', target) // 提交，插入新的数据
          this.$nextTick(function () {
            this.$store.commit('PaintTarget', [
              'rowTrace', 'rowTrace', target
            ])
          })
          this.$store.state.selectedTarget = new TraceData()
          this.$store.state.selectModalVisual = false
        }
      }
    }
  }
</script>
