#include "encrypt.h"
void encrypt(string& data) {
    for (int i = 0; i < data.length(); i++) {
        data[i] = data[i] + 1; // 将每个字符加1
    }
}

void decrypt(string& data) {
    for (int i = 0; i < data.length(); i++) {
        data[i] = data[i] - 1; // 将每个字符减1
    }
}

void writeEncryptedData(string filename, string data) {
    encrypt(data); // 加密数据
    ofstream file(filename, ios::binary);
    file.write(data.c_str(), data.length());
    file.close();
}

string readDecryptedData(string filename) {
    ifstream file(filename, ios::binary);
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    decrypt(data); // 解密数据
    return data;
}