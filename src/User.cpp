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
void User::viewRecord(const Record& record) {
    cout << record.ti << ' ';
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
void User::viewRecords() {
    char choice;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
        viewInfo();
        cout << endl;
        cout << "1.ȫ����¼" << endl;
        cout << "2.�����Ͳ�ѯ" << endl;
        cout << "3.������ѯ" << endl;
        cout << "4.��ʱ���ѯ" << endl;
        cout << "0.����" << endl;
        cout << "��ѡ��";
        if ((choice = cin.get()) == '\n') {
            continue;
        }
        switch (choice) {
        case '1': {
            system("cls");
            ifstream infile(getId() + ".dat", ios::binary | ios::in);
            if (!infile) {
                cerr << "�ļ���ʧ�ܣ�" << endl;
                exit(1);
            }
            Record record;
            infile.seekg(-sizeof(Record), ios::end);
            for (int i = 0; i < recordNum; i++) {
                infile.read((char*)&record, sizeof(Record));
                viewRecord(record);
                infile.seekg(-2 * sizeof(Record), ios::cur);
            }
            infile.close();
            system("pause");
            break;
        }
        case '2': {
            system("cls");
            char type;
            while (true) {
                cout << "1.��ֵ" << endl;
                cout << "2.����" << endl;
                cout << "3.ϴԡ" << endl;
                cout << "4.����" << endl;
                cout << "5.����" << endl;
                cout << "0.����" << endl;
                cout << "��ѡ��";
                if ((type = cin.get()) == '\n') {
                    continue;
                }
                if (type >= '0' && type <= '5') {
                    break;
                }
                else {
                    cout << "����������������룡" << endl;
                }
            }
            if (type == '0')break;
            ifstream infile(getId() + ".dat", ios::binary | ios::in);
            if (!infile) {
                cerr << "�ļ���ʧ�ܣ�" << endl;
                exit(1);
            }
            system("cls");
            Record record;
            infile.seekg(sizeof(userData));
            while (infile.read((char*)&record, sizeof(Record))) {
                if (type == '1' && record.type == Record::RECHARGE) {
                    viewRecord(record);
                }
                else if (type == '2' && (record.type == Record::BATH || record.type == Record::DINE || record.type == Record::SHOP)) {
                    viewRecord(record);
                }
                else if (type == '3' && record.type == Record::BATH) {
                    viewRecord(record);
                }
                else if (type == '4' && record.type == Record::DINE) {
                    viewRecord(record);
                }
                else if (type == '5' && record.type == Record::SHOP) {
                    viewRecord(record);
                }
            }
            infile.close();
            system("pause");
            break;
        }
        case '3': {
            float amount;
            cout << "�������";
            cin >> amount;
            ifstream infile(getId() + ".dat", ios::binary | ios::in);
            if (!infile) {
                cerr << "�ļ���ʧ�ܣ�" << endl;
                exit(1);
            }
            system("cls");
            Record record;
            infile.seekg(-sizeof(Record), ios::end);
            for (int i = 0; i < recordNum; i++) {
                infile.read((char*)&record, sizeof(Record));
                if (record.amount == amount) {
                    viewRecord(record);
                }
                infile.seekg(-2 * sizeof(Record), ios::cur);
            }
            infile.close();
            system("pause");
            break;
        }
        case '4': {
            Time time1, time2;
            cout << "��������ʼʱ�䣺" << endl;
            cout << "�꣺";
            cin >> time1.year;
            cout << "�£�";
            cin >> time1.month;
            if(time1.month < 1 || time1.month > 12) {
                cout << "����������������룡" << endl;
                break;
            }
            cout << "�գ�";
            cin >> time1.day;
            if(time1.day < 1 || time1.day > 31) {
                cout << "����������������룡" << endl;
                break;
            }
            time1.hour = 0;
            time1.minute = 0;
            time1.second = 0;
            cout << "���������ʱ�䣺" << endl;
            cout << "�꣺";
            cin >> time2.year;
            cout << "�£�";
            cin >> time2.month;
            if(time2.month < 1 || time2.month > 12) {
                cout << "����������������룡" << endl;
                break;
            }
            cout << "�գ�";
            cin >> time2.day;
            if(time2.day < 1 || time2.day > 31) {
                cout << "����������������룡" << endl;
                break;
            }
            time2.hour = 23;
            time2.minute = 59;
            time2.second = 59;
            ifstream infile(getId() + ".dat", ios::binary | ios::in);
            if (!infile) {
                cerr << "�ļ���ʧ�ܣ�" << endl;
                exit(1);
            }
            system("cls");
            Record record;
            infile.seekg(sizeof(userData));
            while (infile.read((char*)&record, sizeof(Record))) {
                if (record.ti >= time1 && record.ti <= time2) {
                    viewRecord(record);
                }
            }
            infile.close();
            system("pause");
            break;
        }
        case '0':
            return;
        default:
            cout << "����������������룡" << endl;
            break;
        }
    }
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
    char choice;
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
        cout << "6.������Ϣ" << endl;
        cout << "0.�˳�" << endl;
        cout << "��ѡ��";
        if ((choice = cin.get()) == '\n') {
            continue;
        }
        switch (choice) {
        case '1':
            changeStatus();
            saveData();
            break;
        case '2': {
            if (status) {
                cout << "�ѹ�ʧ���޷�����." << endl;
                system("pause");
                break;
            }

            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.ϴԡ" << endl;
                cout << "2.����" << endl;
                cout << "3.����" << endl;
                cout << "0.�˳�" << endl;
                cout << "��ѡ��";
                if ((choice = cin.get()) == '\n') {
                    continue;
                }
                switch (choice) {
                case '1': {
                    float amount;
                    amount = balanceCheck("���������ѽ�");
                    if (balance >= amount) {
                        consume(amount);
                        if (amount > 0) addRecord(amount, Record::BATH);
                        saveData();
                    }
                    else {
                        cout << "����!" << endl;
                    }
                    break;
                }
                case '2': {
                    float amount;
                    amount = balanceCheck("���������ѽ�");
                    if (balance >= amount) {
                        consume(amount);
                        if (amount > 0) addRecord(amount, Record::DINE);
                        saveData();
                    }
                    else {
                        cout << "����!" << endl;
                    }
                    break;
                }
                case '3': {
                    float amount;
                    amount = balanceCheck("���������ѽ�");
                    if (balance >= amount) {
                        consume(amount);
                        if (amount > 0) addRecord(amount, Record::SHOP);
                        saveData();
                    }
                    else {
                        cout << "����!" << endl;
                    }
                    break;
                }
                case '0':
                    flag = false;
                    break;
                default:
                    cout << "�����������������." << endl;
                    break;
                }
            }
            break;
        }
        case '3': {
            if (status) {
                cout << "�ѹ�ʧ���޷���ֵ." << endl;
                system("pause");
                break;
            }
            float amount;
            amount = balanceCheck("�������ֵ��");
            recharge(amount);
            if (amount > 0) addRecord(amount, Record::RECHARGE);
            saveData();
            break;
        }
        case '4':
            system("cls");
            viewRecords();
            break;
        case '5': {
            system("cls");
            bool flag = true;
            while (flag) {
                _sleep(500);
                system("cls");
                cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
                viewInfo();
                cout << endl;
                cout << "1.�޸�����" << endl;
                cout << "2.�޸�����" << endl;
                cout << "0.�˳�" << endl;
                cout << "��ѡ��";
                if ((choice = cin.get()) == '\n') {
                    continue;
                }
                switch (choice) {
                case '1': {
                    string password;
                    cout << "����������룺";
                    cin >> password;
                    if (password != getPassword()) {
                        cout << "�������." << endl;
                        break;
                    }
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
                case '2': {
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
                case '0':
                    flag = false;
                    break;
                default:
                    cout << "�����������������." << endl;
                    break;
                }
            }
            break;
        }
        case '6':
            exportRecords();
            break;
        case '0': {
            return;
            break;
        }
        default:
            cout << "�����������������." << endl;
            break;
        }
    }
}
void User::exportRecords() {
    ofstream outfile(getId()+".txt");
    if (!outfile.is_open()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
        return;
    }
    outfile << "ѧ�ţ�" << getId() << endl;
    outfile << "������" << getName() << endl;
    outfile << "���ţ�" << getCard() << endl;
    outfile << "��" << getBalance() << endl;
    outfile << "״̬��" << (getStatus() ? "�ѹ�ʧ" : "����") << endl;
    outfile << "��¼��" << endl;
    outfile << "ʱ��\t\t\t\t���\t\t����" << endl;
    Record record;
    ifstream infile(getId() + ".dat", ios::binary | ios::in);
    if (!infile.is_open()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
        return;
    }
    infile.seekg(sizeof(userData), ios::beg);
    while (infile.read((char*)&record, sizeof(Record))) {
        outfile << record.ti << "\t" << record.amount << "\t\t";
        switch (record.type) {
        case Record::RECHARGE:
            outfile << "��ֵ";
            break;
        case Record::BATH:
            outfile << "ϴԡ";
            break;
        case Record::DINE:
            outfile << "����";
            break;
        case Record::SHOP:
            outfile << "����";
            break;
        }
        outfile << endl;
    }
    outfile.close();
    cout << "�����ɹ���" << endl;
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