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
        cout << "������ " << amount << " Ԫ" << endl;
    }
    else {
        cout << "����!" << endl;
    }
}
void User::recharge(float amount) {
    balance += amount;
}
void User::viewInfo() {
    cout << "һ��ͨ��Ϣ��" << endl;
    cout << "�˺�: " << getId() << endl;
    cout << "����: " << getName() << endl;
    cout << "���: " << balance << endl;
    cout << "����: " << card << endl;
    cout << "״̬: " << (status ? "�ѹ�ʧ" : "����") << endl;
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
    cout << "״̬�Ѹ���." << endl;
}
void User::openMenu() {
    int choice;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "һ��ͨ��Ϣ����ϵͳ" << endl << endl;
        viewInfo();
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
            if(status) {
                cout << "�ѹ�ʧ���޷�����." << endl;
                system("pause");
                break;
            }
            float amount;
            cout << "���������ѽ�";
            cin >> amount;
            consume(amount);
            addRecord(amount, "����");
            break;
        }
        case 3: {
            if(status) {
                cout << "�ѹ�ʧ���޷���ֵ." << endl;
                system("pause");
                break;
            }
            cout << "�������ֵ��";
            float amount;
            cin >> amount;
            recharge(amount);
            addRecord(amount, "��ֵ");
            break;
        }
        case 4:
            viewRecords();
            system("pause");
            break;
        case 5: {
            string newName, newPassword;
            cout << "��������������";
            cin >> newName;
            cout << "�����������룺";
            cin >> newPassword;
            modifyInfo(newName, newPassword);
            break;
        }
        case 0: {
            system("cls");
            cout << "��ӭ�´�ʹ�ã�" << endl;
            system("pause");
            return;
            break;
        }
        default:
            cout << "�����������������." << endl;
            break;
        }
    }
}