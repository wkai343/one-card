#pragma once
#include"Account.h"
#include"User.h"
class Admin : public Account {
public:
    Admin() {}
    Admin(string id);
    Admin(string id, string name, string password);
    void addUser(string id, string name, string password, float balance);
    void importUsers(string fileName);
    void deleteUser(string id);
    void deleteUsers(string fileName);
    void viewUser(string id);
    void viewUser(string id, int);
    void viewAllUsers();
    void modifyUserName(string id, string name);
    void modifyUserPassword(string id, string password);
    void changeUserStatus(string id);
    void reissueCard(string id,float money);
    void exportData(bool id,bool password,bool name,bool balance,bool card,bool status);
    virtual void viewInfo();
    virtual void openMenu();
    virtual void loadData();
    virtual void saveData();
};
struct adminData {
    char name[21]{};
};