//
// Created by pj on 17-5-27.
//

#include <vector>
#include <string>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "Basic.h"
#include "parameter.h"
#include "poc.h"

int main(int argc, char *argv[]){
  auto body = string(argv[1]);

  string method_name = "POC";
  Json::Reader reader;

  Json::Value in_root;
  Json::Value out_root;
  out_root["align"] = method_name;
  vector<vector<double> > traces;
  if(reader.parse(body, in_root)){
    if(!Basic::checkParams(in_root, vector<string>{"originalPoints",
                                                   "referTrace",
                                                   "traces"})){
      out_root["traces"].append(Json::Value());
      out_root["message"].append("参数错误");
      cout << out_root.toStyledString() << endl;
      return 1;
    }
    /**
     * 设置参数
     */
    vector<double> refer_trace = Basic::ReadSingleTrace(in_root["referTrace"]);
    auto OriginalPoints = in_root["originalPoints"].asInt();
    Parameter *p = new Parameter();
    p->Align = QString::fromStdString(method_name);
    p->refer_trace = refer_trace;
    p->OriginalPoints = OriginalPoints;
    /**
     * 快速傅利叶变换
     */
    auto method = new POC(p);
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
    out_root["message"].append("内容解析错误");
    cout << out_root.toStyledString() << endl;
    return 1;
  }
}