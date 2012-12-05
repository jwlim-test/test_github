#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
    public:
        Account(const string& name, unsigned int balance, double interest_rate){   //parametor로 이름,잔고,이자율을 받아 setting시킨다. 
            name_ = name;
            balance_ = balance;
            interest_rate_ = interest_rate;
        }
        virtual ~Account() {}       
        void Deposit(unsigned int amount){    //예금함수 받아온 amount만큼 잔고에 추가시킨다. 
            balance_ += amount;
        }
        bool Withdraw(unsigned int amount){   //인출함수 받아온 amount만큼 잔고에서 빼간다. 
            if(amount > balance_ )
                return false;
            else {
                balance_ -= amount;
                return true;
            }
        }
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const{   //normal계좌의 n년 이후의 계좌상황을 출력 
            double COUNT = 0;
            COUNT = (balance_) + (balance_ * interest_rate_ * n_years_later);     //원리합계에서 단리로 계산하면 되므로 
            return static_cast<unsigned int>(COUNT);                                         //잔고 + 잔고*이자율*n을해서 return해주면된다. 
        }
        virtual const char* type() const { return "normal"; }                     //계좌형태 return 
        const unsigned int& balance() const { return balance_; }                  //잔고 return 
        const string& name() const { return name_; }                              //이름 return 
        const double& interest_rate() const { return interest_rate_; }            //이자율 return 
    
    protected:
        string name_;
        unsigned int balance_;
        double interest_rate_; // 기본 계좌는 단리로 계산.
};

class SavingAccount : public Account {    //나머지는 normal계좌랑 같고 복리계산만 다르다. 
    public:
        SavingAccount(const string& name, int balance, double interest_rate) : Account(name, balance, interest_rate) {}
        virtual ~SavingAccount() {}
        virtual const char* type() const { return "saving"; }
// 이 타입의 계좌는 복리로 계산.
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const {      
            double COUNT=balance_;                                                  //원리합계에서 복리계산이므로 
            for(int i=0;i<n_years_later;i++){                                       //잔고 = 잔고 + 잔고*이자율로 계속증가한다. 
                COUNT = COUNT + (COUNT * interest_rate_);
            }
            return static_cast<unsigned int>(COUNT);
        }
};

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate);
