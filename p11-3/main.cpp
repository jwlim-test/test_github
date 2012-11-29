#include <iostream>
#include <string>
#include <vector>
#include "account.h"

using namespace std;

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate);

int main(void) {
    vector<Account*> accounts;
    string cmd;
    while (cmd != "quit") {
        cin >> cmd;
        if (cmd == "add") {        //add 하면 계좌를 추가한다. 
            string name, type;
            int amount;
            double interest_rate;
            cin >> name >> type >> amount >> interest_rate;
            Account* acc = CreateAccount(type, name, amount, interest_rate);
            if (acc == NULL) {
                cout << "Error: " << type << ", " << name << endl;
            } 
            else {
                accounts.push_back(acc);
            }
        } 
        else if (cmd == "delete") {  //delete 시 추가된 계좌중에서 그이름인것을 찾아 삭제한다. 
            string name;
            cin >> name;
            for (int i = 0; i < accounts.size(); ++i) {
                if (accounts[i]->name() == name) {
                    accounts.erase(accounts.begin() + i);
                        break;
                }
            }
        } 
        else if (cmd == "show") {   //show 하면 현재 추가되어있는 계좌들을 모두보여준다. 
            for (int i = 0; i < accounts.size(); ++i) {
                cout << accounts[i]->name() << "\t"
                << accounts[i]->type() << "\t"
                << accounts[i]->balance() << "\t"
                << accounts[i]->interest_rate() << endl;
            }
        } 
        else if (cmd == "after") {   //after하고 숫자를 입력하면 그 숫자만큼 지난후에 계좌의 상황을 보여준다. 
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

// Accout함수는 Account*를 return 해주어야하는데 그냥 Accoun*를선언하고 return 하면 scope특성때문에 사라지므로
// new를 이용해 return 해주어야 사라지지 않는다!! 

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate){
    if(type == "normal"){      //normal계좌생성 
        Account* normal_account= new Account(name, balance, interest_rate);
        return  normal_account;
    }
    else if(type == "saving"){     //saving계좌생성 
        SavingAccount* saving_account = new SavingAccount(name, balance, interest_rate);
        return saving_account;
    }
    else {
        return 0;
    }
}
