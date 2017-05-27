//
// Created by pj on 17-5-26.
//

#include <string>
#include "jsoncpp/json/json.h"
#include "parameter.h"
#include <iostream>
#include "staticalignment_method.h"
#include "Basic.h"

using namespace std;

int main(int argc, char *argv[]){
  string body = string(argv[1]);

  string method_name = "StaticAlignment";
  Json::Reader reader;
  Json::Value in_root;
  Json::Value out_root;
  out_root["align"] = method_name;
  vector<vector<double> > traces;
  auto parse_out = reader.parse(body, in_root);
  if(parse_out){
    if(!Basic::checkParams(in_root, vector<string>{"rangeOffset",
                                                   "startPoint",
                                                   "totalPoints",
                                                   "referTrace",
                                                   "traces"})){
      out_root["traces"].append(Json::Value());
      out_root["message"].append("参数错误");
      cout << out_root.toStyledString() << endl; // 输出
      return 1;
    }
    /**
     * 设置参数
     */
    auto RangeOffset = in_root["rangeOffset"].asInt();
    auto Start_Point = in_root["startPoint"].asInt();
    auto TotalPoints = in_root["totalPoints"].asInt();
    vector<double> refer_trace = Basic::ReadSingleTrace(in_root["referTrace"]);

    Parameter *p = new Parameter();
    p->Align = QString::fromStdString(method_name);
    p->RangeOffset = RangeOffset;
    p->Start_Point = Start_Point;
    p->TotalPoints = TotalPoints;
    p->refer_trace = refer_trace;
    auto method = new StaticAlignment_Method(p);
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
    out_root["message"].append("内容解析失败");
    cout << out_root.toStyledString() << endl;
    return 1;
  }
}