#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Account//단리
{
public:
	Account()
	{}
	Account(const string& name, unsigned int balance, double interest_rate)
	{
		name_ = name;
		balance_ = balance;
		interest_rate_ = interest_rate;
	}
	virtual ~Account(){}

	//void Deposit(unsigned int amount);
	//bool Withdraw(unsigned int amount);

	virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const
	{
		unsigned int val = balance_;
		double plus = 0;

		for(unsigned int i = 0; i<n_years_later; i++)
		{
			plus += double(val)*interest_rate_;
		}

		val += int(plus);

		return val;
	}

	virtual const char* type() const {return "normal";}
	const unsigned int& balance() const {return balance_;}
	const string& name() const {return name_;}
	const double& interest_rate() const { return interest_rate_;}

protected:
	string name_;
	unsigned int balance_;
	double interest_rate_;
};




class SavingAccount : public Account//복리
{
public:
	SavingAccount(const string& name, int balance, double interest_rate)
	{
		name_ = name;
		balance_ = balance;
		interest_rate_ = interest_rate;
	}
	virtual ~SavingAccount(){}

	virtual const char* type() const {return "saving";}

	//이 차입의 계돠는 복리로 계산.
	virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const
	{
		double val = double(balance_);

		for(unsigned int i=0; i<n_years_later; i++)
		{
			val += val*interest_rate_;
		}
		unsigned int re = val;
		return re;
	}
};

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate)
{
	if(type == "normal")
	{
		Account* acc = new Account(name, balance, interest_rate);
		return acc;
	}
	else
	{
		SavingAccount* acc = new SavingAccount(name, balance, interest_rate);
		return acc;
	}
}