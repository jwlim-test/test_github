#include "account.h"


unsigned int Account::ComputeExpectedBalance(unsigned int n_years_late){
        // 최종 n년이 지난후에 얼마가 되는지를 계산해서 반환한다 
         double result;
         
         result=balance_+balance_*interest_rate_*n_years_late;
         
         return (unsigned int)result;
}

unsigned int SavingAccount::ComputeExpectedBalance(unsigned int n_years_later){
        // 이자를 계산하여 n년 뒤 이자를 계산
         
         double result=balance_;
         double rate_=1+interest_rate_;
         //복리의 경우에서 이자계산법 
         for(int i=1; i<n_years_later; i++)
                 rate_*=(1+interest_rate_);
                 
         result*=rate_;
         
         return (unsigned int)result;
}

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate){

       // type()를 확인하여 단리의 경우 계좌 생성 
         if(Account::GetTypeStr()==type) return new Account(name,balance,interest_rate);
        
        // 복리의 경우 계좌 생성 
         else return new SavingAccount(name,balance,interest_rate);
        
}
