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
            cout << "���˺��Ѵ���." << endl;
            return;
        }
        infile >> temp;
    }
    ofstream outfile(id + ".txt");
    if (!outfile) {
        cout << "��ʧ��." << endl;
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
    cout << "�û������." << endl;
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
    cout << "�û���ɾ��." << endl;
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
    cout << "�˺ţ�" << id << endl;
    cout << "������" << name << endl;
    cout << "��" << balance << endl;
    cout << "���ţ�" << card << endl;
    cout << "״̬��" << (status ? "�ѹ�ʧ" : "����") << endl;
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
    cout << "�û���Ϣ���޸�." << endl;
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
        cout << "�޸ĳɹ�." << endl;
    }
    else {
        cout << "�˺Ų�����." << endl;
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
    cout << "�û�״̬���޸�." << endl;
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
    cout << "�Ѳ���." << endl;
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
        cout << "2.ɾ���û�" << endl;
        cout << "3.�鿴�û�" << endl;
        cout << "4.�鿴�����û�" << endl;
        cout << "5.�޸��û�����" << endl;
        cout << "6.�޸��û�����" << endl;
        cout << "7.�޸��û�״̬" << endl;
        cout << "8.����" << endl;
        cout << "9.�޸Ĺ���Ա��Ϣ" << endl;
        cout << "0.�˳�" << endl;
        cout << "������ѡ�";
        cin >> option;
        switch (option) {
        case 1: {
            string id, name, password;
            float balance;
            cout << "�������û��˺ţ�";
            cin >> id;
            cout << "�������û�������";
            cin >> name;
            cout << "�������û����룺";
            cin >> password;
            cout << "�������û���";
            cin >> balance;
            addUser(id, name, password, balance);
            break;
        }
        case 2: {
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id)) {
                cout << "�û�������." << endl;
                system("pause");
                break;
            }
            deleteUser(id);
            break;
        }
        case 3: {
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id)) {
                cout << "�û�������." << endl;
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
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id)) {
                cout << "�û�������." << endl;
                system("pause");
                break;
            }
            cout << "�������û�������";
            cin >> name;
            modifyUserName(id, name);
            break;
        }
        case 6: {
            string id, password;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id)) {
                cout << "�û�������." << endl;
                system("pause");
                break;
            }
            cout << "�������û����룺";
            cin >> password;
            modifyUserPassword(id, password);
            break;
        }
        case 7: {
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id)) {
                cout << "�û�������." << endl;
                system("pause");
                break;
            }
            changeUserStatus(id);
            break;
        }
        case 8: {
            string id;
            cout << "�������û��˺ţ�";
            cin >> id;
            if (!isExist(id)) {
                cout << "�û�������." << endl;
                system("pause");
                break;
            }
            reissueCard(id);
            break;
        }
        case 9: {
            string name, password;
            cout << "���������Ա������";
            cin >> name;
            cout << "���������Ա���룺";
            cin >> password;
            modifyInfo(name, password);
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