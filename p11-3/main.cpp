#include <iostream>
#include "account.h"

using namespace std;

int main() {
  vector<Account*> accounts;
  string cmd;
  while (cmd != "quit") {
    cin >> cmd;
    // 사용자 정보를 입력받아서 새로은 Accout* 를 만들어 vector에 push_back시킴 
    if (cmd == "add") {
      string name, type;
      int amount;
      double interest_rate;
      cin >> name >> type >> amount >> interest_rate;
      Account* acc = CreateAccount(type, name, amount, interest_rate);
      if (acc == NULL) {
        cout << "Error: " << type << ", " << name << endl;
      } else {
        accounts.push_back(acc);
      }
    } else if (cmd == "delete") {// name을 입력받아 찾고 delete시킴 
      string name;
      cin >> name;
      for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->name() == name) {
          accounts.erase(accounts.begin() + i);
          break;
        }
      }
    } else if (cmd == "show") {// accouts에 저장되어있는 정보를 출력 
      for (int i = 0; i < accounts.size(); ++i) {
        cout << accounts[i]->name() << "\t"
          << accounts[i]->type() << "\t"
          << accounts[i]->balance() << "\t"
          << accounts[i]->interest_rate() << endl;
      }
    } else if (cmd == "after") {//n년후에 사용자정보를 출력 
      int n_year = 0;
      cin >> n_year;
      for (int i = 0; i < accounts.size(); ++i) {
        cout << accounts[i]->name() << "\t"
          << accounts[i]->type() << "\t"
          << accounts[i]->ComputeExpectedBalance(n_year) << "\t"
          << accounts[i]->interest_rate() << endl;
      }
    }
  }
  return 0;
}
