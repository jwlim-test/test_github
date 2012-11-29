#include "set_op.h"

template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs){
	set<T> temp;
	temp = lhs;
	typename set<T>::const_iterator it;
	for(it = rhs.begin(); it != rhs.end(); ++it){
		temp.insert(*it);
	}
	return temp;
}

template <typename T>
set<T> operator-(const set<T>& lhs, const set<T>& rhs){
	set<T> temp;
	temp = lhs;
	typename set<T>::const_iterator it;
	for(it = rhs.begin(); it != rhs.end(); ++it){
		temp.erase(*it);
	}
	return temp;
}

template <typename T>
set<T> operator*(const set<T>& lhs, const set<T>& rhs){
	set<T> temp;
	typename set<T>::const_iterator it;
	for(it = rhs.begin(); it != rhs.end(); ++it){
		if(lhs.find(*it) != lhs.end()){
			temp.insert(*it);
		}
	}
	return temp;
}

template <typename T>
ostream& operator<<(ostream& os, const set<T>& s){
	os << "{ ";
	typename set<T>::const_iterator it;
	for(it = s.begin(); it != s.end(); ++it){
		os << *it << " ";
	}
	os << "}";

	return os;
}

template <typename T>
istream& operator>>(istream& is, set<T>& s){
	int size;
	is >> size;
	for(int i = 0; i < size; ++i){
		T input;
		is >> input;
		s.insert(input);
	}
	return is;
}

template <typename T, typename S>
set<T> Cast(const set<S>& s){
	set<T> temp;
	typename set<S>::const_iterator it;
	for(it = s.begin(); it != s.end(); ++it){
		temp.insert(static_cast<T>(*it));
	}
	return temp;
}
