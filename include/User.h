#pragma once
#include"Account.h"
struct Record {
    float amount = 0;
    char type[10]{};
};
class User : public Account {
private:
    float balance;
    int card;
    bool status = 0;
    Record record[100];
    int recordNum = 0;
public:
    friend class Admin;
    User() {}
    User(string id);
    User(string id, string name, string password, float balance, int card, bool status);
    float getBalance();
    int getCard();
    bool getStatus();
    void consume(float amount);
    void recharge(float amount);
    void addRecord(float amount, string type);
    void viewRecords();
    void changeStatus();
    virtual void openMenu();
    virtual void viewInfo();
    virtual void loadData();
    virtual void saveData();
};
struct userData {
    char name[21]{};
    float balance = 0;
    int card = 0;
    bool status = 0;
    Record record[100]{};
    int recordNum = 0;
    userData() {}
    userData(string name, float balance, int card) :balance(balance), card(card) {
        strcpy(this->name, name.c_str());
    }
    userData(string name, float balance, int card, bool status) :userData(name, balance, card) {
        this->status = status;
    }
};