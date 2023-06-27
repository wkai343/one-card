#include"Admin.h"
#include"User.h"
#include"isExist.h"
#include"check.h"
#include<ctime>
bool checkFile() {
    ifstream infile("users.dat", ios::binary);
    if (!infile) {
        cerr << "�ļ���ʧ�ܣ�" << endl;
        return false;
    }
    infile.seekg(0, ios::end);
    if (infile.tellg() == 0) {
        infile.close();
        return false;
    }
    infile.close();
    return true;
}//�ж��ļ��Ƿ�Ϊ��
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
        cerr << "�ļ���ʧ�ܣ�" << endl;
        return;
    }
    account acc(id, password);
    outfile.write((char*)&acc, sizeof(account));
    outfile.close();
    outfile.open(id + ".dat", ios::binary | ios::out);
    userData usr(name, balance, newCard());
    outfile.write((char*)&usr, sizeof(userData));
    outfile.close();
    cout << "�˺��Ѵ���." << endl;
}
void Admin::importUsers(string fileName) {
    ifstream infile(fileName, ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "�ļ������ڣ�" << endl;
        return;
    }
    ofstream outfile1("users.dat", ios::app | ios::binary);
    if (!outfile1) {
        cerr << "�ļ���ʧ�ܣ�" << endl;
        return;
    }
    ofstream outfile2;
    float blance;
    cout << "�������ʼ��";
    cin >> blance;
    account acc;
    userData usr;
    string id, name;
    int m = 0, n = 0;
    for (; infile >> id >> name;++n) {
        if (!idCheck(id)) {
            cout << "��" << n + 1 << "���˺Ÿ�ʽ����������" << endl;
            ++m;
            continue;
        }
        if (isExist(id, true)) {
            cout << "��" << n + 1 << "���˺��Ѵ��ڣ�������" << endl;
            ++m;
            continue;
        }
        if (!nameCheck(name)) {
            cout << "��" << n + 1 << "��������ʽ����������" << endl;
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
    cout << "�ɹ�����" << n - m << "���˺�." << endl;
}
void Admin::deleteUser(string id) {
    fstream outfile("users.dat", ios::binary | ios::in | ios::out);
    ofstream outfile2("temp.dat", ios::binary | ios::out);
    if (!outfile) {
        cerr << "�ļ���ʧ�ܣ�" << endl;
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
    cout << "�˺���ɾ��." << endl;
}
void Admin::deleteUsers(string fileName) {
    ifstream infile(fileName, ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "�ļ������ڣ�" << endl;
        return;
    }
    ofstream outfile2;
    string id, name;
    int m = 0, n = 0;
    for (; infile >> id >> name; ++n) {
        if (!idCheck(id)) {
            cout << "��" << n + 1 << "���˺Ÿ�ʽ����������" << endl;
            ++m;
            continue;
        }
        if (!isExist(id, true)) {
            cout << "��" << n + 1 << "���˺Ų����ڣ�������" << endl;
            ++m;
            continue;
        }
        deleteUser(id);
    }
    cout << "�ɹ�ɾ��" << n - m << "���˺�." << endl;
}
void Admin::viewUser(string id) {
    ifstream infile(id + ".dat");
    if (!infile) {
        cerr << "Error: could not open infile " << id << ".txt" << endl;
        exit(1);
    }
    userData usr;
    infile.read((char*)&usr, sizeof(userData));
    cout << "�˺ţ�" << id << endl;
    cout << "�û�����" << usr.name << endl;
    cout << "��" << usr.balance << endl;
    cout << "���ţ�" << usr.card << endl;
    cout << "״̬��" << (usr.status ? "�ѹ�ʧ" : "����") << endl;
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
    cout << id << '\t' << usr.name << '\t' << usr.balance << '\t' << usr.card << '\t' << (usr.status ? "�ѹ�ʧ" : "����") << endl;
    infile.close();
}
void Admin::modifyUserName(string id, string name) {
    User usr(id);
    usr.loadData();
    usr.setName(name);
    usr.saveData();
    cout << "�û���Ϣ���޸�." << endl;
}
void Admin::modifyUserPassword(string id, string password) {
    User usr(id);
    usr.loadData();
    usr.setPassword(password);
    usr.saveData();
    cout << "�û���Ϣ���޸�." << endl;
}
void Admin::changeUserStatus(string id) {
    User usr(id);
    usr.loadData();
    usr.changeStatus();
    usr.saveData();
    cout << "�û���Ϣ���޸�." << endl;
}
void Admin::reissueCard(string id) {
    User usr(id);
    usr.loadData();
    usr.card = newCard();
    usr.status = false;
    usr.saveData();
    cout << "�û���Ϣ���޸�." << endl;
}
void Admin::viewAllUsers() {
    ifstream infile("users.dat", ios::binary);
    if (!infile) {
        cerr << "Error: could not open infile users.dat" << endl;
        exit(1);
    }
    account acc;
    infile.seekg(0, ios::beg);
    cout << "�˺�\t\t����\t���\t����\t\t״̬" << endl;
    while (infile.read((char*)&acc, sizeof(account))) {
        viewUser(acc.id, 0);
    }
    infile.close();
}
void Admin::viewInfo() {
    cout << "�˺ţ�" << getId() << endl;
    cout << "������" << getName() << endl;
}
void Admin::openMenu() {
    char option;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
        viewInfo();
        cout << endl;
        cout << "1.����û�" << endl;
        cout << "2.ɾ���û�" << endl;
        cout << "3.��������/ɾ���û�" << endl;
        cout << "4.�鿴�û�" << endl;
        cout << "5.�鿴�����û�" << endl;
        cout << "6.�޸��û���Ϣ" << endl;
        cout << "7.�޸Ĺ���Ա��Ϣ" << endl;
        cout << "0.�˳�" << endl;
        cout << "������ѡ�";
        if ((option = cin.get()) == '\n') {
            continue;
        }
        switch (option) {
        case '1': {
            string id, name, password;
            float balance;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (isExist(id, 1)) {
                cout << "�û��Ѵ���." << endl;
                break;
            }
            if (!idCheck(id)) {
                cout << "�˺Ÿ�ʽ����." << endl;
                break;
            }
            cout << "�������û�������";
            cin >> name;
            if (!nameCheck(name)) {
                cout << "�����ַ���������." << endl;
                break;
            }
            cout << "�������û����룺";
            cin >> password;
            if (!passwordCheck(password)) {
                cout << "�����ʽ����." << endl;
                break;
            }
            balance = balanceCheck("�������û���");
            addUser(id, name, password, balance);
            break;
        }
        case '2': {
            if (!checkFile()) {
                cout << "���û���Ϣ." << endl;
                break;
            }
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id, 1)) {
                cout << "�û�������." << endl;
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
                cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.���������û�" << endl;
                cout << "2.����ɾ���û�" << endl;
                cout << "0.����" << endl;
                cout << "������ѡ�";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string filename;
                    cout << "�������ļ�����";
                    cin >> filename;
                    importUsers(filename);
                    system("pause");
                    break;
                }
                case '2': {
                    if (!checkFile()) {
                        cout << "���û���Ϣ." << endl;
                        break;
                    }
                    string filename;
                    cout << "�������ļ�����";
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
                    cout << "�����������������." << endl;
                    break;
                }
                }
            }
            break;
        }
        case '4': {
            if (!checkFile()) {
                cout << "���û���Ϣ." << endl;
                break;
            }
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.���˺Ų���" << endl;
                cout << "2.����������" << endl;
                cout << "3.�����Ų���" << endl;
                cout << "4.��״̬����" << endl;
                cout << "0.����" << endl;
                cout << "������ѡ�";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string id;
                    cout << "�������û��˺ţ�";
                    cin >> id;
                    if (!isExist(id, 1)) {
                        cout << "�û�������." << endl;
                        break;
                    }
                    system("cls");
                    viewUser(id);
                    system("pause");
                    break;
                }
                case '2': {
                    string name;
                    cout << "�������û�������";
                    cin >> name;
                    ifstream infile1("users.dat", ios::binary | ios::in), infile2;
                    if (!infile1) {
                        cerr << "�޷����ļ�." << endl;
                        exit(1);
                    }
                    system("cls");
                    account acc;
                    userData usr;
                    int n = 0;
                    while (infile1.read((char*)&acc, sizeof(account))) {
                        infile2.open((string)acc.id + ".dat", ios::binary | ios::in);
                        if (!infile2) {
                            cerr << "�޷����ļ�." << endl;
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
                    else cout << "�û�������." << endl;
                    break;
                }
                case '3': {
                    int card;
                    cout << "�������û����ţ�";
                    cin >> card;
                    ifstream infile1("users.dat", ios::binary | ios::in), infile2;
                    if (!infile1) {
                        cerr << "�޷����ļ�." << endl;
                        exit(1);
                    }
                    system("cls");
                    account acc;
                    userData usr;
                    int n = 0;
                    while (infile1.read((char*)&acc, sizeof(account))) {
                        infile2.open((string)acc.id + ".dat", ios::binary | ios::in);
                        if (!infile2) {
                            cerr << "�޷����ļ�." << endl;
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
                    else cout << "�û�������." << endl;
                    break;
                }
                case '4': {
                    while (true) {
                        _sleep(500);
                        system("cls");
                        cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                        viewInfo();
                        cout << endl;
                        cout << "1.����" << endl;
                        cout << "2.��ʧ" << endl;
                        cout << "0.����" << endl;
                        cout << "������ѡ�";
                        if ((option = cin.get()) == '\n') {
                            continue;
                        }
                        if (option >= '0' && option <= '2') break;
                        else cout << "�����������������." << endl;
                    }
                    if (option == '0') break;
                    ifstream infile1("users.dat", ios::binary | ios::in), infile2;
                    if (!infile1) {
                        cerr << "�޷����ļ�." << endl;
                        exit(1);
                    }
                    system("cls");
                    account acc;
                    userData usr;
                    bool status = option - '1';
                    int n = 0;
                    cout << "�˺�\t\t����\t���\t����\t\t״̬" << endl;
                    while (infile1.read((char*)&acc, sizeof(account))) {
                        infile2.open((string)acc.id + ".dat", ios::binary | ios::in);
                        if (!infile2) {
                            cerr << "�޷����ļ�." << endl;
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
                    else cout << "�û�������." << endl;
                    break;
                }
                case '0': {
                    flag = false;
                    break;
                }
                default: {
                    cout << "�����������������." << endl;
                    break;
                }
                }
            }
            break;
        }
        case '5': {
            if (!checkFile()) {
                cout << "���û���Ϣ." << endl;
                break;
            }
            system("cls");
            viewAllUsers();
            system("pause");
            break;
        }
        case '6': {
            if (!checkFile()) {
                cout << "���û���Ϣ." << endl;
                break;
            }
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!idCheck(id)) {
                cout << "�˺Ÿ�ʽ����." << endl;
                break;
            }
            if (!isExist(id, 1)) {
                cout << "�û�������." << endl;
                break;
            }
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.�޸��û���" << endl;
                cout << "2.�޸��û�����" << endl;
                cout << "3.�޸��û�״̬" << endl;
                cout << "4.����һ��ͨ" << endl;
                cout << "0.����" << endl;
                cout << "������ѡ�";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string name;
                    cout << "���������û�����";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "�����ַ���������." << endl;
                        break;
                    }
                    modifyUserName(id, name);
                    break;
                }
                case '2': {
                    string password;
                    cout << "���������û����룺";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "�����ʽ����." << endl;
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
                    cout << "�����������������." << endl;
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
                cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.�޸Ĺ���Ա����" << endl;
                cout << "2.�޸Ĺ���Ա����" << endl;
                cout << "0.����" << endl;
                cout << "������ѡ�";
                if ((option = cin.get()) == '\n') {
                    continue;
                }
                switch (option) {
                case '1': {
                    string name;
                    cout << "������������";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "�����ַ���������." << endl;
                        break;
                    }
                    setName(name);
                    saveData();
                    break;
                }
                case '2': {
                    string password;
                    cout << "���������룺";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "�����ʽ����." << endl;
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
                    cout << "�����������������." << endl;
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
            cout << "�����������������." << endl;
            break;
        }
        }
    }
}
void Admin::loadData() {
    ifstream infile("admins.dat", ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "����Ա�ļ��Ѷ�ʧ��" << endl;
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