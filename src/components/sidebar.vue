<style>
  .layout-menu-left {
    background: #464c5b;
  }

  .layout-logo-left {
    font-size: 20px;
    font-weight: bold;
    text-align: center;

    color: whitesmoke;
    width: 90%;
    height: 30px;
    background: #5b6270;
    border-radius: 3px;
    margin: 15px auto;
  }

</style>

<template>
  <Menu
    @on-select="handleProcessSwitch"
    :active-name="activeMenuName"
    theme="dark"
    width="auto"
    class="layout-menu-left">
    <div class="layout-logo-left">
      <Icon type="android-wifi" size="33"></Icon>
    </div>
    <Menu-item
      v-for="(process, processName) in processes"
      :name="processName"
      :key="process['id']">
      <Icon :type="process['iconType']" size="26"></Icon>
      <span class="layout-text">
        {{ process['name'] }}
      </span>
    </Menu-item>
  </Menu>
</template>

<script>
  //  import { mapGetters } from 'vuex'
  export default {
    computed: {
      processes () {
        return this.$store.getters.Processes
      },
      activeMenuName () {
        return this.$store.state.activeMenuName
      }
    },
    methods: {
      handleProcessSwitch (name) {
        this.$store.state.activeMenuName = name
        console.log(this.$store.state.activeMenuName)
      }
    }
  }
</script>
