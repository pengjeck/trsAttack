#include "aes.h"


AES::AES(Parameter *parameter){
  this->IsValue = parameter->IsValueBuild;
  this->SBoxLength = parameter->SBoxLength;
  this->HM00 = parameter->HM00;
  this->HM01 = parameter->HM01;
  this->Model = parameter->Model;
}

/*参数说明：
 * IsValue：是否根据值建立模板
 * SBoxLength：2的子密钥比特数次幂
 * HM00：泄漏点1
 * HM01：泄漏点2
 * Model：功耗模型
 * */
const unsigned int AES::HM[256] =
    {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4,
        5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5,
        5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4,
        5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6,
        5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4,
        5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5,
        5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4,
        5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7,
        5, 6, 6, 7, 6, 7, 7, 8
    };

const QString AES::S_box[256] =
    {
        "63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76",
        "ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0",
        "b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15",
        "04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75",
        "09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84",
        "53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf",
        "d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8",
        "51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2",
        "cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73",
        "60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db",
        "e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79",
        "e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08",
        "ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a",
        "70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e",
        "e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df",
        "8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"
    };

/*
 * 未知密钥下计算中间值
 * 一条明文对应256个中间值
 * */
vector<int> AES::NoneProfileMiddle(QString plain_s, int SNum){
  int firststate, secondstate;
  bool ok;
  vector<int> middle_subkey;
  middle_subkey.resize(this->SBoxLength, 0);
  QString tem = plain_s.mid(SNum * 3, 2);
  int plain_int = tem.toInt(&ok, 16);
  for(int i = 0; i < this->SBoxLength; i++){
    int middle_tmp = plain_int ^i;
    int sboxmiddle = S_box[middle_tmp].toInt(&ok, 16);
    if(this->HM00 == 0)
      firststate = plain_int;
    if(this->HM00 == 1)
      firststate = middle_tmp;
    if(this->HM00 == 2)
      firststate = sboxmiddle;
    if(this->HM01 == 1)
      secondstate = middle_tmp;
    if(this->HM01 == 2)
      secondstate = sboxmiddle;
    if(this->Model == "HanMing Weight"){
      if(this->IsValue)
        middle_subkey[i] = firststate;
      else
        middle_subkey[i] = HM[firststate];
    }else{
      if(this->IsValue)
        middle_subkey[i] = firststate ^ secondstate;
      else
        middle_subkey[i] = HM[firststate ^ secondstate];
    }
  }
  return middle_subkey;
}

/*
 * 已知密钥下计算中间值
 * 一条明文对应一个中间值
 * */
int AES::ProfileMiddle(QString plain_s, int correctkey, int SNum){
  int firststate, secondstate;
  int middle_subkey;
  bool ok;
  QString tem = plain_s.mid(SNum * 3, 2);
  int plain_int = tem.toInt(&ok, 16);//Integer.parseInt(plain_s, 16);
  int middle_tmp = plain_int ^correctkey;
  int sboxmiddle = S_box[middle_tmp].toInt(&ok, 16);
  if(this->HM00 == 0)
    firststate = plain_int;
  if(this->HM00 == 1)
    firststate = middle_tmp;
  if(this->HM00 == 2)
    firststate = sboxmiddle;
  if(this->HM01 == 1)
    secondstate = middle_tmp;
  if(this->HM01 == 2)
    secondstate = sboxmiddle;
  if(this->Model == "HanMing Weight"){
    if(this->IsValue)
      middle_subkey = firststate;
    else
      middle_subkey = HM[firststate];
  }else{
    if(this->IsValue)
      middle_subkey = firststate ^ secondstate;
    else
      middle_subkey = HM[firststate ^ secondstate];
  }
  return middle_subkey;
}
