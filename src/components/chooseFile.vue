<style>
  .input-file {
    width: 0px;
    height: 0px;
    opacity: 0;
    overflow: hidden;
    position: absolute;
    z-index: -1;
  }

  .input-file + label {
    font-size: 1.25em;
    font-weight: 700;
    color: white;
    background-color: black;
    display: inline-block;
  }
</style>

<template>
  <!-- 选择文件 -->
  <Dropdown style="margin-left: 20px"
            @on-click="chooseFileType">
    <Button type="primary">
      选择文件
      <Icon type="arrow-down-b"></Icon>
    </Button>

    <Dropdown-menu slot="list">
      <Dropdown-item name="trs">
        <b>trs</b>文件
      </Dropdown-item>
      <Dropdown-item name="txt">
        <b>txt</b>文件
      </Dropdown-item>
    </Dropdown-menu>
  </Dropdown>

</template>

<script>
  const {dialog} = require('electron').remote
  import { readHeader } from '../util/decode'
  import TraceData from '../util/traceData'
  const path = require('path')
  export default {
    methods: {
      /**
       * 选择文件类型
       * @param type
       */
      chooseFileType (type) {
        if (type === 'trs') {
          dialog.showOpenDialog({
            title: '选择文件',
            filters: [{name: type + '文件', extensions: type}],
            properties: ['openFile']
          }, (fileNames) => {
            if (fileNames === undefined) {
              console.log('没有选中文件')
            } else {
              let filename = fileNames[0] // 文件的完整路径
              let queryTarget = this.$store.getters.Target(filename)
              if (queryTarget.length !== 0) {
                this.$Modal.info({
                  title: '提示',
                  content: '<p>该文件已经被打开，请勿打开重复的文件</p>'
                })
                return
              }
              this.$store.state.selectedTarget = readHeader(filename)
              this.$store.state.selectModalVisual = true
            }
          })
        } else if (type === 'txt') {
          dialog.showOpenDialog({
            title: '选择文件',
            filters: [{name: type + '文件', extensions: type}],
            properties: ['openFile', 'multiSelections'] // 允许多选
          }, (fileNames) => {
            if (fileNames === undefined) {
              console.log('没有选中文件')
            } else {
              if (fileNames.length !== 2) {
                dialog.showErrorBox('error', '打开txt文件需要打开两个文件')
                return
              }
              let waveFilename = null
              let roundKeyFilename = null
              for (let index in fileNames) {
                let filename = fileNames[index]
                let baseFilename = path.basename(filename)
                console.log(filename + ':' + baseFilename)
                if (baseFilename === 'roundKey.txt') {
                  roundKeyFilename = filename
                } else if (baseFilename === 'waves.txt') {
                  waveFilename = filename
                }
              }
              if (waveFilename === null || roundKeyFilename === null) {
                dialog.showErrorBox('error',
                  '打开的两个文件名称应该分别为\nwaves.txt\nroundKey.txt')
                return
              }
              let queryTarget = this.$store.getters.Target(waveFilename)
              if (queryTarget.length !== 0) {
                this.$Modal.info({
                  title: '提示',
                  content: '<p>该文件已经被打开，请勿打开重复的文件</p>'
                })
                return
              }
              let traceData = new TraceData()
              traceData.filename = waveFilename
              traceData.roundKeyFilename = roundKeyFilename
              traceData.traceNum = 2
              traceData.sampleNum = 50000
              this.$store.state.selectedTarget = traceData
              this.$store.state.selectModalVisual = true
            }
          })
        } else {
          // do nothing
        }
      }
    }
  }
</script>
