#pragma once
#include"Account.h"
#include"User.h"
class Admin : public Account {
public:
    Admin() {}
    Admin(string id);
    Admin(string id, string name, string password);
    void addUser(string id, string name, string password, float balance);
    void deleteUser(string id);
    void viewUser(string id);
    void viewAllUsers();
    void modifyUserName(string id, string name);
    void modifyUserPassword(string id, string password);
    void changeUserStatus(string id);
    void reissueCard(string id);
    virtual void viewInfo();
    virtual void openMenu();
    virtual void loadData();
    virtual void saveData();
};
struct adminData {
    char name[21]{};
};