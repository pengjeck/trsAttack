/**
 * Created by pj on 17-4-18.
 */
import vis from 'vis'

/**
 * 只绘制曲线
 * @param myChart
 * @param lines
 * @param labelX
 * @param labelY
 * @param scaleX
 * @param scaleY
 * @param globalTitle
 */
function paintLines (myChart, lines, labelX, labelY, scaleX, scaleY, globalTitle) {
  if (lines.length === 0) {
    return
  }
  // 生成所有的x轴的数据
  let xAxisData = Array.from(new Array(lines[0].length), function (_, i) {
    return i
  })
  let seriesConfig = lines.map(function (line, i) {
    return {
      name: labelY + '#' + i.toString(),
      type: 'line',
      data: line,
      smooth: true,
      lineStyle: {
        normal: {
          width: 0.5
        }
      }
    }
  })

  myChart.setOption({
    title: {
      text: globalTitle
    },
    tooltip: {
      trigger: 'axis'
    },
    xAxis: {
      name: labelX,
      scale: scaleX,
      data: xAxisData
    },
    yAxis: {
      type: 'value',
      scale: scaleY,
      splitLine: {
        show: true
      }
    },
    dataZoom: [{
      type: 'inside',
      start: 0,
      end: 10
    }, {
      start: 0,
      end: 10,
      handleIcon: 'M10.7,11.9v-1.3H9.3v1.3c-4.9,0.3-8.8,4.4-8.8,9.4c0,5,3.9,9.1,8.8,9.4v1.3h1.3v-1.3c4.9-0.3,8.8-4.4,8.8-9.4C19.5,16.3,15.6,12.2,10.7,11.9z M13.3,24.4H6.7V23h6.6V24.4z M13.3,19.6H6.7v-1.4h6.6V19.6z',
      handleSize: '80%',
      handleStyle: {
        color: '#fff',
        shadowBlur: 3,
        shadowColor: 'rgba(0, 0, 0, 0.6)',
        shadowOffsetX: 2,
        shadowOffsetY: 2
      }
    }],
    toolbox: {
      left: 'center',
      feature: {
        dataZoom: {},
        restore: {},
        saveAsImage: {}
      }
    },
    series: seriesConfig
  })
}

/**
 * 回执多个SingleTraces
 * @param myChart
 * @param traces: singleTrace对象列表
 * @param labelX
 * @param labelY
 * @param scaleX
 * @param scaleY
 * @param globalTitle
 */
function paintTraces (myChart, traces, labelX, labelY, scaleX, scaleY, globalTitle) {
  if (traces.length === 0) {
    return
  }
  // 生成所有的x轴的数据
  let xAxisData = Array.from(new Array(traces[0].getSampleNum()), function (_, i) {
    return i + traces[0].sampleBegIndex
  })

  let seriesConfig = traces.map(function (item) {
    return {
      name: labelY + '#' + item.traceIndex.toString(),
      type: 'line',
      data: item.samples,
      smooth: true,
      lineStyle: {
        normal: {
          width: 0.5
        }
      }
    }
  })

  myChart.setOption({
    title: {
      text: globalTitle
    },
    tooltip: {
      trigger: 'axis'
    },
    xAxis: {
      name: labelX,
      scale: scaleX,
      data: xAxisData
    },
    yAxis: {
      type: 'value',
      scale: scaleY,
      splitLine: {
        show: true
      }
    },
    dataZoom: [{
      type: 'inside',
      start: 0,
      end: 10
    }, {
      start: 0,
      end: 10,
      handleIcon: 'M10.7,11.9v-1.3H9.3v1.3c-4.9,0.3-8.8,4.4-8.8,9.4c0,5,3.9,9.1,8.8,9.4v1.3h1.3v-1.3c4.9-0.3,8.8-4.4,8.8-9.4C19.5,16.3,15.6,12.2,10.7,11.9z M13.3,24.4H6.7V23h6.6V24.4z M13.3,19.6H6.7v-1.4h6.6V19.6z',
      handleSize: '80%',
      handleStyle: {
        color: '#fff',
        shadowBlur: 3,
        shadowColor: 'rgba(0, 0, 0, 0.6)',
        shadowOffsetX: 2,
        shadowOffsetY: 2
      }
    }],
    toolbox: {
      left: 'center',
      feature: {
        dataZoom: {},
        restore: {},
        saveAsImage: {}
      }
    },
    series: seriesConfig
  })
}

/**
 * 画彩带
 * @param myChart
 * @param ribbons: 二维数组
 * @param labelX
 * @param labelY
 * @param labelZ
 * @param globalTitle
 */
function paintRibbons (myChart, ribbons) {
  let ribbonsNum = 1
  try {
    ribbonsNum = ribbons.length
  } catch (e) {
    throw new RangeError('param ribbon should be 2 dim array')
  }

  if (ribbonsNum === 0) {
    throw new RangeError('ribbon num should > 1')
  }
  let ySum = ribbons[0].length

  let data = new vis.DataSet()
  // create some nice looking data with sin/cos
  let counter = 0
  for (let x = 0; x < ribbonsNum; x += 1) {
    for (let y = 0; y < ySum; y += 1) {
      let value = ribbons[x][y]
      data.add({id: counter++, x: x, y: y, z: value, style: value})
    }
  }

  // specify options
  let options = {
    width: myChart.clientWidth + 'px',
    height: myChart.clientHeight + 'px',
    style: 'surface',
    showPerspective: true,
    showGrid: true,
    showShadow: false,
    keepAspectRatio: true,
    verticalRatio: 0.5
  }
  /* eslint-disable no-new */
  new vis.Graph3d(myChart, data, options)
}
export { paintLines, paintTraces, paintRibbons }
