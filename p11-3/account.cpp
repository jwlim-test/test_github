#include "account.h"
//입력받은 이름,금액,이율을 저장 
Account :: Account(const string& name, unsigned int balance, double interest_rate)
{
    name_ = name;
    balance_ = balance;
    interest_rate_ = interest_rate;
}
//이율 계산방식에 따라 이자를 계산. 
unsigned int Account:: ComputeExpectedBalance(unsigned int n_years_later) const
{
    unsigned int mon = balance_;
    unsigned int plus_mon = balance_*interest_rate_;        
    mon = mon + plus_mon * n_years_later;
    return mon;
}
SavingAccount :: SavingAccount(const string& name, int balance, double interest_rate) : Account(name,balance,interest_rate)
{}
//복리 계산방식에 따라 금액 계산 
unsigned int SavingAccount :: ComputeExpectedBalance(unsigned int n_years_later) const //: Account(name,balance,interest_rate)
{
    float mon=balance_;
    for(int i=0;i<n_years_later;i++)
    {
        mon = mon*(1+interest_rate_);
    }
    return mon;
}
//각 경우에 따라 옳은 Account를 return 
Account* CreateAccount(const string& type,const string& name, unsigned int balance, double interest_rate)
{
    Account* q;
    
    if(type == "normal")
    {
        q = new Account (name,balance,interest_rate);
        return q;
    }
    
    else if(type == "saving")
    {
        q = new SavingAccount (name,balance,interest_rate);
        return q;
    }
}
