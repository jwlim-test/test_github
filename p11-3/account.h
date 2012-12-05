#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
    public:
        Account(const string& name, unsigned int balance, double interest_rate){   //parametor�� �̸�,�ܰ�,�������� �޾� setting��Ų��. 
            name_ = name;
            balance_ = balance;
            interest_rate_ = interest_rate;
        }
        virtual ~Account() {}       
        void Deposit(unsigned int amount){    //�����Լ� �޾ƿ� amount��ŭ �ܰ� �߰���Ų��. 
            balance_ += amount;
        }
        bool Withdraw(unsigned int amount){   //�����Լ� �޾ƿ� amount��ŭ �ܰ��� ������. 
            if(amount > balance_ )
                return false;
            else {
                balance_ -= amount;
                return true;
            }
        }
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const{   //normal������ n�� ������ ���»�Ȳ�� ��� 
            double COUNT = 0;
            COUNT = (balance_) + (balance_ * interest_rate_ * n_years_later);     //�����հ迡�� �ܸ��� ����ϸ� �ǹǷ� 
            return static_cast<unsigned int>(COUNT);                                         //�ܰ� + �ܰ�*������*n���ؼ� return���ָ�ȴ�. 
        }
        virtual const char* type() const { return "normal"; }                     //�������� return 
        const unsigned int& balance() const { return balance_; }                  //�ܰ� return 
        const string& name() const { return name_; }                              //�̸� return 
        const double& interest_rate() const { return interest_rate_; }            //������ return 
    
    protected:
        string name_;
        unsigned int balance_;
        double interest_rate_; // �⺻ ���´� �ܸ��� ���.
};

class SavingAccount : public Account {    //�������� normal���¶� ���� ������길 �ٸ���. 
    public:
        SavingAccount(const string& name, int balance, double interest_rate) : Account(name, balance, interest_rate) {}
        virtual ~SavingAccount() {}
        virtual const char* type() const { return "saving"; }
// �� Ÿ���� ���´� ������ ���.
        virtual unsigned int ComputeExpectedBalance(unsigned int n_years_later) const {      
            double COUNT=balance_;                                                  //�����հ迡�� ��������̹Ƿ� 
            for(int i=0;i<n_years_later;i++){                                       //�ܰ� = �ܰ� + �ܰ�*�������� ��������Ѵ�. 
                COUNT = COUNT + (COUNT * interest_rate_);
            }
            return static_cast<unsigned int>(COUNT);
        }
};

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate);
