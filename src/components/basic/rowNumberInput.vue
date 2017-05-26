<style>
  .header4-text {
    font-size: 14px;
    font-weight: bold;
    text-align: center;
  }
</style>

<template>
  <Row>
    <i-col :span="leftSpan">
        <span class="header4-text">
          {{ illustrate }}
        </span>
    </i-col>
    <i-col :span="rightSpan">
      <Input-number :max="inputNumberRange[1]"
                    :min="inputNumberRange[0]"
                    v-model="inputNumberValue">
      </Input-number>
    </i-col>
  </Row>
</template>

<script>
  export default {
    data () {
      return {
        inputNumberValue: 0
      }
    },
    props: {
      leftSpan: {
        type: Number,
        default: 12
      },
      illustrate: {
        type: String,
        required: true
      },
      inputNumberRange: {
        type: Array,
        required: true
      }
    },
    computed: {
      rightSpan: function () {
        return 24 - this.leftSpan
      }
    },
    methods: {
      getInputNumber: function () {
        return this.inputNumberValue
      }
    }
  }
</script>
