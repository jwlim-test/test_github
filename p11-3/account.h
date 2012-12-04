#include <iostream>
#include <vector>

using namespace std;


class Account {
  public:
    Account(const string& name, unsigned int balance, double interest_rate) : name_(name), balance_(balance), interest_rate_(interest_rate){}
    virtual ~Account(){}
    void Deposit(unsigned int amount){}
    bool Withdraw(unsigned int amount){}
    virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const;
    virtual const char* type() const { return "normal"; }
    const unsigned int& balance() const { return balance_; }
    const string& name() const { return name_; }
    const double& interest_rate() const { return interest_rate_; }
  protected:
    string name_;
    unsigned int balance_;
    double interest_rate_; // 단리로 계산 
};

class SavingAccount : public Account {
  public:
    SavingAccount(const string& name, int balance, double interest_rate): Account(name, balance, interest_rate) {}
    virtual ~SavingAccount(){}
    virtual const char* type() const { return "saving"; }
    //이 타입의 계좌는 복리로 계산 
    virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const;
};
Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate);

