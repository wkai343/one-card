#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
struct account {
    char id[11];
    char password[17]{};
};
bool nameCheck(string name) {
    if (name.length() > 20) {
        return false;
    }
    return true;
}
int main(){
    ifstream infile("�����2203.txt", ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "�ļ������ڣ�" << endl;
        return 0;
    }
    ofstream outfile1("users.dat", ios::app | ios::binary);
    if (!outfile1) {
        cerr << "�ļ���ʧ�ܣ�" << endl;
        return 0;
    }
    ofstream outfile2;
    int m = 0, n = 0;
    string id,name;
    for (; infile >> id >> name;++n) {
        // if (nameCheck(name)) {
        //     cout << "��" << n + 1 << "��������ʽ����������" << endl;
        //     ++m;
        //     continue;
        // }
        cout << "��" << n + 1 << "�У�" << id << " " << name << endl;
        cout<<name.length()<<endl;
    }
    infile.close();
    outfile1.close();
    system("pause");
    return 0;
}