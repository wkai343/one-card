#include"check.h"
bool idCheck(string id) {
    if (id.length() != 10) {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(id[i])) {
            return false;
        }
    }
    return true;
}
bool passwordCheck(string password) {
    if (password.length() < 9 || password.length() > 16) {
        return false;
    }
    for (int i = 0; i < password.length(); i++) {
        if (!isalnum(password[i])) {
            return false;
        }
    }
    return true;
}
bool nameCheck(string name) {
    if (name.length() > 20) {
        return false;
    }
    return true;
}
float balanceCheck(const char* prompt) {
    cout << prompt;
    float balance;
    while (true) {
        cin >> balance;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "����������������룺";
        }
        else {
            if (balance < 0) {
                cout << "����������������룺";
                continue;
            }
            cin.ignore(1024, '\n');
            return balance;
        }
    }
    return 0;
}
int cardCheck(const char* prompt) {
    cout << prompt;
    int card;
    while (true) {
        cin >> card;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "����������������룺";
        }
        else {
            if (card < 0) {
                cout << "����������������룺";
                continue;
            }
            cin.ignore(1024, '\n');
            return card;
        }
    }
    return 0;
}