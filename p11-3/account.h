#include <string>
#include <vector>

class Account { 
 public:
  Account(const std::string& name, unsigned int balance, double interest_rate);
  virtual ~Account(){};
        
  virtual unsigned int ComputeExpectedBalance(
      unsigned int n_years_later) const{
	      return (balance_ * n_years_later * interest_rate_) + balance_;
  };
      
  virtual const char* type() const { return "normal"; }
  const unsigned int& balance() const { return balance_; }
  const std::string& name() const { return name_; }
  const double& interest_rate() const { return interest_rate_; }
        
 protected:
  std::string name_;
  unsigned int balance_;
  double interest_rate_;  // 기본 계좌는 단리로 계산.
};           
             
class SavingAccount : public Account {
 public:
	 SavingAccount(const std::string& name, int balance, double interest_rate): Account(name,balance,interest_rate){};
	 virtual ~SavingAccount(){};
      
  virtual const char* type() const { return "saving"; }
  // 이 타입의 계좌는 복리로 계산.
  virtual unsigned int ComputeExpectedBalance(
      unsigned int n_years_later) const{
		  double temp = balance_;
		  for(int i=0;i<n_years_later;i++){
			  double temp2 = temp *interest_rate_;
			  temp +=temp2;
		  }
		  return temp;
  };
};    
      
inline Account* CreateAccount(const std::string& type,
    const std::string& name, unsigned int balance, double interest_rate){
	if(type == "normal"){
		Account *a = new Account(name,balance,interest_rate);
		return a;
	}
	else{
		SavingAccount *a = new SavingAccount(name,balance,interest_rate);
		return a;
	}
    return NULL;
}
