#pragma once
#include<string>
#include<iostream>
using namespace std;
bool idCheck(string id);
bool passwordCheck(string password);//检查密码是否为9-16位的数字和字母组合
bool nameCheck(string name);
float balanceCheck(const char*);