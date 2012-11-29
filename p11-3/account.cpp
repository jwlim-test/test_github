#include "account.h"
#include <fstream>

using namespace std;
// type이 복리인지 단지인지 구분하고 그에 맞는 class를 리턴시킨다 
Account* CreateAccount(const string& type, const string& name, unsigned int balance, double interest_rate){
  Account * account = new Account(name, balance, interest_rate);
  SavingAccount * sacc= new SavingAccount(name, balance, interest_rate);
  if(type == account->type()){
    return account;
  }
  else if(type == sacc->type()){
    return sacc;
  }
  else
    return NULL; 
}
//n년후 단리로 계산했을때 남아있는 총 money를 리턴  total = a(1+ rn)
unsigned int Account::ComputeExpectedBalance(unsigned int n_years_later) const{
  unsigned int total;
  total = balance()*(1+(interest_rate()*n_years_later));
  return total;
}
//n년후 복리로 계산했을 떄 남아있는 총 money를 리턴 total = a(1+r)^n 
unsigned int SavingAccount::ComputeExpectedBalance(unsigned int n_years_later) const{
  unsigned int total;
  double a;
  a = balance_;
  for(int i=0; i<n_years_later; i++){
    a = (a*(1+interest_rate_));
  }
  total = a;
  return total;
}


