const STORAGE_KEY = 'userId'
const USER_ID = '23543224'

export default {
  /**
   * 保存用户id
   */
  saveUserId () {
    window.localStorage.setItem(STORAGE_KEY, USER_ID)
  },
  /**
   * 获取用户id
   */
  fetchUserId () {
    let userId = window.localStorage.getItem(STORAGE_KEY)
    if (userId === null) {
      window.localStorage.setItem(STORAGE_KEY, USER_ID)
    }

    return window.localStorage.getItem(STORAGE_KEY)
  }
}
