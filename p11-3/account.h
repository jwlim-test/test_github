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
        double interest_rate_; // 기본 계좌는 단리로 계산.
};

class SavingAccount : public Account {
    public:
        SavingAccount(const string& name, int balance, double interest_rate) : Account(name, balance, interest_rate) {}
        virtual ~SavingAccount() {}
        virtual const char* type() const { return "saving"; }
// 이 타입의 계좌는 복리로 계산.
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const {
            double COUNT=balance_;
            for(int i=0;i<n_years_later;i++){
                COUNT = COUNT + (COUNT * interest_rate_);
            }
            return (unsigned int)(COUNT);
        }
};
