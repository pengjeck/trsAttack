//
// Created by pj on 17-4-26.
//

#ifndef PROPROCESS_CONVERT_H
#define PROPROCESS_CONVERT_H

#include <vector>
#include <cmath>
#include <string>
#include <cstring>

//#include <algorithm>

using namespace std;


class Convert{
public:
  static long bytes2int(vector<char> bs);

  static string bytes2string(vector<char> bs);

  static string bytes2binarystr(vector<char> bs);

  static float bytes2float(char *bs, size_t size = 4);
};


#endif //PROPROCESS_CONVERT_H
