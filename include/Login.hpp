#pragma once
#include <fstream>
#include <cstdlib>
#include "Admin.h"
#include "User.h"
using namespace std;
bool isExist(string id) {
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
void savePassword(Admin admin) {
    ofstream outfile("admin.txt", ios::trunc);
    if (!outfile) {
        cerr << "Error: could not open file admin.txt" << endl;
        exit(1);
    }
    outfile << admin.getPassword() << endl;
    outfile.close();
}
void savePassword(User user) {
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
        if (currentUsername == user.getId()) {
            outputFile << user.getId() << ' ' << user.getPassword() << '\n';
        }
        else {
            outputFile << line << '\n';
        }
    }
    inputFile.close();
    outputFile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}
bool adminLogin(string password) {
    ifstream infile("admin.txt");
    if (!infile) {
        cerr << "Error: could not open file admin.txt" << endl;
        exit(1);
    }
    string adminPassword;
    getline(infile, adminPassword);
    infile.close();
    if (password == adminPassword) return true;
    return false;
}
bool userLogin(string id, string password) {
    ifstream infile("users.txt");
    if (!infile) {
        cerr << "Error: could not open file users.txt" << endl;
        exit(1);
    }
    string idFromFile, passwordFromFile;
    while (infile >> idFromFile >> passwordFromFile) {
        if (idFromFile == id && passwordFromFile == password) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}
int checkId(string id) {
    if (id.length() == 1 && id[0] == '0') {
        return 1;
    }
    if (id.length() != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(id[i])) {
            return 0;
        }
    }
    if (!isExist(id)) return 3;
    return 2;
}
int Login() {
    string id, password;
    while (true) {
        _sleep(500);
        system("cls");
        cout << "ÇëÊäÈëÕËºÅ£º";
        cin >> id;
        int check;
        if ((check = checkId(id)) == 0) {
            cout << "ÕËºÅ¸ñÊ½´íÎó£¡" << endl;
            continue;
        }
        else if (check == 3) {
            cout << "ÕËºÅ²»´æÔÚ£¡" << endl;
            continue;
        }
        cout << "ÇëÊäÈëÃÜÂë£º";
        cin >> password;
        if (check == 1) {
            if (adminLogin(password)) {
                {
                    cout << "µÇÂ½³É¹¦£¡" << endl;
                }
                fstream file(id + ".txt");
                if (!file) {
                    cerr << "Error: could not open file " << id << ".txt" << endl;
                    exit(1);
                }
                string name;
                file >> name;
                Admin admin(id, name, password);
                admin.openMenu();
                file << name;
                file.close();
                savePassword(admin);
            }
            else cout << "ÃÜÂë´íÎó£¡" << endl;
        }

        else {
            if (userLogin(id, password)) {
                cout << "µÇÂ½³É¹¦£¡" << endl;
                string fileName = id + ".txt";
                ifstream infile(fileName);
                if (!infile) {
                    cerr << "Error: could not open infile " << id << ".txt" << endl;
                    exit(1);
                }
                string name;
                float balance;
                int card;
                bool status;
                infile >> name >> balance >> card >> status;
                infile.close();
                User user(id, name, password, balance, card, status);
                user.openMenu();
                string temp = name + " " + to_string(user.getBalance()) + " " + to_string(user.getCard()) + " " + to_string(user.getStatus());
                ofstream outfile(fileName, ios::trunc);
                if (!outfile) {
                    cerr << "Error: could not open outfile " << id << ".txt" << endl;
                    exit(1);
                }
                outfile << temp;
                outfile.close();
                savePassword(user);
            }
            else cout << "ÃÜÂë´íÎó£¡" << endl;
        }
    }
}