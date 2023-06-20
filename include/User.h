#pragma once
#include"Account.h"
#include<iostream>
struct Record {
    float amount;
    string type;
};
class User: public Account {
private:
    float balance;
    int card;
    bool status = 0;
    Record record[100];
    int recordNum = 0;
public:
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
};