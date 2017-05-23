<style>
  .chart {
    height: 100%;
    width: 100%;
  }

  .chart-init {
    height: 100%;
    width: 100%;
  }

  .chart-loading {
    height: 100%;
    width: 100%;
  }
</style>

<template>
  <Row type="flex" :gutter="16" style="height: 480px;">
    <i-col
      span="12"
      v-for="(methodValue, methodName) in process.methods"
      :key="methodName">
      <Card
        v-if="methodValue.charts[target.filename] !== undefined">
        <div
          :id="target.filename + '-' + preProcess + '-' + methodName"
          class="chart">
        </div>
      </Card>
      <Card
        v-else
        class="chart-init">
        <div style="text-align:center;">
          <Button type="ghost" icon="grid" shape="circle" size="large">
            {{ methodName }}
          </Button>
        </div>
      </Card>
    </i-col>
  </Row>
</template>


<!-- chart id： 命名格式为：
[文件名]-[处理过程]-[处理方法]  // 这个chart id 必须是全局唯一的
filename-process_name-process_method
 -->
<script>

  export default {
    computed: {
      process: function () {
        return this.$store.getters.Process(this.attack)
      },
      height: function () {
        return 400
      },
      target: function () {
        return this.$store.getters.Target(this.$store.state.activeTabName)
      }
    },
    watch: {
    },
    methods: {
    },
    data () {
      return {
        attack: 'attack'
      }
    }
  }
</script>
