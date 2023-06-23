#include"Admin.h"
#include"User.h"
#include"isExist.h"
#include"check.h"
#include<ctime>
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
    string id,name;
    int m = 0, n = 0;
    for (; infile >> id >>name; ++n) {
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
    //�ж��ļ��Ƿ�Ϊ��
    infile.seekg(0, ios::end);
    if (infile.tellg() == 0) {
        cout << "���û���Ϣ." << endl;
        infile.close();
        return;
    }
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
    int option;
    while (true) {
        _sleep(1000);
        system("cls");
        cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
        viewInfo();
        cout << "1.����û�" << endl;
        cout << "2.���������û�" << endl;
        cout << "3.ɾ���û�" << endl;
        cout << "4.����ɾ���û�" << endl;
        cout << "5.�鿴�û�" << endl;
        cout << "6.�鿴�����û�" << endl;
        cout << "7.�޸��û���Ϣ" << endl;
        cout << "8.�޸Ĺ���Ա��Ϣ" << endl;
        cout << "0.�˳�" << endl;
        cout << "������ѡ�";
        cin >> option;
        switch (option) {
        case 1: {
            string id, name, password;
            float balance;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (isExist(id, 1)) {
                cout << "�û��Ѵ���." << endl;
                _sleep(1000);
                break;
            }
            if (!idCheck(id)) {
                cout << "�˺Ÿ�ʽ����." << endl;
                _sleep(1000);
                break;
            }
            cout << "�������û�������";
            cin >> name;
            if (!nameCheck(name)) {
                cout << "�����ַ���������." << endl;
                _sleep(1000);
                break;
            }
            cout << "�������û����룺";
            cin >> password;
            if (!passwordCheck(password)) {
                cout << "�����ʽ����." << endl;
                _sleep(1000);
                break;
            }
            balance = balanceCheck("�������û���");
            addUser(id, name, password, balance);
            break;
        }
        case 2: {
            string filename;
            cout << "�������ļ�����";
            cin >> filename;
            importUsers(filename);
            system("pause");
            break;
        }
        case 3: {
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id, 1)) {
                cout << "�û�������." << endl;
                _sleep(1000);
                break;
            }
            deleteUser(id);
            break;
        }
        case 4: {
            string filename;
            cout << "�������ļ�����";
            cin >> filename;
            deleteUsers(filename);
            system("pause");
            break;
        }
        case 5: {
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id, 1)) {
                cout << "�û�������." << endl;
                _sleep(1000);
                break;
            }
            viewUser(id);
            system("pause");
            break;
        }
        case 6: {
            viewAllUsers();
            system("pause");
            break;
        }
        case 7: {
            string id;
            int option;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!idCheck(id)) {
                cout << "�˺Ÿ�ʽ����." << endl;
                _sleep(1000);
                break;
            }
            if (!isExist(id, 1)) {
                cout << "�û�������." << endl;
                _sleep(1000);
                break;
            }
            bool flag = true;
            while (flag) {
                system("cls");
                cout << "1.�޸��û���" << endl;
                cout << "2.�޸��û�����" << endl;
                cout << "3.�޸��û�״̬" << endl;
                cout << "4.����һ��ͨ" << endl;
                cout << "0.����" << endl;
                cout << "������ѡ�";
                cin >> option;
                switch (option) {
                case 1: {
                    string name;
                    cout << "���������û�����";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "�����ַ���������." << endl;
                        _sleep(1000);
                        break;
                    }
                    modifyUserName(id, name);
                    break;
                }
                case 2: {
                    string password;
                    cout << "���������û����룺";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "�����ʽ����." << endl;
                        _sleep(1000);
                        break;
                    }
                    modifyUserPassword(id, password);
                    break;
                }
                case 3: {
                    changeUserStatus(id);
                    break;
                }
                case 4: {
                    reissueCard(id);
                    break;
                }
                case 0: {
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
        case 8: {
            int option;
            bool flag = true;
            while (flag) {
                system("cls");
                cout << "1.�޸Ĺ���Ա����" << endl;
                cout << "2.�޸Ĺ���Ա����" << endl;
                cout << "0.����" << endl;
                cout << "������ѡ�";
                cin >> option;
                switch (option) {
                case 1: {
                    string name;
                    cout << "������������";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "�����ַ���������." << endl;
                        _sleep(1000);
                        break;
                    }
                    setName(name);
                    saveData();
                    break;
                }
                case 2: {
                    string password;
                    cout << "���������룺";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "�����ʽ����." << endl;
                        _sleep(1000);
                        break;
                    }
                    setPassword(password);
                    saveData();
                    break;
                }
                case 0: {
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
        case 0: {
            system("cls");
            cout << "��ӭ�´�ʹ�ã�" << endl;
            system("pause");
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