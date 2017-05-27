<style>
  .tab-pane-content {
    /*margin: 5px;*/
    background: #f5f7f9;
    width: 100%;
    overflow: hidden;
    /*background: #fff;*/
  }

  .fill {
    height: 100%;
    width: 100%;
  }
</style>

<template>
  <div>
    <Tabs v-model="selectFileName"
          type="card"
          style="margin-bottom: 0"
          closable
          @on-tab-remove="handleTabRemove">
      <Tab-pane
        v-for="target in targets"
        v-if="target['show']"
        :value="target['filename']"
        :key="target['filename']"
        :label="target.GetShortFileName()"
        :name="target['filename']"
        class="tab-pane-content"
        :style="{height: tabPanelHeight+'px'}">
        <!-- >>>>>>>>>>> 页面内容 <<<<<<<<<<<< -->
        <Carousel
          @on-change="handleCarouselChange"
          v-model="processIndex"
          arrow="never"
          dots="none">
          <!-- 原始曲线 -->
          <Carousel-item>
            <row-trace-panel
              :target="target" class="fill">
            </row-trace-panel>
          </Carousel-item>

          <!-- 预处[先只考虑只有四种预处理的情况] -->
          <Carousel-item>
            <pre-process-panel></pre-process-panel>
          </Carousel-item>

          <!-- 攻击 -->
          <Carousel-item>
            <attack-panel>
            </attack-panel>
          </Carousel-item>

          <!-- 评价 -->
          <Carousel-item>
            <assess-panel>
            </assess-panel>
          </Carousel-item>

          <!-- 生成报告 -->
          <Carousel-item>
            <report-panel>
            </report-panel>
            <div>生成报告</div>
          </Carousel-item>
        </Carousel>

      </Tab-pane>
    </Tabs>
  </div>
</template>


<script>
  import rowTracePanel from './rowTracePanel.vue'
  import preProcessPanel from './preProcess/preProcessPanel.vue'
  import attackPanel from './attack/attackPanel.vue'
  import assessPanel from './assess/assessPanel.vue'
  import reportPanel from './reportPanel.vue'
  import Tabs from '../../node_modules/iview/src/components/tabs/tabs'
  import TabPane from '../../node_modules/iview/src/components/tabs/pane'
  import Row from '../../node_modules/iview/src/components/grid/row'
  import ICol from '../../node_modules/iview/src/components/grid/col'
  //  const testTraceData = require('../store/modules/testTarget.json')

  export default {
    components: {
      ICol,
      Row,
      TabPane,
      Tabs,
      rowTracePanel,
      preProcessPanel,
      attackPanel,
      assessPanel,
      reportPanel
    },
    computed: {
      tabPanelHeight () {
        return this.$store.state.interfaceConfig.appHeight
      },
      selectFileName () {
        return this.$store.state.activeTabName
      },
      targets () {
        return this.$store.getters.AllTarget
      },
      processIndex () {
        return this.$store.getters.ProcessIndex(this.$store.state.activeMenuName)
      }
    },
    methods: {
      handleTabRemove: function (filename) {
        this.$store.commit('RemoveTarget', filename)
        this.$store.commit('DeleteChartsWithFiles', filename)
        this.$nextTick(function () {
          if (this.targets.length === 0) {
            this.$store.state.activeTabName = null
          } else {
            this.$store.state.activeTabName = this.targets[0].filename
          }
        })
      },
      handleCarouselChange: function (oldValue, value) {
        this.$store.state.activeMenuName = this.$store.getters.ProcessNameWithIndex(value)
      }
    }
  }
</script>
