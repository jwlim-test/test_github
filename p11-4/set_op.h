#include <set>
#include <iostream>
#include <stdlib.h>
using namespace std;
template <typename T>
inline set<T> operator+(const set<T>& lhs, const set<T>& rhs)
{
	set<T> temp = lhs;
	typename set<T>::iterator it;
	for (it = rhs.begin();it!=rhs.end();++it) // find what doesn't exist in lhs
	{
		if (temp.find(*it) == temp.end())
			temp.insert(*it);
	}
	return temp;
}

template <typename T>
inline set<T> operator-(const set<T>& lhs, const set<T>& rhs)
{
	set<T> temp;
	typename set<T>::iterator it;
	for (it = lhs.begin();it!=lhs.end();++it)
	{
		if (rhs.find(*it) == rhs.end()) // if doesn't exist -> insert
			temp.insert(*it);
	}	
	return temp;
}
template <typename T>
inline set<T> operator*(const set<T>& lhs, const set<T>& rhs)
{
	set<T> temp;
	typename set<T>::iterator it;
	for (it = lhs.begin();it!=lhs.end();++it)
	{
		if (rhs.find(*it) != rhs.end()) // if exist in both -> insert
			temp.insert(*it);
	}	
	return temp;
}
template <typename T>
inline ostream& operator<<(ostream& os, const set<T>& s)
{
	typename set<T>::iterator it;
	os << "{ ";
	for (it = s.begin();it!=s.end();++it)
		os << *it << " ";	
	os << "}";
	return os;
}
template <typename T>
inline istream& operator>>(istream& is, set<T>& s)
{
	int i,n;
	is >> n;
	for (i=1;i<=n;++i)
	{
		T input_num;		
		is >> input_num;
		s.insert(input_num);
	}
	return is;
}
template <typename T, typename S>
inline set<T> Cast(const set<S>& s)
{
	set<T> temp;
	typename set<S>::iterator it;
	for (it = s.begin();it!=s.end();++it)
		temp.insert(static_cast<T>(*it));
	return temp;		
}

/*
template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs);
template <typename T>
set<T> operator-(const set<T>& lhs, const set<T>& rhs);
template <typename T>
set<T> operator*(const set<T>& lhs, const set<T>& rhs);  
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s);
template <typename T>
istream& operator>>(istream& is, set<T>& s);
template <typename T, typename S>
set<T> Cast(const set<S>& s);
*/
