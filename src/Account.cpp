#include"Account.h"
Account::Account(string id, std::string name, string password) :id(id), name(name), password(password) {
}
string Account::getId() {
    return id;
}
std::string Account::getName() {
    return name;
}
string Account::getPassword() {
    return password;
}
void Account::setName(std::string name) {
    this->name = name;
}
void Account::setPassword(string password) {
    this->password = password;
}
void Account::modifyInfo(string name, string password) {
    setName(name);
    setPassword(password);
    cout << "信息已更改." << endl;
}
