#include"Admin.h"
#include<ctime>
#include<fstream>
int newCard() {
    int card;
    srand(time(NULL));
    card = rand() % 1000000000 + 1000000000;
    return card;
}
bool Admin::isExist(string id) {
    ifstream infile("users.txt");
    if (!infile) {
        cerr << "Error: could not open infile users.txt" << endl;
        exit(1);
    }
    string temp;
    while (infile >> temp) {
        if (temp == id) {
            infile.close();
            return true;
        }
        infile >> temp;
    }
    infile.close();
    return false;
}
Admin::Admin(string id, string name, string password) :Account(id, name, password) {}
void Admin::addUser(string id, string name, string password, float balance) {
    ifstream infile("users.txt");
    if (!infile) {
        cerr << "Error: could not open infile users.txt" << endl;
        exit(1);
    }
    string temp;
    while (infile >> temp) {
        if (temp == id) {
            cout << "该账号已存在." << endl;
            return;
        }
        infile >> temp;
    }
    ofstream outfile(id + ".txt");
    if (!outfile) {
        cout << "打开失败." << endl;
        return;
    }
    outfile << name << ' ' << balance << ' ' << newCard() << ' ' << 0 << endl;
    outfile.close();
    outfile.open("users.txt", ios::app);
    if (!outfile) {
        cerr << "Error: could not open file users.txt" << endl;
        exit(1);
    }
    outfile << id << ' ' << password << endl;
    cout << "用户已添加." << endl;
}
void Admin::deleteUser(string id) {
    ifstream infile("users.txt");
    if (!infile) {
        cerr << "Error: could not open infile users.txt" << endl;
        exit(1);
    }
    string temp;
    // temp.txt is a temporary file to store the data of users.txt
    ofstream outfile("temp.txt");
    if (!outfile) {
        cerr << "Error: could not open file temp.txt" << endl;
        exit(1);
    }
    while (infile >> temp) {
        if (temp == id) {
            infile >> temp;
            continue;
        }
        outfile << temp << ' ';
        infile >> temp;
        outfile << temp << endl;
    }
    remove("users.txt");
    rename("temp.txt", "users.txt");
    remove((id + ".txt").c_str());
    cout << "用户已删除." << endl;
}
void Admin::viewUser(string id) {
    ifstream infile(id + ".txt");
    if (!infile) {
        cerr << "Error: could not open infile " << id << ".txt" << endl;
        exit(1);
    }
    string name;
    float balance;
    int card;
    bool status;
    infile >> name >> balance >> card >> status;
    cout << "账号：" << id << endl;
    cout << "姓名：" << name << endl;
    cout << "余额：" << balance << endl;
    cout << "卡号：" << card << endl;
    cout << "状态：" << (status ? "已挂失" : "正常") << endl;
}
void Admin::modifyUserName(string id, string name) {
    ifstream infile(id + ".txt");
    if (!infile) {
        cerr << "Error: could not open infile " << id << ".txt" << endl;
        exit(1);
    }
    string temp;
    float balance;
    int card;
    bool status;
    infile >> temp >> balance >> card >> status;
    infile.close();
    ofstream outfile(id + ".txt");
    temp = name + " " + to_string(balance) + " " + to_string(card) + " " + to_string(status);
    outfile << temp;
    outfile.close();
    cout << "用户信息已修改." << endl;
}
void Admin::modifyUserPassword(string id, string password) {
    ifstream inputFile("users.txt");
    ofstream outputFile("temp.txt");
    string line;
    bool found = false;
    while (getline(inputFile, line)) {
        string currentUsername;
        string currentPassword;
        bool foundUsername = false;
        for (char c : line) {
            if (c == ' ') {
                foundUsername = true;
            }
            else if (foundUsername) {
                currentPassword += c;
            }
            else {
                currentUsername += c;
            }
        }
        if (currentUsername == id) {
            outputFile << id << ' ' << password << '\n';
            found = true;
        }
        else {
            outputFile << line << '\n';
        }
    }
    inputFile.close();
    outputFile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
    if (found) {
        cout << "修改成功." << endl;
    }
    else {
        cout << "账号不存在." << endl;
    }
}

void Admin::changeUserStatus(string id) {
    fstream file(id + ".txt");
    if (!file) {
        cerr << "Error: could not open file " << id << ".txt" << endl;
        exit(1);
    }
    string name;
    float balance;
    int card;
    bool status;
    file >> name >> balance >> card >> status;
    string temp = name + " " + to_string(balance) + " " + to_string(card) + " " + to_string(!status);
    file.seekg(0, ios::beg);
    file << temp;
    file.close();
    cout << "用户状态已修改." << endl;
}
void Admin::reissueCard(string id) {
    fstream file(id + ".txt");
    if (!file) {
        cerr << "Error: could not open file " << id << ".txt" << endl;
        exit(1);
    }
    string name;
    float balance;
    file >> name >> balance;
    file.seekg(0, ios::beg);
    string temp=name+" "+to_string(balance)+" "+to_string(newCard())+" 0";
    file << temp;
    cout << "已补卡." << endl;
}
void Admin::viewAllUsers() {
    ifstream infile("users.txt");
    if (!infile) {
        cerr << "Error: could not open infile users.txt" << endl;
        exit(1);
    }
    string id;
    while (infile >> id) {
        viewUser(id);
        infile >> id;
        cout << endl;
    }
}
void Admin::viewInfo() {
    cout << "账号：" << getId() << endl;
    cout << "姓名：" << getName() << endl;
}
void Admin::openMenu() {
    int option;
    while (true) {
        _sleep(1000);
        system("cls");
        cout << "一卡通信息管理系统" << endl << endl;
        viewInfo();
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.查看用户" << endl;
        cout << "4.查看所有用户" << endl;
        cout << "5.修改用户姓名" << endl;
        cout << "6.修改用户密码" << endl;
        cout << "7.修改用户状态" << endl;
        cout << "8.补卡" << endl;
        cout << "9.修改管理员信息" << endl;
        cout << "0.退出" << endl;
        cout << "请输入选项：";
        cin >> option;
        switch (option) {
        case 1: {
            string id, name, password;
            float balance;
            cout << "请输入用户账号：";
            cin >> id;
            cout << "请输入用户姓名：";
            cin >> name;
            cout << "请输入用户密码：";
            cin >> password;
            cout << "请输入用户余额：";
            cin >> balance;
            addUser(id, name, password, balance);
            break;
        }
        case 2: {
            string id;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id)) {
                cout << "用户不存在." << endl;
                system("pause");
                break;
            }
            deleteUser(id);
            break;
        }
        case 3: {
            string id;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id)) {
                cout << "用户不存在." << endl;
                system("pause");
                break;
            }
            viewUser(id);
            system("pause");
            break;
        }
        case 4: {
            viewAllUsers();
            system("pause");
            break;
        }
        case 5: {
            string id, name;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id)) {
                cout << "用户不存在." << endl;
                system("pause");
                break;
            }
            cout << "请输入用户姓名：";
            cin >> name;
            modifyUserName(id, name);
            break;
        }
        case 6: {
            string id, password;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id)) {
                cout << "用户不存在." << endl;
                system("pause");
                break;
            }
            cout << "请输入用户密码：";
            cin >> password;
            modifyUserPassword(id, password);
            break;
        }
        case 7: {
            string id;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id)) {
                cout << "用户不存在." << endl;
                system("pause");
                break;
            }
            changeUserStatus(id);
            break;
        }
        case 8: {
            string id;
            cout << "请输入用户账号：";
            cin >> id;
            if (!isExist(id)) {
                cout << "用户不存在." << endl;
                system("pause");
                break;
            }
            reissueCard(id);
            break;
        }
        case 9: {
            string name, password;
            cout << "请输入管理员姓名：";
            cin >> name;
            cout << "请输入管理员密码：";
            cin >> password;
            modifyInfo(name, password);
            break;
        }
        case 0: {
            system("cls");
            cout << "欢迎下次使用！" << endl;
            system("pause");
            return;
        }
        default: {
            cout << "输入错误，请重新输入." << endl;
            break;
        }
        }
    }
}