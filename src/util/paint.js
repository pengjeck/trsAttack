/**
 * Created by pj on 17-4-18.
 */

/**
 * ps: 为什么这里不直接用target（traceData）来囊括所有数据参数?
 * 是因为如果函数的功能只是画曲线，那么其实它并不需要那么多的数据。
 * @param myChart
 * @param traces
 * @param labelX
 * @param labelY
 * @param scaleX
 * @param scaleY
 * @param globalTitle
 */
function paintLines (myChart, traces, labelX, labelY, scaleX, scaleY, globalTitle) {
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

export default paintLines
