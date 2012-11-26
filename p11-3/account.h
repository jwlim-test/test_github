#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
    public:
        Account(const string& name, unsigned int balance, double interest_rate){
            name_ = name;
            balance_ = balance;
            interest_rate_ = interest_rate;
        }
        virtual ~Account() {}
        void Deposit(unsigned int amount){
            balance_ += amount;
        }
        bool Withdraw(unsigned int amount){
            balance_ -= amount;
        }
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const{
            double COUNT = 0;
            COUNT = (balance_) + (balance_ * interest_rate_ * n_years_later);
            return (unsigned int)(COUNT);        
        }
        virtual const char* type() const { return "normal"; }
        const unsigned int& balance() const { return balance_; }
        const string& name() const { return name_; }
        const double& interest_rate() const { return interest_rate_; }
    
    protected:
        string name_;
        unsigned int balance_;
        double interest_rate_; // �⺻ ���´� �ܸ��� ���.
};

class SavingAccount : public Account {
    public:
        SavingAccount(const string& name, int balance, double interest_rate) : Account(name, balance, interest_rate) {}
        virtual ~SavingAccount() {}
        virtual const char* type() const { return "saving"; }
// �� Ÿ���� ���´� ������ ���.
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const {
            double COUNT=balance_;
            for(int i=0;i<n_years_later;i++){
                COUNT = COUNT + (COUNT * interest_rate_);
            }
            return (unsigned int)(COUNT);
        }
};
