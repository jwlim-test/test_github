#include"account.h"

int main()
{
	vector<Account*> accounts;
	string cmd;

	while(cmd !="quit")
	{
		cin>>cmd;
		if(cmd == "add")
		{
			string name, type;
			int amount;
			double interest_rate;

			cin>>name>>type>>amount>>interest_rate;

			Account* acc = CreateAccount(type, name, amount, interest_rate);

			if(acc == NULL)
			{
				cout<<"Error: "<<type<<", "<<name<<endl;
			}
			else
			{
				accounts.push_back(acc);
			}
		}
		else if(cmd == "delete")
		{
			string name;
			
			cin>>name;

			for(unsigned int i=0; i<accounts.size(); ++i)
			{
				if(accounts[i]->name() == name)
				{
					accounts.erase(accounts.begin() + i);
					break;
				}
			}
		}
		else if(cmd == "show")
		{
			for(unsigned int i=0; i<accounts.size(); ++i)
			{
				cout<<accounts[i]->name()<<"\t"<<accounts[i]->type()<<"\t"<<accounts[i]->balance()<<"\t"<<accounts[i]->interest_rate()<<endl;
			}
		}
		else if(cmd == "after")
		{
			int n_year;
			cin>>n_year;

			for(unsigned int i= 0; i<accounts.size(); ++i)
			{
				cout<<accounts[i]->name()<<"\t"<<accounts[i]->type()<<"\t"<<accounts[i]->ComputeExpectedBalance(n_year)<<"\t"<<accounts[i]->interest_rate()<<endl;
			}
		}
	}

	for(unsigned int i=0; i<accounts.size(); i++)
	{
		delete accounts[i];
	}
	return 0;
}