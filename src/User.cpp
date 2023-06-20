#include"User.h"
User::User(string id, string name, string password, float balance, int card, bool status) :Account(id, name, password), balance(balance), card(card), status(status) {}
float User::getBalance() {
    return balance;
}
int User::getCard() {
    return card;
}
bool User::getStatus() {
    return status;
}
void User::consume(float amount) {
    if (balance >= amount) {
        balance -= amount;
        cout << "已消费 " << amount << " 元" << endl;
    }
    else {
        cout << "余额不足!" << endl;
    }
}
void User::recharge(float amount) {
    balance += amount;
}
void User::viewInfo() {
    cout << "一卡通信息：" << endl;
    cout << "账号: " << getId() << endl;
    cout << "姓名: " << getName() << endl;
    cout << "余额: " << balance << endl;
    cout << "卡号: " << card << endl;
    cout << "状态: " << (status ? "已挂失" : "正常") << endl;
}
void User::addRecord(float amount, string type) {
    record[recordNum].amount = amount;
    record[recordNum].type = type;
    recordNum++;
}
void User::viewRecords() {
    for (int i = 0; i < recordNum; i++) {
        cout << "Amount: " << record[i].amount << " Type: " << record[i].type << endl;
    }
}
void User::changeStatus() {
    status = !status;
    cout << "状态已更改." << endl;
}
void User::openMenu() {
    int choice;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "一卡通信息管理系统" << endl << endl;
        viewInfo();
        cout << "1.挂失/解挂" << endl;
        cout << "2.消费" << endl;
        cout << "3.充值" << endl;
        cout << "4.查询记录" << endl;
        cout << "5.修改信息" << endl;
        cout << "0.退出" << endl;
        cout << "请选择：";
        cin >> choice;
        switch (choice) {
        case 1:
            changeStatus();
            break;
        case 2: {
            if(status) {
                cout << "已挂失，无法消费." << endl;
                system("pause");
                break;
            }
            float amount;
            cout << "请输入消费金额：";
            cin >> amount;
            consume(amount);
            addRecord(amount, "消费");
            break;
        }
        case 3: {
            if(status) {
                cout << "已挂失，无法充值." << endl;
                system("pause");
                break;
            }
            cout << "请输入充值金额：";
            float amount;
            cin >> amount;
            recharge(amount);
            addRecord(amount, "充值");
            break;
        }
        case 4:
            viewRecords();
            system("pause");
            break;
        case 5: {
            string newName, newPassword;
            cout << "请输入新姓名：";
            cin >> newName;
            cout << "请输入新密码：";
            cin >> newPassword;
            modifyInfo(newName, newPassword);
            break;
        }
        case 0: {
            system("cls");
            cout << "欢迎下次使用！" << endl;
            system("pause");
            return;
            break;
        }
        default:
            cout << "输入错误，请重新输入." << endl;
            break;
        }
    }
}