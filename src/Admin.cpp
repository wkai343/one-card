#include"Admin.h"
#include"User.h"
#include"isExist.h"
#include"check.h"
#include<ctime>
bool checkFile() {
    ifstream infile("users.dat", ios::binary);
    if (!infile) {
        cerr << "文件打开失败！" << endl;
        return false;
    }
    infile.seekg(0, ios::end);
    if (infile.tellg() == 0) {
        infile.close();
        return false;
    }
    infile.close();
    return true;
}//判断文件是否为空
int newCard(int n = 0) {
    int card;
    srand(time(NULL) + n);
    card = rand() % 1000000000 + 1000000000;
    return card;
}
Admin::Admin(string id) :Account(id) {}
Admin::Admin(string id, string name, string password) :Account(id, name, password) {}
void Admin::addUser(string id, string name, string password, float balance) {
    ofstream outfile("users.dat", ios::app | ios::binary);
    if (!outfile) {
        cerr << "文件打开失败！" << endl;
        return;
    }
    account acc(id, password);
    outfile.write((char*)&acc, sizeof(account));
    outfile.close();
    outfile.open(id + ".dat", ios::binary | ios::out);
    userData usr(name, balance, newCard());
    outfile.write((char*)&usr, sizeof(userData));
    outfile.close();
    cout << "账号已创建." << endl;
}
void Admin::importUsers(string fileName) {
    ifstream infile(fileName, ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "文件不存在！" << endl;
        return;
    }
    ofstream outfile1("users.dat", ios::app | ios::binary);
    if (!outfile1) {
        cerr << "文件打开失败！" << endl;
        return;
    }
    ofstream outfile2;
    float blance;
    cout << "请输入初始余额：";
    cin >> blance;
    account acc;
    userData usr;
    string id, name;
    int m = 0, n = 0;
    for (; infile >> id >> name;++n) {
        if (!idCheck(id)) {
            cout << "第" << n + 1 << "行账号格式错误，已跳过" << endl;
            ++m;
            continue;
        }
        if (isExist(id, true)) {
            cout << "第" << n + 1 << "行账号已存在，已跳过" << endl;
            ++m;
            continue;
        }
        if (!nameCheck(name)) {
            cout << "第" << n + 1 << "行姓名格式错误，已跳过" << endl;
            ++m;
            continue;
        }
        strcpy(acc.id, id.c_str());
        strcpy(acc.password, acc.id);
        outfile1.write((char*)&acc, sizeof(account));
        outfile2.open(id + ".dat", ios::binary | ios::out);
        usr = userData(name, blance, newCard(n));
        outfile2.write((char*)&usr, sizeof(userData));
        outfile2.close();
    }
    infile.close();
    outfile1.close();
    cout << "成功导入" << n - m << "个账号." << endl;
}
void Admin::deleteUser(string id) {
    fstream outfile("users.dat", ios::binary | ios::in | ios::out);
    ofstream outfile2("temp.dat", ios::binary | ios::out);
    if (!outfile) {
        cerr << "文件打开失败！" << endl;
        return;
    }
    account acc;
    while (outfile.read((char*)&acc, sizeof(account))) {
        if (acc.id == id) {
            continue;
        }
        outfile2.write((char*)&acc, sizeof(account));
    }
    outfile.close();
    outfile2.close();
    remove("users.dat");
    rename("temp.dat", "users.dat");
    remove((id + ".dat").c_str());
    cout << "账号已删除." << endl;
}
void Admin::deleteUsers(string fileName) {
    ifstream infile(fileName, ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "文件不存在！" << endl;
        return;
    }
    ofstream outfile2;
    string id, name;
    int m = 0, n = 0;
    for (; infile >> id >> name; ++n) {
        if (!idCheck(id)) {
            cout << "第" << n + 1 << "行账号格式错误，已跳过" << endl;
            ++m;
            continue;
        }
        if (!isExist(id, true)) {
            cout << "第" << n + 1 << "行账号不存在，已跳过" << endl;
            ++m;
            continue;
        }
        deleteUser(id);
    }
    cout << "成功删除" << n - m << "个账号." << endl;
}
void Admin::viewUser(string id) {
    ifstream infile(id + ".dat");
    if (!infile) {
        cerr << "Error: could not open infile " << id << ".txt" << endl;
        exit(1);
    }
    userData usr;
    infile.read((char*)&usr, sizeof(userData));
    cout << "账号：" << id << endl;
    cout << "用户名：" << usr.name << endl;
    cout << "余额：" << usr.balance << endl;
    cout << "卡号：" << usr.card << endl;
    cout << "状态：" << (usr.status ? "已挂失" : "正常") << endl;
    infile.close();
}
void Admin::viewUser(string id, int) {
    ifstream infile(id + ".dat");
    if (!infile) {
        cerr << "Error: could not open infile " << id << ".txt" << endl;
        exit(1);
    }
    userData usr;
    infile.read((char*)&usr, sizeof(userData));
    cout << id << '\t' << usr.name << '\t' << usr.balance << '\t' << usr.card << '\t' << (usr.status ? "已挂失" : "正常") << endl;
    infile.close();
}
void Admin::modifyUserName(string id, string name) {
    User usr(id);
    usr.loadData();
    usr.setName(name);
    usr.saveData();
    cout << "用户信息已修改." << endl;
}
void Admin::modifyUserPassword(string id, string password) {
    User usr(id);
    usr.loadData();
    usr.setPassword(password);
    usr.saveData();
    cout << "用户信息已修改." << endl;
}
void Admin::changeUserStatus(string id) {
    User usr(id);
    usr.loadData();
    usr.changeStatus();
    usr.saveData();
    cout << "用户信息已修改." << endl;
}
void Admin::reissueCard(string id) {
    User usr(id);
    usr.loadData();
    usr.card = newCard();
    usr.status = false;
    usr.saveData();
    cout << "用户信息已修改." << endl;
}
void Admin::viewAllUsers() {
    ifstream infile("users.dat", ios::binary);
    if (!infile) {
        cerr << "Error: could not open infile users.dat" << endl;
        exit(1);
    }
    account acc;
    infile.seekg(0, ios::beg);
    cout << "账号\t\t姓名\t余额\t卡号\t\t状态" << endl;
    while (infile.read((char*)&acc, sizeof(account))) {
        viewUser(acc.id, 0);
    }
    infile.close();
}
void Admin::viewInfo() {
    cout << "账号：" << getId() << endl;
    cout << "姓名：" << getName() << endl;
}
void Admin::openMenu() {
    char option;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "一卡通信息管理系统" << endl << endl;
        viewInfo();
        cout << endl;
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.批量导入/删除用户" << endl;
        cout << "4.查看用户" << endl;
        cout << "5.查看所有用户" << endl;
        cout << "6.修改用户信息" << endl;
        cout << "7.修改管理员信息" << endl;
        cout << "0.退出" << endl;
        cout << "请输入选项：";
        if ((option = cin.get()) == '\n') {
            continue;
        }
        switch (option) {
        case '1': {
            string id, name, password;
            float balance;
            cout << "请输入用户账号：";
            cin >> id;
            if (isExist(id, 1)) {
                cout << "用户已存在." << endl;
                break;
            }
            if (!idCheck(id)) {
                cout << "账号格式错误." << endl;
                break;
            }
            cout << "请输入用户姓名：";
            cin >> name;
            if (!nameCheck(name)) {
                cout << "输入字符超出限制." << endl;
                break;
            }
            cout << "请输入用户密码：";
            cin >> password;
            if (!passwordCheck(password)) {
                cout << "密码格式错误." << endl;
                break;
            }
            balance = balanceCheck("请输入用户余额：");
            addUser(id, name, password, balance);
            break;
        }
        case '2': {
            if (!checkFile()) {
                cout << "无用户信息." << endl;
                break;
            }
            string id;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id, 1)) {
                cout << "用户不存在." << endl;
                break;
            }
            deleteUser(id);
            break;
        }
        case '3': {
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "一卡通信息管理系统" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.批量导入用户" << endl;
                cout << "2.批量删除用户" << endl;
                cout << "0.返回" << endl;
                cout << "请输入选项：";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string filename;
                    cout << "请输入文件名：";
                    cin >> filename;
                    importUsers(filename);
                    system("pause");
                    break;
                }
                case '2': {
                    if (!checkFile()) {
                        cout << "无用户信息." << endl;
                        break;
                    }
                    string filename;
                    cout << "请输入文件名：";
                    cin >> filename;
                    deleteUsers(filename);
                    system("pause");
                    break;
                }
                case '0': {
                    flag = false;
                    break;
                }
                default: {
                    cout << "输入错误，请重新输入." << endl;
                    break;
                }
                }
            }
            break;
        }
        case '4': {
            if (!checkFile()) {
                cout << "无用户信息." << endl;
                break;
            }
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "一卡通信息管理系统" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.按账号查找" << endl;
                cout << "2.按姓名查找" << endl;
                cout << "3.按卡号查找" << endl;
                cout << "4.按状态查找" << endl;
                cout << "0.返回" << endl;
                cout << "请输入选项：";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string id;
                    cout << "请输入用户账号：";
                    cin >> id;
                    if (!isExist(id, 1)) {
                        cout << "用户不存在." << endl;
                        break;
                    }
                    system("cls");
                    viewUser(id);
                    system("pause");
                    break;
                }
                case '2': {
                    string name;
                    cout << "请输入用户姓名：";
                    cin >> name;
                    ifstream infile1("users.dat", ios::binary | ios::in), infile2;
                    if (!infile1) {
                        cerr << "无法打开文件." << endl;
                        exit(1);
                    }
                    system("cls");
                    account acc;
                    userData usr;
                    int n = 0;
                    while (infile1.read((char*)&acc, sizeof(account))) {
                        infile2.open((string)acc.id + ".dat", ios::binary | ios::in);
                        if (!infile2) {
                            cerr << "无法打开文件." << endl;
                            exit(1);
                        }
                        infile2.read((char*)&usr, sizeof(userData));
                        infile2.close();
                        if (usr.name == name) {
                            viewUser(acc.id);
                            n++;
                        }
                    }
                    infile1.close();
                    if (n > 0) system("pause");
                    else cout << "用户不存在." << endl;
                    break;
                }
                case '3': {
                    int card;
                    cout << "请输入用户卡号：";
                    cin >> card;
                    ifstream infile1("users.dat", ios::binary | ios::in), infile2;
                    if (!infile1) {
                        cerr << "无法打开文件." << endl;
                        exit(1);
                    }
                    system("cls");
                    account acc;
                    userData usr;
                    int n = 0;
                    while (infile1.read((char*)&acc, sizeof(account))) {
                        infile2.open((string)acc.id + ".dat", ios::binary | ios::in);
                        if (!infile2) {
                            cerr << "无法打开文件." << endl;
                            exit(1);
                        }
                        infile2.read((char*)&usr, sizeof(userData));
                        infile2.close();
                        if (usr.card == card) {
                            viewUser(acc.id);
                            n++;
                        }
                    }
                    infile1.close();
                    if (n > 0) system("pause");
                    else cout << "用户不存在." << endl;
                    break;
                }
                case '4': {
                    while (true) {
                        _sleep(500);
                        system("cls");
                        cout << "一卡通信息管理系统" << endl << endl;
                        viewInfo();
                        cout << endl;
                        cout << "1.正常" << endl;
                        cout << "2.挂失" << endl;
                        cout << "0.返回" << endl;
                        cout << "请输入选项：";
                        if ((option = cin.get()) == '\n') {
                            continue;
                        }
                        if (option >= '0' && option <= '2') break;
                        else cout << "输入错误，请重新输入." << endl;
                    }
                    if (option == '0') break;
                    ifstream infile1("users.dat", ios::binary | ios::in), infile2;
                    if (!infile1) {
                        cerr << "无法打开文件." << endl;
                        exit(1);
                    }
                    system("cls");
                    account acc;
                    userData usr;
                    bool status = option - '1';
                    int n = 0;
                    cout << "账号\t\t姓名\t余额\t卡号\t\t状态" << endl;
                    while (infile1.read((char*)&acc, sizeof(account))) {
                        infile2.open((string)acc.id + ".dat", ios::binary | ios::in);
                        if (!infile2) {
                            cerr << "无法打开文件." << endl;
                            exit(1);
                        }
                        infile2.read((char*)&usr, sizeof(userData));
                        infile2.close();
                        if (usr.status == status) {
                            viewUser(acc.id, 0);
                            n++;
                        }
                    }
                    infile1.close();
                    if (n > 0) system("pause");
                    else cout << "用户不存在." << endl;
                    break;
                }
                case '0': {
                    flag = false;
                    break;
                }
                default: {
                    cout << "输入错误，请重新输入." << endl;
                    break;
                }
                }
            }
            break;
        }
        case '5': {
            if (!checkFile()) {
                cout << "无用户信息." << endl;
                break;
            }
            system("cls");
            viewAllUsers();
            system("pause");
            break;
        }
        case '6': {
            if (!checkFile()) {
                cout << "无用户信息." << endl;
                break;
            }
            string id;
            cout << "请输入用户账号：";
            cin >> id;
            if (!idCheck(id)) {
                cout << "账号格式错误." << endl;
                break;
            }
            if (!isExist(id, 1)) {
                cout << "用户不存在." << endl;
                break;
            }
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "一卡通信息管理系统" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.修改用户名" << endl;
                cout << "2.修改用户密码" << endl;
                cout << "3.修改用户状态" << endl;
                cout << "4.补办一卡通" << endl;
                cout << "0.返回" << endl;
                cout << "请输入选项：";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string name;
                    cout << "请输入新用户名：";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "输入字符超出限制." << endl;
                        break;
                    }
                    modifyUserName(id, name);
                    break;
                }
                case '2': {
                    string password;
                    cout << "请输入新用户密码：";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "密码格式错误." << endl;
                        break;
                    }
                    modifyUserPassword(id, password);
                    break;
                }
                case '3': {
                    changeUserStatus(id);
                    break;
                }
                case '4': {
                    reissueCard(id);
                    break;
                }
                case '0': {
                    flag = false;
                    break;
                }
                default: {
                    cout << "输入错误，请重新输入." << endl;
                    break;
                }
                }
            }
            break;
        }
        case '7': {
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "一卡通信息管理系统" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.修改管理员姓名" << endl;
                cout << "2.修改管理员密码" << endl;
                cout << "0.返回" << endl;
                cout << "请输入选项：";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string name;
                    cout << "请输入姓名：";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "输入字符超出限制." << endl;
                        break;
                    }
                    setName(name);
                    saveData();
                    break;
                }
                case '2': {
                    string password;
                    cout << "请输入密码：";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "密码格式错误." << endl;
                        break;
                    }
                    setPassword(password);
                    saveData();
                    break;
                }
                case '0': {
                    flag = false;
                    break;
                }
                default: {
                    cout << "输入错误，请重新输入." << endl;
                    break;
                }
                }
            }
            break;
        }
        case '0': {
            return;
        }
        default: {
            cout << "输入错误，请重新输入." << endl;
            break;
        }
        }
    }
}
void Admin::loadData() {
    ifstream infile("admins.dat", ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "管理员文件已丢失！" << endl;
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
        cerr << "Error: could not open infile " << getId() << ".dat" << endl;
        exit(1);
    }
    adminData ad;
    infile.read((char*)&ad, sizeof(adminData));
    setName(ad.name);
    infile.close();
}
void Admin::saveData() {
    fstream outfile("admins.dat", ios::binary | ios::in | ios::out);
    if (!outfile) {
        cerr << "Error: could not open outfile admins.dat" << endl;
        exit(1);
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
    outfile.open(getId() + ".dat", ios::binary | ios::out);
    if (!outfile) {
        cerr << "Error: could not open outfile " << getId() << ".dat" << endl;
        exit(1);
    }
    adminData ad;
    strcpy(ad.name, getName().c_str());
    outfile.write((char*)&ad, sizeof(adminData));
    outfile.close();
}