#include "account.h"

/*void Account::Deposit(unsinged int amount){
     balance_+=amount;
}
     
bool Account::Withdraw(unsinged int amount){
     if(balance_>=amount){
                          balance-=amount;
                          return true;
                          }
     else return false;
}
*/
unsigned int Account::ComputeExpectedBalance(unsigned int n_years_late){
         double result;
         
         result=balance_+balance_*interest_rate_*n_years_late;
         
         return (unsigned int)result;
}

unsigned int SavingAccount::ComputeExpectedBalance(unsigned int n_years_later){
         double result=balance_;
         double rate_=1+interest_rate_;
         
         for(int i=1; i<n_years_later; i++)
                 rate_*=(1+interest_rate_);
                 
         result*=rate_;
         
         return (unsigned int)result;
}

Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate){

       
         Account* acc=new Account(name, balance, interest_rate);
         if(acc->type()==type) return acc;
         
         delete acc;
         acc=NULL;
         
         acc=new SavingAccount(name, balance, interest_rate);
         if(acc->type()==type) return acc;
         
         delete acc;
         
         acc=NULL;
        return acc;


}
