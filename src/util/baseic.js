/**
 * Created by pj on 17-5-24.
 */

/**
 * 判断一个数是不是2的n次方
 * @param x
 */
function is2Exp (x) {
  let include = [1, 2, 4, 8, 16, 32, 64, 128,
    256, 512, 1024, 2048, 4096, 8192, 16384,
    32768, 65536, 131072]
  return include.filter(i => i === x).length !== 0
}

export { is2Exp }
