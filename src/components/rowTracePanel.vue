<style>
  .chart {
  min-height: 400px;
  width: 100%;
  }
</style>

<template>
  <div style="text-align: center">
    <Row>
      <i-col span="18">
        <div
          class="chart"
          :id="target.filename + '_' + rowTrace + '_' + rowTrace">
        </div>
      </i-col>
      <i-col span="6">
        <Table size="small" :columns="tableColumns" :data="targetInfo"></Table>
      </i-col>
   </Row>

  </div>
</template>


<script>
  import ICol from '../../node_modules/iview/src/components/grid/col'
  export default {
    components: {ICol},
    props: {
      target: {
        type: Object,
        required: true
      }
    },
    computed: {
      tableColumns: function () {
        return [
          {
            title: '属性',
            key: 'key'
          },
          {
            title: '属性值',
            key: 'value'
          }
        ]
      },
      targetInfo: function () {
        return [
          {
            key: '文件',
            value: this.target.filename
          },
          {
            key: '总trace数量',
            value: this.target.traceNum
          },
          {
            key: '总样本数量',
            value: this.target.sampleNum
          },
          {
            key: 'ScaleX',
            value: this.target.scaleX
          },
          {
            key: 'ScaleY',
            value: this.target.scaleY
          },
          {
            key: 'labelX',
            value: this.target.labelX
          },
          {
            key: 'labelY',
            value: this.target.labelY
          }
        ]
      }
    },
    methods: {},
    data () {
      return {
        rowTrace: 'rowTrace'
      }
    }
  }
</script>
