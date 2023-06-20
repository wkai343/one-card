#pragma once
#include<string>
#include<iostream>
using namespace std;
class Account
{
private:
    string id;
    string name;
    string password;
public:
    Account(string id, string name, string password);
    string getId();
    string getName();
    string getPassword();
    void setName(string name);
    void setPassword(string password);
    virtual void openMenu()=0;
    virtual void viewInfo()=0;
    void modifyInfo(string name, string password);
};