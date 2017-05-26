/**
 * Created by pj on 17-5-24.
 */
const methodNames = {
  StaticAlignment: 'StaticAlignment',
  FFT: 'FFT',
  DTW: 'DTW',
  POC: 'POC'
}

export default function formatPostData (methodName, config) {
  if (methodName === methodNames.StaticAlignment) {
    // TODO: staticAlignment
  } else if (methodName === methodNames.FFT.name) {
    return {
      OriginalPoints: this.target.GetInSampleNum(),
      traces: this.target.traces.map(function (singleTrace) {
        return singleTrace.samples
      })
    }
  } else if (methodName === methodNames.DTW.name) {
    // TODO: dtw format
  } else if (methodName === methodNames.POC.name) {
    // TODO: poc format
  } else {
    throw new TypeError('the method do not supported until now!')
  }
}

