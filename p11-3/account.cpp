#include "account.h"

Account::Account(const string& name, unsigned int balance, double interest_rate){
	name_ = name;
	balance_ = balance;
	interest_rate_ = interest_rate;
}

Account::~Account(){;}

void Account::Deposit(unsigned int amount){
	balance_ += amount;
}

bool Account::Withdraw(unsigned int amount){
	if(amount > balance_) return false;
	else{
		balance_ -= amount;
		return true;
	}
}

unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const{
	double temp = balance_;
	for(int i = 0; i<n_years_later; ++i){
		temp += balance_ * interest_rate_;
	}
	return temp;
}

SavingAccount::SavingAccount(const string& name, int balance, double interest_rate)
	: Account(name,balance,interest_rate) {;}

SavingAccount::~SavingAccount(){;}

unsigned int SavingAccount::ComputeExpectedBalance( unsigned int n_years_later) const{
	double temp = balance_;
	for(int i = 0; i < n_years_later; ++i){
		temp *= (1 + interest_rate_);
	}
	return temp;
}

Account* CreateAccount(const string& type,
    const string& name, unsigned int balance, double interest_rate
	, vector<Account>& box1, vector<SavingAccount>& box2){
		if(type == "normal"){
			Account temp(name,balance,interest_rate);
			box1.push_back(temp);
			return &box1[box1.size() - 1];
		}
		else{
			SavingAccount temp(name,balance,interest_rate);
			box2.push_back(temp);
			return &box2[box2.size() - 1];
		}
}

/*
bool SaveAccounts(const vector<Account*>& accounts, const string& filename){
	ofstream f;
	
	f.open(filename.c_str());
	if(f.is_open()){
		for(int i = 0; i < accounts.size(); ++i){
			f << accounts[i]->name() << "\t" 
			  << accounts[i]->type() << "\t" 
			  << accounts[i]->balance() << "\t" 
			  << accounts[i]->interest_rate();
			if(i != accounts.size() - 1) f << endl;
			else ;
		}
		f.close();
		return true;
	}else{
		return false;
	}
}

bool LoadAccounts(const string& filename, vector<Account*>* accounts
				  ,vector<Account>& box1, vector<SavingAccount>& box2){
	ifstream f;
	
	f.open(filename.c_str());
	if(f.is_open()){
		box1.clear();
		box2.clear();
		accounts->clear();
		while(f.good()){
			string name, type;
			int amount;
			double interest_rate;
			f >> name >> type >> amount >> interest_rate;
			Account* temp = CreateAccount(type,name,amount,interest_rate,box1,box2);
			accounts->push_back(temp);
		}
		f.close();
		return true;
	}else{
		return false;
	}

}
*/