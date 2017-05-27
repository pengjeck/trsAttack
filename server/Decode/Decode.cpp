//
// Created by pj on 17-3-31.
//

#include "Decode.h"

// region private method

/*
 * 函数主要是为了从int中得到tag所代表的message
 */
map<int, string> Decode::info_map(string mapfile){
  map<int, string> res;
  ifstream f;
  string line;
  f.open(mapfile);
  bool flag = false;
  int tag = 0;
  while(getline(f, line)){
    if(flag){
      // 读入message
      res.insert(std::pair<int, string>(tag, line));
      flag = false;
    }else{
      // 读入tag
      tag = stoi(line);
      flag = true;
    }
  }
  return res;
};


// endregion private method


// region gen out trs file

void Decode::gen_info(ifstream &fs,
                      int &len_cry_data,
                      int &num_traces,
                      int &num_sample_per_traces,
                      int &sample_len,
                      bool &sample_type,
                      int &title_space,
                      string info_txt){
  map<int, string> tag_info = info_map();
  int size = 1;
  ofstream os;
  os.open(info_txt);
  title_space = 0;
  /*
   * state 在这里表明处理字符时的状态。
   *  =0 正在处理tag
   *  =1 正在处理length
   *  =2 正在处理内容
   */
  int state = 0, tag = 0;
  string info;
  while(true){
    char *data = new char[size];
    if(state == 0){
      if(fs.read(data, 1)){
        tag = int(data[0]);
        if(tag == 95){
          fs.read(data, 1);
          if(int(data[0]) == 0){
            break;
          }else{
            int p = int(fs.tellg());
            fs.seekg(p - 1);
          }
        }
        size = 1;
        state = 1;
        info = tag_info[tag];
      }else{
        break;
      }
    }else if(state == 1){
      fs.read(data, size);
      int length = int(data[0]);
      size = length;
      state = 2;
    }else{
      if(fs.read(data, size)){
        if(tag == 65 || tag == 66 || tag == 68 || tag == 69){
          // convert to int;
          reverse(data, &data[size]);
          vector<char> in(data, &data[size]);
          long out = Convert::bytes2int(in);
          os << info << ":" << out << endl;
          //
          if(tag == 68){
            // get crypto data len.
            len_cry_data = int(out);
          }else if(tag == 65){
            // get trace number;
            num_traces = int(out);
          }else if(tag == 66){
            // get number of sample per traces.
            num_sample_per_traces = int(out);
          }else if(tag == 69){
            title_space = int(out);
          }
        }else if(tag == 70 || tag == 71 || tag == 73 || tag == 74){
          // convert to string
          vector<char> in(data, &data[size]);
          string out = Convert::bytes2string(in);
          os << info << ":" << out << endl;
        }else if(tag == 67){
          // convert to binary string
          vector<char> in;
          in.push_back(data[0]);
          string out = Convert::bytes2binarystr(in);
          os << info << ":" << out << endl;

          sample_type = out[3] != '1';
          if(out[7] == '1'){
            sample_len = 1;
          }else if(out[6] == '1'){
            sample_len = 2;
          }else if(out[5] == '1'){
            sample_len = 4;
          }

        }else if(tag == 75 || tag == 76){
          // convert to float
          // reverse(data, &data[size]);
          float f = Convert::bytes2float(data);
          os << info << ":" << f << endl;
        }else{

        }
        state = 0;
        size = 1;
      }else{
        break;
      }
    }
  }
  os.close();
  return;
}


/*
 * sample_type:说的是采样数据的类型，
 *  true: integer
 *  false: float
 */
void Decode::read_content(ifstream &fs,
                          int len_cry_data, int num_traces,
                          int num_sample_per_traces, int sample_len,
                          bool sample_type,
                          int title_space,
                          string wave_text,
                          string data_text){
  ofstream wave_os, data_os;
  wave_os.open(wave_text);
  data_os.open(data_text);

  char *cry_data = new char[len_cry_data];
  char *title = new char[title_space];
  for(int i = 0; i < num_traces; ++i){
    if(title_space > 0){
      fs.read(title, title_space);
    }

    fs.read(cry_data, len_cry_data);
    string cry_data_str(cry_data, &cry_data[len_cry_data]);
    data_os << cry_data_str << endl;

    char *sample_data = new char[sample_len];
    for(int j = 0; j < num_sample_per_traces; ++j){
      fs.read(sample_data, sample_len);
      reverse(sample_data, &sample_data[sample_len]);
      vector<char> sample_data_vec(sample_data, &sample_data[sample_len]);
      if(sample_type){
        // integer
        long out = Convert::bytes2int(sample_data_vec);
        wave_os << out << " ";
      }else{
        // float
        float f = Convert::bytes2float(sample_data, size_t(sample_len));
        wave_os << f << " ";
      }
    }
    wave_os << endl;
  }
  wave_os.close();
  data_os.close();
}

// endregion


// region op in memory

TrsHeader Decode::read_header(ifstream &fs){
  TrsHeader header;
  map<int, string> tag_info = info_map();
  int size = 1;
//  ofstream os;
//  os.open(info_txt);
  header.title_space_len = 0;

  /*
   * state 在这里表明处理字符时的状态。
   *  =0 正在处理tag
   *  =1 正在处理length
   *  =2 正在处理内容
   */
  int state = 0, tag = 0;
  string info;
  while(true){
    char *data = new char[size];
    if(state == 0){
      if(fs.read(data, 1)){
        tag = int(data[0]);

        /*
         * 判断结束
         */
        if(tag == 95){
          fs.read(data, 1);
          if(int(data[0]) == 0){
            break;
          }else{
            int p = int(fs.tellg());
            fs.seekg(p - 1);
          }
        }

        size = 1;
        state = 1;
        info = tag_info[tag];
      }else{
        break;
      }
    }else if(state == 1){
      fs.read(data, size);
      int length = int(data[0]);
      size = length;
      state = 2;
    }else{
      if(fs.read(data, size)){
        if(tag == 65 || tag == 66 || tag == 68 || tag == 69 || tag == 72){
          /*
           * convert to int;
           */
          reverse(data, &data[size]);
          vector<char> in(data, &data[size]);
          int out = int(Convert::bytes2int(in));
          switch(tag){
            case 65:
              header.trace_num = out;
              break;
            case 66:
              header.sample_num = out;
              break;
            case 68:
              header.cry_data_len = out;
              break;
            case 69:
              header.title_space_len = out;
              break;
            case 72:
              header.x_offset = out;
              break;
          }
        }else if(tag == 70 || tag == 71 || tag == 73 || tag == 74){
          /*
           * convert to string
           */
          vector<char> in(data, &data[size]);
          string out = Convert::bytes2string(in);
          switch(tag){
            case 70:
              header.global_title = out;
              break;
            case 71:
              header.description = out;
              break;
            case 73:
              header.label_x = out;
              break;
            case 74:
              header.label_y = out;
              break;
            default:;
          }
        }else if(tag == 67){
          /*
           * convert to binary string
           */
          vector<char> in;
          in.push_back(data[0]);
          string out = Convert::bytes2binarystr(in);
          // os << info << ":" << out << endl;

          header.sample_type = out[3] != '1';
          if(out[7] == '1'){
            header.sample_data_len = 1;
          }else if(out[6] == '1'){
            header.sample_data_len = 2;
          }else if(out[5] == '1'){
            header.sample_data_len = 4;
          }

        }else if(tag == 75 || tag == 76){
          /*
           * convert to float
           */
          float f = Convert::bytes2float(data);
          switch(tag){
            case 75:
              header.scale_x = f;
              break;
            case 76:
              header.scale_y = f;
              break;
            default:;
          }
        }else{
          // 77 | 78
        }
        state = 0;
        size = 1;
      }else{
        break;
      }
    }
  }
  header.f_header_len = fs.tellg();

  return header;
}

/*
 * 读取某一个index的header
 */
SingleTrace Decode::read_single_trace_int(ifstream &fs,
                                          TrsHeader header,
                                          int index){
  long seek_p = header.f_header_len + header.trace_total_len() * index;
  fs.seekg(seek_p);
  char *title = new char[header.title_space_len];
  char *cry_data = new char[header.cry_data_len];
  fs.read(title, header.title_space_len);
  fs.read(cry_data, header.cry_data_len);
  string title_str(title);
  string cry_data_str(cry_data);

  char *tmp_data = new char[header.sample_data_len];
  /*
   * integer
   */
  SingleTrace trace;
  for(int i = 0; i < header.sample_num; ++i){
    fs.read(tmp_data, header.sample_data_len);
    vector<char> in(tmp_data, &tmp_data[header.sample_data_len]);
    float out = Convert::bytes2int(in) * header.scale_y;
    trace.push_sample(out);
  }
  trace.title = title_str;
  trace.cry_data = cry_data_str;
  return trace;
}

SingleTrace Decode::read_single_trace_float(ifstream &fs,
                                            TrsHeader header,
                                            int index){
  long seek_p = header.f_header_len + header.trace_total_len() * index;
  fs.seekg(seek_p);
  char *title = new char[header.title_space_len];
  char *cry_data = new char[header.cry_data_len];
  fs.read(title, header.title_space_len);
  fs.read(cry_data, header.cry_data_len);
  string title_str(title);
  string cry_data_str(cry_data);

  char *tmp_data = new char[header.sample_data_len];
  /*
   * integer
   */
  SingleTrace trace;
  for(int i = 0; i < header.sample_num; ++i){
    fs.read(tmp_data, header.sample_data_len);
    // vector<char> in(tmp_data, &tmp_data[header.sample_data_len]);
    float out = Convert::bytes2float(tmp_data) * header.scale_y;
    trace.push_sample(out);
  }
  trace.title = title_str;
  trace.cry_data = cry_data_str;
  return trace;
}


vector<SingleTrace> Decode::read_multi_trace(ifstream &fs, TrsHeader &header,
                                             int beg_index, int end_index){
  long seek_p = header.f_header_len + header.trace_total_len() * beg_index;
  fs.seekg(seek_p);
  char *title = new char[header.title_space_len];
  char *cry_data = new char[header.cry_data_len];
  fs.read(title, header.title_space_len);
  fs.read(cry_data, header.cry_data_len);
  string title_str(title);
  string cry_data_str(cry_data);

  char *tmp_data = new char[header.sample_data_len];
  /*
   * integer
   */
  vector<SingleTrace> traces;
  if(header.sample_type){
    for(int i = beg_index; i < end_index; i++){
      SingleTrace trace;
      for(int j = 0; j < header.sample_num; ++j){
        fs.read(tmp_data, header.sample_data_len);
        vector<char> in(tmp_data, &tmp_data[header.sample_data_len]);
        float out = float(Convert::bytes2int(in)) * header.scale_y;
        trace.push_sample(out);
      }
      trace.title = title_str;
      trace.cry_data = cry_data_str;
      traces.push_back(trace);
    }
    return traces;
  }else{
    for(int i = beg_index; i < end_index; i++){
      SingleTrace trace;
      for(int j = 0; j < header.sample_num; ++j){
        fs.read(tmp_data, header.sample_data_len);
        // vector<char> in(tmp_data, &tmp_data[header.sample_data_len]);
        float out = Convert::bytes2float(tmp_data) * header.scale_y;
        trace.push_sample(out);
      }
      trace.title = title_str;
      trace.cry_data = cry_data_str;
      traces.push_back(trace);
    }
    return traces;
  }
}



// endregion op in memory