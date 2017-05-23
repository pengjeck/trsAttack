/**
 * Created by pj on 17-5-17.
 */


let urlAddParam = (url, key, value) => {
  let splitChar = '?'
  if (url.indexOf('?') !== -1) {
    // 已经有参数了
    splitChar = '&'
  }
  url += splitChar + key + '=' + value
  return url
}
/**
 * 添加子路径
 **/
let urlAddSubPath = (url, subPath) => {
  if (url.indexOf('?') !== -1) {
    throw new SyntaxError('添加的url中不应该有参数')
  }
  url += '/' + subPath
  return url
}
