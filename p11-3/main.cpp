#include "account.h"


int main() 
{
	vector<Account*> accounts;
	vector<Account> box1;		//Account 클래스를 저장하는 벡터
	vector<SavingAccount> box2;	//SavingAccount 클래스를 저장하는 벡터
	box1.reserve(50);			//resize로 인해 좌표가 변경되는 것을 막기 위해 reserve
	box2.reserve(50);

	string cmd;
	while (cmd != "quit") {
		cin >> cmd;
		if (cmd == "add") { 
			string name, type;
			int amount;
			double interest_rate;
			cin >> name >> type >> amount >> interest_rate;
			Account* acc = CreateAccount(type, name, amount, interest_rate
				, box1, box2);
			if (acc == NULL) {
				cout << "Error: " << type << ", " << name << endl;
			} else {
				accounts.push_back(acc);
			}
		} else if (cmd == "delete") {
			string name;
			cin >> name;
			for (int i = 0; i < accounts.size(); ++i) {
				if (accounts[i]->name() == name) {
					accounts.erase(accounts.begin() + i);
					break;
				}
			}
		} else if (cmd == "show") {
			for (int i = 0; i < accounts.size(); ++i) {
				cout << accounts[i]->name() << "\t"
					<< accounts[i]->type() << "\t"
					<< accounts[i]->balance() << "\t"
					<< accounts[i]->interest_rate() << endl;
			}
		} else if (cmd == "after") {
			int n_year = 0;
			cin >> n_year;
			for (int i = 0; i < accounts.size(); ++i) {
				cout << accounts[i]->name() << "\t"
					<< accounts[i]->type() << "\t"
					<< accounts[i]->ComputeExpectedBalance(n_year) << "\t"
					<< accounts[i]->interest_rate() << endl;
			}
		/*
		} else if (cmd == "save") {
			string filename;
			SaveAccounts(accounts, filename);
		} else if (cmd == "load") {
			string filename;
			cin >> filename;
			if (LoadAccounts(filename, &accounts,box1,box2) == false) {
				cout << "Error in loading accounts from  " << filename << endl;
			}
		}
		*/
		}
	}
	 accounts.clear();
	 return 0;
}