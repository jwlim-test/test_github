#include "account.h"
  Account::Account(const string& name, unsigned int balance, double interest_rate) : name_(name), balance_(balance), interest_rate_(interest_rate)
  {
	}
    Account::~Account()
    {
		delete this;
	}
  void Account::Deposit(unsigned int amount)
  {
		balance_+=amount;
	}
  bool Account::Withdraw(unsigned int amount)
  {
		if (balance_ < amount)
			return 0;
		balance_-=amount;
		return 1;
	}
  unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const    
  {
		return int(balance_+interest_rate_*double(balance_*n_years_later));
	}
  SavingAccount::SavingAccount(const string& name, int balance, double interest_rate) : Account(name,balance,interest_rate)
  {
	}
  SavingAccount::~SavingAccount()
  {
		delete this;
	}
      
  unsigned int SavingAccount::ComputeExpectedBalance(unsigned int n_years_later) const
  {
		double sum=balance_;
		int i;
		for (i=1;i<=n_years_later;++i) // balance*(1+interest_rate_) n time
			sum*=(1+interest_rate_);
			return int(sum);
	}
    
      
Account* CreateAccount(const string& type,const string& name, unsigned int balance, double interest_rate)
{
	if (type == "normal")
		return new Account(name,balance,interest_rate);
	if (type == "saving")
		return new SavingAccount(name,balance,interest_rate);
}
