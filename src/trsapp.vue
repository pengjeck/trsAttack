<style>
  .layout {
    border: 1px solid #d7dde4;
    background: #f5f7f9;
    position: relative;
    border-radius: 4px;
    overflow: hidden;
  }

  .layout-copy {
    text-align: center;
    padding: 10px 0 20px;
    color: #9ea7b4;
  }

  .layout-header {
    height: 45px;
    background: #fff;
    box-shadow: 0 1px 1px rgba(0, 0, 0, .1);
  }

  .layout-header-text {
    white-space: nowrap;
    text-overflow: ellipsis;
    font-size: 20px;
    font-weight: bold;
    text-align: center;
  }

  .layout-ceiling-main a {
    color: #9ba7b5;
  }

</style>

<template>
  <div class="layout">
    <Row type="flex">
      <!-- ---------------------------- 侧边栏 -------------------------- -->
      <i-col span="3" class="layout-menu-left">
        <sidebar></sidebar>
      </i-col>

      <!-- -------------------------- 内容部分 -------------------------- -->
      <i-col span="21">

        <!-- ------------------------ 头部 ------------------------------ -->
        <Row>
          <div class="layout-header">
            <div style="padding: 5px">
              <i-col span="21">
                <div class="layout-header-text">
                  <span>在线分析平台</span>
                </div>
              </i-col>

              <!--上传文件-->
              <i-col span="3">
                <choose-file></choose-file>
              </i-col>
            </div>
          </div>
        </Row>

        <!-- -------------------------- 文件面板 -------------------------- -->
        <i-col span="24">
          <file-tabs :style="{height: appHeight + 'px'}"></file-tabs>
        </i-col>

        <!-- -------------------------- 版权信息 -------------------------- -->
        <i-col span="24">
          <div class="layout-copy">
            2011-2016 &copy; PJZero
          </div>
        </i-col>
      </i-col>
    </Row>

    <selectWindow></selectWindow>
  </div>
</template>


<script>
  // ------------import components------------
  import selectWindow from './components/selectWindow.vue'
  import chooseFile from './components/chooseFile.vue'
  import sidebar from './components/sidebar.vue'
  import fileTabs from './components/fileTabs.vue'
  // ------------import utils ----------------
  export default {
    components: {
      selectWindow,
      chooseFile,
      sidebar,
      fileTabs
    },
    methods: {},
    computed: {
      appHeight () {
        return this.$store.state.interfaceConfig.appMinHeight
      }
    },
    created: function () {
//      setInterval(() => {
//        for (let process in this.processes) {
//          if (process['methods'] === null || process['methods'] === undefined) {
//            break
//          }
//          for (let method of process['methods']) {
//            if (method['charts'] === null || method['charts'] === undefined) {
//              break
//            }
//            for (let file in method['charts']) {
//              method['charts'][file].resize()
//            }
//          }
//        }
//      }, 2000)
    }
  }
</script>
