<style>

</style>

<template>
  <Modal v-model="visible"  :closable="false" :mask-closable="false">
    <p slot="header" style="color:gray;text-align:center;font-size:20px;">
      <span>正在上传</span>
    </p>
    <div style="text-align:center;">
      <Icon type="load-a" size="32"></Icon>
    </div>

    <!-- footer -->
    <div slot="footer">
      <Button icon="ios-close-empty" @click="handleUploadCancel">
        取消上传
      </Button>
    </div>
  </Modal>
</template>

<script>
  export default {
    props: {
      visible: Boolean
    },
    data () {
      return {
      }
    },
    methods: {
      handleUploadCancel: function () {
        // 发送上传取消的信号
        this.$emit('uploadCancel')
      }
    }
  }
</script>
