#pragma once
#include<fstream>
#include<cstdlib>
#include"Admin.h"
#include"isExist.h"
using namespace std;
int n = 0;
int checkId(string id) {
    if (id.length() != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(id[i])) {
            return 0;
        }
    }
    if (!((n = isExist(id, 0)) || (n = isExist(id, 1)))) return 3;
    if (id == "1000000001" || id == "1000000002" || id == "1000000003") return 1;
    return 2;
}
bool checkPassword(string id, string password, bool check) {
    string str;
    if (check) str = "users.dat";
    else str = "admins.dat";
    fstream file(str);
    if (!file) {
        cerr << "Error: could not open file" << endl;
        exit(1);
    }
    account acc;
    int j = 0;
    while (file.read((char*)&acc, sizeof(account)), ++j, j != n) {}
    if (acc.password == password) return true;
    return false;
}
int Login() {
    string id, password;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "ÇëÊäÈëÕËºÅ£º";
        cin >> id;
        int check;
        if ((check = checkId(id)) == 0) {
            cout << "¸ñÊ½´íÎó£¡" << endl;
            continue;
        }
        else if (check == 3) {
            cout << "ÕËºÅ²»´æÔÚ£¡" << endl;
            continue;
        }
        check -= 1;
        cout << "ÇëÊäÈëÃÜÂë£º";
        cin >> password;
        if (!checkPassword(id, password, check)) {
            cout << "ÃÜÂë´íÎó£¡" << endl;
            continue;
        }
        if (check) {
            User user(id);
            user.loadData();
            user.openMenu();
        }
        else {
            Admin admin(id);
            admin.loadData();
            admin.openMenu();
        }
        return 0;
    }
}
