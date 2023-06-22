#include"isExist.h"
#include"account.h"
int isExist(string id, bool check) {
    string str;
    if (check) str = "users.dat";
    else str = "admins.dat";
    ifstream infile(str);
    if (!infile) {
        cerr << "Error: could not open infile " << str << endl;
        exit(1);
    }
    int n = 1;
    account acc;
    while (infile.read((char*)&acc, sizeof(account))) {
        if (acc.id == id) {
            infile.close();
            return n;
        }
        ++n;
    }
    infile.close();
    return 0;
}