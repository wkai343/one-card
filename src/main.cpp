#include"Admin.h"
#include"User.h"
#include"Login.hpp"
#include<iostream>
using namespace std;
int main() {
    int choice;
    while (true) {
        system("cls");
        cout << "һ��ͨ��Ϣ����ϵͳ" << endl;
        cout << "1.��¼" << endl;
        cout << "2.�˳�" << endl;
        cout << "��ѡ��";
        cin >> choice;
        switch (choice) {
        case 1:
            Login();
            break;
        case 2:
            system("cls");
            cout << "��ӭ�´�ʹ�ã�" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "�������" << endl;
            _sleep(500);
            system("cls");
            break;
        }
    }
    return 0;
}
