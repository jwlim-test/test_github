#include "account.h"
Account :: Account(const string& name, unsigned int balance, double interest_rate){
  name_ = name;
  balance_ = balance;
  interest_rate_ = interest_rate; 
}