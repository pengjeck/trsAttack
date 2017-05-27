//
// Created by pj on 17-5-27.
//

#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "Basic.h"
#include "parameter.h"
#include "dtw.h"

using namespace std;

int main(int argc, char *argv[]){
  auto body = string(argv[1]);

  string method_name = "DTW";
  Json::Reader reader;

  Json::Value in_root;
  Json::Value out_root;
  out_root["Align"] = method_name;
  vector<vector<double> > traces;
  if(reader.parse(body, in_root)){
    if(!Basic::checkParams(in_root, vector<string>{"refer_trace",
                                                   "traces"})){
      out_root["traces"].append(Json::Value());
      cout << out_root.toStyledString() << endl;
      return 1;
    }
    /**
     * 设置参数
     */
    vector<double> refer_trace = Basic::ReadSingleTrace(in_root["refer_trace"]);

    Parameter *p = new Parameter();
    p->Align = QString::fromStdString(method_name);
    p->refer_trace = refer_trace;
    /**
     * 快速傅利叶变换
     */
    auto method = new dtw(p);
    Json::Value single_trace;

    traces = Basic::ReadTraces(in_root);
    auto iterator = traces.begin();
    for(; iterator != traces.end(); iterator++){
      single_trace.clear();
      Basic::Iterable2Json(single_trace, method->Align(*iterator));
      out_root["traces"].append(single_trace);
    }
    cout << out_root.toStyledString() << endl;
    return 0;
  }else{
    out_root["traces"].append(Json::Value());

    cout << out_root.toStyledString() << endl;
    // 返回不支持的媒体类型
    return 1;
  }
}

