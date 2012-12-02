//#include"set_op.h"

//template<typename T>
//set<T> operator+(const set<T>& lhs, const set<T>& rhs)
//{
//	set<T> re = lhs;
//	for(unsigned int i=0; i<rhs.size(); i++)
//	{
//		if(lhs.find(rhs[i]) != lhs.end())
//			re.insert(rhs[i]);
//	}
//
//	return re;
//}
//
//template<typename T>
//set<T> operator-(const set<T>& lhs, const set<T>& rhs)
//{
//	set<T> re = lhs;
//
//	for(unsigned int i=0; i<rhs.size(); i++)
//	{
//		if(lhs.find(rhs[i]) != lhs.end())
//			re.erase(lhs.find(rhs[i]));
//	}
//
//	return re;
//}

//template<typename T>
//set<T> operator*(const set<T>& lhs, const set<T>& rhs)
//{
//	set<T> re;
//
//	for(unsigned int i=0; i<lhs.size(); i++)
//	{
//		if(lhs.find(rhs[i]) != lhs.end())
//			re.insert(rhs[i]);
//	}
//
//	return re;
//}



//template <typename T>
//ostream* operator<<(ostream* os, const set<T>& s)
//{
//	cout<<"{ ";
//	
//	for(s.iterator it = s.begin(); it!=s.end(); it++)
//		cout<<*it<<" ";
//
//	cout<<"}"<,endl;
//
//	return os;
//}

//template <typename T>
//istream& operator>>(istream* is, set<T>& s)
//{
//	while(1)
//	{
//		char a;
//		cin>>a;
//
//		if(a != '\n')
//			s.insert(T(a-48));
//		else
//			break;
//	}
//
//	return is;
//}



//template <typename T, typename S>
//set<T> Cast(const set<S>& s)
//{
//	set<T> re;
//
//	for(unsigned int i=0; i<s.size(); i++)
//	{
//		re.insert(T(s[i]));
//	}
//
//	return re;
//}