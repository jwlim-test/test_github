#include "account.h"
using namespace std;
Account::Account(const string& name, unsigned int balance, double interest_rate) : name_(name), balance_(balance), interest_rate_(interest_rate)
{
}
Account::~Account()
{
}
void Account::Deposit(unsigned int amount)
{
	balance_+=amount;
}
bool Account::Withdraw(unsigned int amount)
{
	if (balance_ < amount)
		return false;
	balance_-=amount;
	return true;
}
unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const    
{
	return static_cast<int>(balance_+interest_rate_*balance_*n_years_later);
	//  static_cast<int> 안 써도 되긴 하는데 warning 뜸 
}
SavingAccount::SavingAccount(const string& name, int balance, double interest_rate) : Account(name,balance,interest_rate)
{
}
SavingAccount::~SavingAccount()
{
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
