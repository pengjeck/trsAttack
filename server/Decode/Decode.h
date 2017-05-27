//
// Created by pj on 17-3-31.
//

#ifndef SOURCE_CODE_DECODE_H
#define SOURCE_CODE_DECODE_H

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "Convert.h"

using namespace std;

class SingleTrace{
private:
  vector<float> _samples;

public:
  string title;
  string cry_data;

  // region constructor

  /**
   * 默认构造函数
   */
  SingleTrace(){
    this->title = "";
    this->cry_data = "";
    this->_samples.clear();
  }

  SingleTrace(string title, string cry_data, vector<float> samples){
    this->title = title;
    this->cry_data = cry_data;
    this->_samples = samples;
  }

  // endregion

  // region public tools

  const string &getTitle() const{
    return title;
  }

  const string &getCry_data() const{
    return cry_data;
  }

  const vector<float> &getSamples() const{
    return _samples;
  }

  /**
   * 这里加上const是为啦防止对非static变量的修改。
   * @param out
   */
  void getDoubleSamples(vector<double> &out, int beg, int end){
    if(beg > end){
      out.clear();
      return;
    }

    vector<float>::iterator first = _samples.begin() + beg;
    vector<float>::iterator after = _samples.end() + end;

    for(; first != after; first++){
      auto tmp = (double) *first;
      out.push_back(tmp);
    }
  }

  const void push_sample(float sample_data){
    this->_samples.push_back(sample_data);
  }

  // endregion

  // region override

  friend ostream &operator<<(ostream &os, const SingleTrace &singleTrace){
    for(int i = 0; i < 5; i++){
      os << singleTrace._samples[i] << '\t';
    }
    os << endl;
    return os;
  }
  // endregion

};

class TrsHeader{
private:
public:

  // region file title
  int trace_num = 0;
  int sample_num = 0;
  /*
   * integer or float:
   *     true: integer
   *     false: float
  */
  bool sample_type = true;
  int cry_data_len = 0;

  /*
   * 1 / 2 / 4
   */
  int sample_data_len = 1;
  int title_space_len = 0;
  string global_title;
  string label_x, label_y;
  float scale_x = 0, scale_y = 0;
  int x_offset = 0;
  string description;

  // endregion

  long f_header_len;

  TrsHeader(){};

  // method
  int trace_total_len(){
    return (this->title_space_len +
            this->cry_data_len +
            (this->sample_data_len * this->sample_num));
  }
};

class Decode{
private:
  static map<int, string> info_map(string mapfile = "/home/pj/pro/secure/trs/data/table.txt");

public:
  // region write out file
  static void gen_info(ifstream &fs,
                       int &len_cry_data,
                       int &num_traces,
                       int &num_sample_per_traces,
                       int &sample_len,
                       bool &sample_type,
                       int &title_space,
                       string info_txt = "/home/pj/pro/secure/trs/out/info.txt");

  static void read_content(ifstream &fs,
                           int len_cry_data, int num_traces,
                           int num_sample_per_traces, int sample_len,
                           bool sample_type = true,
                           int title_space = 0,
                           string wave_text = "/home/pj/pro/secure/trs/out/wave.txt",
                           string data_text = "/home/pj/pro/secure/trs/out/data.txt");

  // endregion write out file
  static TrsHeader read_header(ifstream &fs);

  SingleTrace read_single_trace_int(ifstream &fs,
                                    TrsHeader header,
                                    int index);

  SingleTrace read_single_trace_float(ifstream &fs,
                                      TrsHeader header,
                                      int index);


  vector<SingleTrace> read_multi_trace(ifstream &fs, TrsHeader &header,
                                       int beg_index, int end_index);

};

#endif //SOURCE_CODE_DECODE_H
