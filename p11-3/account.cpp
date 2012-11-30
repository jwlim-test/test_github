#include "account.h"
//�Է¹��� �̸�,�ݾ�,������ ���� 
Account :: Account(const string& name, unsigned int balance, double interest_rate)
{
    name_ = name;
    balance_ = balance;
    interest_rate_ = interest_rate;
}
//���� ����Ŀ� ���� ���ڸ� ���. 
unsigned int Account:: ComputeExpectedBalance(unsigned int n_years_later) const
{
    unsigned int mon = balance_;
    unsigned int plus_mon = balance_*interest_rate_;        
    mon = mon + plus_mon * n_years_later;
    return mon;
}
SavingAccount :: SavingAccount(const string& name, int balance, double interest_rate) : Account(name,balance,interest_rate)
{}
//���� ����Ŀ� ���� �ݾ� ��� 
unsigned int SavingAccount :: ComputeExpectedBalance(unsigned int n_years_later) const //: Account(name,balance,interest_rate)
{
    float mon=balance_;
    for(int i=0;i<n_years_later;i++)
    {
        mon = mon*(1+interest_rate_);
    }
    return mon;
}
//�� ��쿡 ���� ���� Account�� return 
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
