#include <set>
#include <iostream>
#include <stdlib.h>
template <typename T>
inline std::set<T> operator+(const std::set<T>& lhs, const std::set<T>& rhs)
{
	std::set<T> temp = lhs;
	typename std::set<T>::iterator it;
	for (it = rhs.begin();it!=rhs.end();++it) // find what doesn't exist in lhs
	{
		if (temp.find(*it) == temp.end())
			temp.insert(*it);
	}
	return temp;
}

template <typename T>
inline std::set<T> operator-(const std::set<T>& lhs, const std::set<T>& rhs)
{
	std::set<T> temp;
	typename std::set<T>::iterator it;
	for (it = lhs.begin();it!=lhs.end();++it)
	{
		if (rhs.find(*it) == rhs.end()) // if doesn't exist -> insert
			temp.insert(*it);
	}	
	return temp;
}
template <typename T>
inline std::set<T> operator*(const std::set<T>& lhs, const std::set<T>& rhs)
{
	std::set<T> temp;
	typename std::set<T>::iterator it;
	for (it = lhs.begin();it!=lhs.end();++it)
	{
		if (rhs.find(*it) != rhs.end()) // if exist in both -> insert
			temp.insert(*it);
	}	
	return temp;
}
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
	typename std::set<T>::iterator it;
	os << "{ ";
	for (it = s.begin();it!=s.end();++it)
		os << *it << " ";	
	os << "}";
	return os;
}
template <typename T>
inline std::istream& operator>>(std::istream& is, std::set<T>& s)
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
inline std::set<T> Cast(const std::set<S>& s)
{
	std::set<T> temp;
	typename std::set<S>::iterator it;
	for (it = s.begin();it!=s.end();++it)
		temp.insert(static_cast<T>(*it));
	return temp;		
}
