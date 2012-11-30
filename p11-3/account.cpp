#include "account.h"

using namespace std;

unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const{
    return balance_*(1+(interest_rate_*n_years_later));
}

unsigned int SavingAccount::ComputeExpectedBalance(unsigned int n_years_later) const{
    double temp=balance_;
    for(int i=0;i<n_years_later;++i){
        temp=temp*(1+(interest_rate_));
    }

    return temp;
}

Account* CreateAccount(const string& type,const string& name, unsigned int balance, double interest_rate){
    if(type=="normal"){
        return new Account(name,balance,interest_rate);
    }
    else if(type=="saving"){
        return new SavingAccount(name,balance,interest_rate);
    }
}

