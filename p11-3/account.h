#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Account { 
public:
	Account(const std::string& name, unsigned int balance, double interest_rate);
	virtual ~Account();
  
	void Deposit(unsigned int amount);
	bool Withdraw(unsigned int amount);
        
	virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const;
      
	virtual const char* type() const { return "normal"; }
	const unsigned int& balance() const { return balance_; }
	const std::string& name() const { return name_; }
	const double& interest_rate() const { return interest_rate_; }
protected:
	std::string name_;
	unsigned int balance_;
	double interest_rate_;  // �⺻ ���´� �ܸ��� ���.
};

class SavingAccount : public Account {
public:
	SavingAccount(const std::string& name, int balance, double interest_rate);
	virtual ~SavingAccount();
    
	virtual const char* type() const { return "saving"; }
	// �� Ÿ���� ���´� ������ ���.
	virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const;
};    

Account* CreateAccount(const std::string& type,
    const std::string& name, unsigned int balance, double interest_rate);
