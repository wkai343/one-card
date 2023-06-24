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
    cout << "�ѳ�ֵ " << amount << " Ԫ" << endl;
}
void User::addRecord(float amount, Record::TYPE type) {
    ofstream outfile(getId() + ".dat", ios::binary | ios::app);
    if (!outfile) {
        cerr << "�ļ���ʧ�ܣ�" << endl;
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
        cerr << "�ļ���ʧ�ܣ�" << endl;
        return;
    }
    infile.seekg(sizeof(userData));
    Record record;
    cout << "��¼���£�" << endl;
    while (infile.read((char*)&record, sizeof(Record))) {
        cout << record.ti.year << "-" << record.ti.month << "-" << record.ti.day << " " << record.ti.hour << ":" << record.ti.minute << ":" << record.ti.second << " ";
        switch (record.type) {
        case Record::RECHARGE:
            cout << "��ֵ ";
            break;
        case Record::BATH:
            cout << "ϴԡ ";
            break;
        case Record::DINE:
            cout << "���� ";
            break;
        case Record::SHOP:
            cout << "���� ";
            break;
        }
        cout << record.amount << " Ԫ" << endl;
    }
    infile.close();
}
void User::changeStatus() {
    status = !status;
    cout << "״̬�Ѹ���." << endl;
}
void User::viewInfo() {
    cout << "һ��ͨ��Ϣ��" << endl;
    cout << "�˺�: " << getId() << endl;
    cout << "����: " << getName() << endl;
    cout << "���: " << balance << endl;
    cout << "����: " << card << endl;
    cout << "״̬: " << (status ? "�ѹ�ʧ" : "����") << endl;
}
void User::openMenu() {
    int choice;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
        viewInfo();
        cout << endl;
        cout << "1.��ʧ/���" << endl;
        cout << "2.����" << endl;
        cout << "3.��ֵ" << endl;
        cout << "4.��ѯ��¼" << endl;
        cout << "5.�޸���Ϣ" << endl;
        cout << "0.�˳�" << endl;
        cout << "��ѡ��";
        cin >> choice;
        switch (choice) {
        case 1:
            changeStatus();
            break;
        case 2: {
            if (status) {
                cout << "�ѹ�ʧ���޷�����." << endl;
                system("pause");
                break;
            }

            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "1.ϴԡ" << endl;
                cout << "2.����" << endl;
                cout << "3.����" << endl;
                cout << "0.�˳�" << endl;
                cout << "��ѡ��";
                cin >> choice;
                switch (choice) {
                case 1: {
                    cout << "���������ѽ�";
                    float amount;
                    cin >> amount;
                    if (balance >= amount) {
                        consume(amount);
                        addRecord(amount, Record::BATH);
                        saveData();
                    }
                    else {
                        cout << "����!" << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "���������ѽ�";
                    float amount;
                    cin >> amount;
                    if (balance >= amount) {
                        consume(amount);
                        addRecord(amount, Record::DINE);
                        saveData();
                    }
                    else {
                        cout << "����!" << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "���������ѽ�";
                    float amount;
                    cin >> amount;
                    if (balance >= amount) {
                        consume(amount);
                        addRecord(amount, Record::SHOP);
                        saveData();
                    }
                    else {
                        cout << "����!" << endl;
                    }
                    break;
                }
                case 0:
                    flag = false;
                    break;
                default:
                    cout << "�����������������." << endl;
                    break;
                }
            }
            break;
        }
        case 3: {
            if (status) {
                cout << "�ѹ�ʧ���޷���ֵ." << endl;
                system("pause");
                break;
            }
            cout << "�������ֵ��";
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
                cout << "1.�޸�����" << endl;
                cout << "2.�޸�����" << endl;
                cout << "0.�˳�" << endl;
                cout << "��ѡ��";
                cin >> choice;
                switch (choice) {
                case 1: {
                    string password;
                    cout << "�����������룺";
                    cin >> password;
                    if (!passwordCheck(password)) {
                        cout << "�����ʽ����." << endl;
                        break;
                    }
                    setPassword(password);
                    saveData();
                    cout << "�������޸�." << endl;
                    break;
                }
                case 2: {
                    string name;
                    cout << "��������������";
                    cin >> name;
                    if (!nameCheck(name)) {
                        cout << "������ʽ����." << endl;
                        break;
                    }
                    setName(name);
                    saveData();
                    cout << "�������޸�." << endl;
                    break;
                }
                case 0:
                    flag = false;
                    break;
                default:
                    cout << "�����������������." << endl;
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
            cout << "�����������������." << endl;
            break;
        }
    }
}
void User::loadData() {
    ifstream infile("users.dat", ios::binary | ios::in);
    if (!infile.is_open()) {
        cout << "�û��ļ��Ѷ�ʧ��" << endl;
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
        cout << "�ļ���ʧ�ܣ�" << endl;
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
        cout << "�ļ���ʧ�ܣ�" << endl;
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
        cerr << "�ļ���ʧ�ܣ�" << endl;
        exit(1);
    }
    ofstream outfile2("temp.dat", ios::binary | ios::out);
    if (!outfile2) {
        cerr << "�ļ���ʧ�ܣ�" << endl;
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