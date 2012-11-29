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
        if (cmd == "add") {        //add �ϸ� ���¸� �߰��Ѵ�. 
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
        else if (cmd == "delete") {  //delete �� �߰��� �����߿��� ���̸��ΰ��� ã�� �����Ѵ�. 
            string name;
            cin >> name;
            for (int i = 0; i < accounts.size(); ++i) {
                if (accounts[i]->name() == name) {
                    accounts.erase(accounts.begin() + i);
                        break;
                }
            }
        } 
        else if (cmd == "show") {   //show �ϸ� ���� �߰��Ǿ��ִ� ���µ��� ��κ����ش�. 
            for (int i = 0; i < accounts.size(); ++i) {
                cout << accounts[i]->name() << "\t"
                << accounts[i]->type() << "\t"
                << accounts[i]->balance() << "\t"
                << accounts[i]->interest_rate() << endl;
            }
        } 
        else if (cmd == "after") {   //after�ϰ� ���ڸ� �Է��ϸ� �� ���ڸ�ŭ �����Ŀ� ������ ��Ȳ�� �����ش�. 
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

// Accout�Լ��� Account*�� return ���־���ϴµ� �׳� Accoun*�������ϰ� return �ϸ� scopeƯ�������� ������Ƿ�
// new�� �̿��� return ���־�� ������� �ʴ´�!! 

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate){
    if(type == "normal"){      //normal���»��� 
        Account* normal_account= new Account(name, balance, interest_rate);
        return  normal_account;
    }
    else if(type == "saving"){     //saving���»��� 
        SavingAccount* saving_account = new SavingAccount(name, balance, interest_rate);
        return saving_account;
    }
    else {
        return 0;
    }
}
