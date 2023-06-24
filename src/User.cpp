#include"User.h"
#include"check.h"
User::User(string id) :Account(id) {}
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
    balance -= amount;
}
void User::recharge(float amount) {
    balance += amount;
    cout << "已充值 " << amount << " 元" << endl;
}
void User::addRecord(float amount, Record::TYPE type) {
    ofstream outfile(getId() + ".dat", ios::binary | ios::app);
    if (!outfile) {
        cerr << "文件打开失败！" << endl;
        exit(1);
    }
    Record record(amount, type);
    outfile.write((char*)&record, sizeof(Record));
    outfile.close();
    recordNum++;
}
void User::viewRecords() {
    ifstream infile(getId() + ".dat", ios::binary);
    if (!infile) {
        cerr << "文件打开失败！" << endl;
        return;
    }
    infile.seekg(sizeof(userData));
    Record record;
    cout << "记录如下：" << endl;
    while (infile.read((char*)&record, sizeof(Record))) {
        cout << record.ti.year << "-" << record.ti.month << "-" << record.ti.day << " " << record.ti.hour << ":" << record.ti.minute << ":" << record.ti.second << " ";
        switch (record.type) {
        case Record::RECHARGE:
            cout << "充值 ";
            break;
        case Record::BATH:
            cout << "洗浴 ";
            break;
        case Record::DINE:
            cout << "餐饮 ";
            break;
        case Record::SHOP:
            cout << "购物 ";
            break;
        }
        cout << record.amount << " 元" << endl;
    }
    infile.close();
}
void User::changeStatus() {
    status = !status;
    cout << "状态已更改." << endl;
}
void User::viewInfo() {
    cout << "一卡通信息：" << endl;
    cout << "账号: " << getId() << endl;
    cout << "姓名: " << getName() << endl;
    cout << "余额: " << balance << endl;
    cout << "卡号: " << card << endl;
    cout << "状态: " << (status ? "已挂失" : "正常") << endl;
}
void User::openMenu() {
    int choice;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "一卡通信息管理系统" << endl << endl;
        viewInfo();
        cout << endl;
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
            if (status) {
                cout << "已挂失，无法消费." << endl;
                system("pause");
                break;
            }

            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "1.洗浴" << endl;
                cout << "2.餐饮" << endl;
                cout << "3.购物" << endl;
                cout << "0.退出" << endl;
                cout << "请选择：";
                cin >> choice;
                switch (choice) {
                case 1: {
                    cout << "请输入消费金额：";
                    float amount;
                    cin >> amount;
                    if (balance >= amount) {
                        consume(amount);
                        addRecord(amount, Record::BATH);
                        saveData();
                    }
                    else {
                        cout << "余额不足!" << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "请输入消费金额：";
                    float amount;
                    cin >> amount;
                    if (balance >= amount) {
                        consume(amount);
                        addRecord(amount, Record::DINE);
                        saveData();
                    }
                    else {
                        cout << "余额不足!" << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "请输入消费金额：";
                    float amount;
                    cin >> amount;
                    if (balance >= amount) {
                        consume(amount);
                        addRecord(amount, Record::SHOP);
                        saveData();
                    }
                    else {
                        cout << "余额不足!" << endl;
                    }
                    break;
                }
                case 0:
                    flag = false;
                    break;
                default:
                    cout << "输入错误，请重新输入." << endl;
                    break;
                }
            }
            break;
        }
        case 3: {
            if (status) {
                cout << "已挂失，无法充值." << endl;
                system("pause");
                break;
            }
            cout << "请输入充值金额：";
            float amount;
            cin >> amount;
            recharge(amount);
            addRecord(amount, Record::RECHARGE);
            saveData();
            break;
        }
        case 4:
            system("cls");
            viewRecords();
            system("pause");
            break;
        case 5: {
            system("cls");
            int choice;
            bool flag = true;
            while (flag) {
                _sleep(500);
                cout << "1.修改密码" << endl;
                cout << "2.修改姓名" << endl;
                cout << "0.退出" << endl;
                cout << "请选择：";
                cin >> choice;
                switch (choice) {
                case 1: {
                    string password;
                    cout << "请输入新密码：";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "密码格式错误." << endl;
                        break;
                    }
                    setPassword(password);
                    saveData();
                    cout << "密码已修改." << endl;
                    break;
                }
                case 2: {
                    string name;
                    cout << "请输入新姓名：";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "姓名格式错误." << endl;
                        break;
                    }
                    setName(name);
                    saveData();
                    cout << "姓名已修改." << endl;
                    break;
                }
                case 0:
                    flag = false;
                    break;
                default:
                    cout << "输入错误，请重新输入." << endl;
                    break;
                }
            }
            break;
        }
        case 0: {
            return;
            break;
        }
        default:
            cout << "输入错误，请重新输入." << endl;
            break;
        }
    }
}
void User::loadData() {
    ifstream infile("users.dat", ios::binary | ios::in);
    if (!infile.is_open()) {
        cout << "用户文件已丢失！" << endl;
        exit(1);
    }
    account acc;
    for (int i = 0;!infile.eof();i++) {
        infile.read((char*)&acc, sizeof(account));
        if (acc.id == getId()) {
            setPassword(acc.password);
            break;
        }
    }
    infile.close();
    infile.open(getId() + ".dat", ios::binary | ios::in);
    if (!infile) {
        cout << "文件打开失败！" << endl;
        return;
    }
    userData usr;
    infile.read((char*)&usr, sizeof(userData));
    setName(usr.name);
    balance = usr.balance;
    card = usr.card;
    status = usr.status;
    recordNum = usr.recordNum;
    infile.close();
}
void User::saveData() {
    fstream outfile("users.dat", ios::binary | ios::in | ios::out);
    if (!outfile) {
        cout << "文件打开失败！" << endl;
        return;
    }
    account acc;
    for (int i = 0;!outfile.eof();i++) {
        outfile.read((char*)&acc, sizeof(account));
        if (acc.id == getId()) {
            strcpy(acc.password, getPassword().c_str());
            outfile.seekp(i * sizeof(account), ios::beg);
            outfile.write((char*)&acc, sizeof(account));
            break;
        }
    }
    outfile.close();
    ifstream outfile1(getId() + ".dat", ios::binary | ios::in);
    if (!outfile1) {
        cerr << "文件打开失败！" << endl;
        exit(1);
    }
    ofstream outfile2("temp.dat", ios::binary | ios::out);
    if (!outfile2) {
        cerr << "文件打开失败！" << endl;
        exit(1);
    }
    userData usr((getName().c_str()), balance, card, status);
    usr.recordNum = recordNum;
    outfile2.write((char*)&usr, sizeof(userData));
    outfile1.seekg(sizeof(userData), ios::beg);
    char* buffer = new char[sizeof(Record)];
    for (int i = 0;i < recordNum;i++) {
        outfile1.read(buffer, sizeof(Record));
        outfile2.write(buffer, sizeof(Record));
    }
    delete[] buffer;
    outfile1.close();
    outfile2.close();
    remove((getId() + ".dat").c_str());
    rename("temp.dat", (getId() + ".dat").c_str());
}