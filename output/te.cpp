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
    ifstream infile("计算机2203.txt", ios::binary | ios::in);
    if (!infile.is_open()) {
        cerr << "文件不存在！" << endl;
        return 0;
    }
    ofstream outfile1("users.dat", ios::app | ios::binary);
    if (!outfile1) {
        cerr << "文件打开失败！" << endl;
        return 0;
    }
    ofstream outfile2;
    int m = 0, n = 0;
    string id,name;
    for (; infile >> id >> name;++n) {
        // if (nameCheck(name)) {
        //     cout << "第" << n + 1 << "行姓名格式错误，已跳过" << endl;
        //     ++m;
        //     continue;
        // }
        cout << "第" << n + 1 << "行：" << id << " " << name << endl;
        cout<<name.length()<<endl;
    }
    infile.close();
    outfile1.close();
    system("pause");
    return 0;
}