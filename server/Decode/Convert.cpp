//
// Created by pj on 17-4-26.
//

#include "Convert.h"

long Convert::bytes2int(vector<char> bs){
  int len = int(bs.size());
  long sum = 0;
  for(int i = 0; i < len; ++i){
    sum += int(bs[i]) * pow(16.0, (len - i - 1) * 2);
  }
  return sum;
}

/*
 * 把一个bytes(char)数组转为string
 */
string Convert::bytes2string(vector<char> bs){
  string res(bs.begin(), bs.end());
  return res;
}

string Convert::bytes2binarystr(vector<char> bs){
  string res;
  unsigned char mask = 128;
  int len = int(bs.size());
  for(int i = 0; i < len; ++i){
    int t = int(bs[i]);
    for(int j = 0; j < 8; ++j){
      int out = ((t << j) & mask);
      if(out != 0){
        res += '1';
      }else{
        res += '0';
      }
    }
  }
  return res;
}

/*
 * 运用内存复制将bytes数组转为float，
 * 这里bytes的总的内存一定要和float内存相等，也就是4个bytes
 */
float Convert::bytes2float(char *bs, size_t size){
  float f;
  memcpy(&f, bs, size);
  return f;
}