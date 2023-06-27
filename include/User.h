#pragma once
#include"Account.h"
#include<ctime>
struct Time {
    short year;
    short month;
    short day;
    short hour;
    short minute;
    short second;
    Time() {
        time_t t = time(0);
        tm* local = localtime(&t);
        year = local->tm_year + 1900;
        month = local->tm_mon + 1;
        day = local->tm_mday;
        hour = local->tm_hour;
        minute = local->tm_min;
        second = local->tm_sec;
    }
    bool operator>=(const Time& ti) {
        if (year >= ti.year) {
            if (month >= ti.month) {
                if (day >= ti.day) {
                    if (hour >= ti.hour) {
                        if (minute >= ti.minute) {
                            if (second >= ti.second) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    bool operator<=(const Time& ti) {
        if (year <= ti.year) {
            if (month <= ti.month) {
                if (day <= ti.day) {
                    if (hour <= ti.hour) {
                        if (minute <= ti.minute) {
                            if (second <= ti.second) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    friend ostream& operator<<(ostream& out, const Time& ti) {
        out << ti.year << '/' << ti.month << '/' << ti.day << '/' << ti.hour << ':' << ti.minute << ':' << ti.second;
        return out;
    }
};
struct Record {
    float amount = 0;
    enum TYPE { RECHARGE, BATH, DINE, SHOP } type;
    Time ti;
    Record() {}
    Record(float amount, TYPE type) {
        this->amount = amount;
        this->type = type;
    }
};
class User : public Account {
private:
    float balance;
    int card;
    bool status = 0;
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
    void addRecord(float amount, Record::TYPE type);
    void viewRecord(const Record& record);
    void viewRecords();
    void changeStatus();
    void exportRecords();
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
    unsigned short recordNum = 0;
    userData() {}
    userData(string name, float balance, int card) :balance(balance), card(card) {
        strcpy(this->name, name.c_str());
    }
    userData(string name, float balance, int card, bool status) :userData(name, balance, card) {
        this->status = status;
    }
};