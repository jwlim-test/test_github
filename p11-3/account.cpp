#include "account.h"

Account::Account(const std::string& name, unsigned int balance, double interest_rate){
	name_ = name;
	balance_ = balance;
	interest_rate_ = interest_rate;
}

Account::~Account(){}

void Account::Deposit(unsigned int amount){
	balance_ += amount;
}

bool Account::Withdraw(unsigned int amount){
	if (amount > balance_) return false;

	balance_ -= amount;
	return true;
}

unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const{
	double ret = balance_;
	for (int i = 0; i<n_years_later; ++i){
		ret += balance_ * interest_rate_;
	}
	return static_cast<unsigned int>(ret);
}

SavingAccount::SavingAccount(const std::string& name, int balance, double interest_rate)
	: Account(name,balance,interest_rate) {}

SavingAccount::~SavingAccount(){}

unsigned int SavingAccount::ComputeExpectedBalance( unsigned int n_years_later) const{
	double ret = balance_;
	for (int i = 0; i < n_years_later; ++i){
		ret *= (1 + interest_rate_);
	}
	return static_cast<unsigned int>(ret);
}

Account* CreateAccount(const std::string& type,
    const std::string& name, unsigned int balance, double interest_rate){
		if (type == "normal"){
			Account* ret = new Account(name,balance,interest_rate);
			return ret;
		}
		else{
			SavingAccount* ret = new SavingAccount(name,balance,interest_rate);
			return ret;
		}
}
