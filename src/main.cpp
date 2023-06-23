#include"Admin.h"
#include"User.h"
#include"Login.hpp"
#include<iostream>
using namespace std;
int main() {
    int choice;
    while (true) {
        system("cls");
        cout << "一卡通信息管理系统" << endl;
        cout << "1.登录" << endl;
        cout << "2.退出" << endl;
        cout << "请选择：";
        cin >> choice;
        switch (choice) {
        case 1:
            Login();
            break;
        case 2:
            system("cls");
            cout << "欢迎下次使用！" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "输入错误！" << endl;
            _sleep(500);
            system("cls");
            break;
        }
    }
    return 0;
}
