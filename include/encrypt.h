#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// 加密函数
void encrypt(string& data);

// 解密函数
void decrypt(string& data);

// 写入加密数据到二进制文件
void writeEncryptedData(string filename, string data);

// 从二进制文件中读取加密数据并解密
string readDecryptedData(string filename);