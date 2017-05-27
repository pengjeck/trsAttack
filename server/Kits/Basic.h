//
// Created by pj on 17-5-27.
//

#ifndef PROJECT_BASIC_H
#define PROJECT_BASIC_H

#include "jsoncpp/json/json.h"
#include <vector>

using namespace std;

class Basic{
public:
  static vector<double> ReadSingleTrace(const Json::Value &root){
    vector<double> out;
    int sample_num = root.size();
    for(int i = 0; i < sample_num; i++){
      out.push_back(root[i].asDouble());
    }
    return out;
  }

  static vector<vector<double> > ReadTraces(const Json::Value &root){
    vector<vector<double> > out;

    Json::Value traces = root["traces"];
    int traces_num = traces.size();
    Json::Value samples = traces[0];
    int sample_num = samples.size();

    for(int i = 0; i < traces_num; i++){
      // size_t trace_len = traces[i].size();
      vector<double> trace;
      for(int j = 0; j < sample_num; j++){
        trace.push_back(traces[i][j].asDouble());
      }
      out.push_back(trace);
    }
    return out;
  }

  static bool checkParams(Json::Value const &root, vector<string> const &params){
    for(auto &&element: params){
      if(root[element].isNull()){
        return false;
      }
    }
    return true;
  }

  template<typename Iterable>
  static void Iterable2Json(Json::Value &value, Iterable const &cont){
    for(auto &&element: cont){
      value.append(element);
    }
  }
};


#endif //PROJECT_BASIC_H
