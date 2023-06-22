#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;
class Account {
private:
    string id;
    string name;
    string password;
public:
    Account() {}
    Account(string id);
    Account(string id, string name, string password);
    string getId();
    string getName();
    string getPassword();
    void setName(string name);
    void setPassword(string password);
    virtual void openMenu() = 0;
    virtual void viewInfo() = 0;
    void modifyInfo(string name, string password);
    virtual void loadData() = 0;
    virtual void saveData() = 0;
};
struct account {
    char id[11];
    char password[17]{};
    account() {}
    account(string id, string password) {
        strcpy(this->id, id.c_str());
        strcpy(this->password, password.c_str());
    }
};