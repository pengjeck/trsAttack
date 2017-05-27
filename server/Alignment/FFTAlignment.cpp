//
// Created by pj on 17-5-27.
//

#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "Basic.h"
#include "parameter.h"
#include "fft_method.h"

using namespace std;

int main(int argc, char *argv[]){
  auto body = string(argv[1]);

  string method_name = "FFT";
  Json::Reader reader;

  Json::Value in_root;
  Json::Value out_root;
  out_root["align"] = method_name;
  vector<vector<double> > traces;
  if(reader.parse(body, in_root)){
    if(!Basic::checkParams(in_root, vector<string>{"originalPoints", "traces"})){
      out_root["traces"].append(Json::Value());
      out_root["message"].append("参数错误");
      cout << out_root.toStyledString() << endl;
      return 1;
    }

    auto originalPoints = in_root["originalPoints"].asInt();

    traces = Basic::ReadTraces(in_root);
    auto iterator = traces.begin();

    /**
     * 设置参数
     */
    Parameter *p = new Parameter();
    p->Align = QString::fromStdString(method_name);
    p->OriginalPoints = originalPoints;

    /**
     * 快速傅利叶变换
     */
    auto fft_method = new FFT_Method(p);
    Json::Value single_trace;
    for(; iterator != traces.end(); iterator++){
      single_trace.clear();
      Basic::Iterable2Json(single_trace, fft_method->Align(*iterator));
      out_root["traces"].append(single_trace);
    }
    cout << out_root.toStyledString() << endl;
    return 0;
  }else{
    out_root["traces"].append(Json::Value());
    out_root["message"].append("内容解析错误");
    // 返回不支持的媒体类型
    cout << out_root.toStyledString() << endl;
    return 1;
  }
}