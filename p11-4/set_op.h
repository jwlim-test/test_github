#include <iostream>
#include <string>
#include <set>

template <typename T>
std::set<T> operator+(const std::set<T>& lhs, const std::set<T>& rhs);
template <typename T>
std::set<T> operator-(const std::set<T>& lhs, const std::set<T>& rhs);
template <typename T>
std::set<T> operator*(const std::set<T>& lhs, const std::set<T>& rhs);  
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s);
template <typename T>
std::istream& operator>>(std::istream& is, std::set<T>& s);
template <typename T, typename S>
std::set<T> Cast(const std::set<S>& s);  

template <typename T>
std::set<T> operator+(const std::set<T>& lhs, const std::set<T>& rhs){
	std::set<T> ret(lhs);
	typename std::set<T>::const_iterator it;
	for (it = rhs.begin(); it != rhs.end(); ++it){
		ret.insert(*it);
	}
	return ret;
}

template <typename T>
std::set<T> operator-(const std::set<T>& lhs, const std::set<T>& rhs){
	std::set<T> ret(lhs);
	typename std::set<T>::const_iterator it;
	for (it = rhs.begin(); it != rhs.end(); ++it){
		ret.erase(*it);
	}
	return ret;
}

template <typename T>
std::set<T> operator*(const std::set<T>& lhs, const std::set<T>& rhs){
	std::set<T> ret;
	typename std::set<T>::const_iterator it;
	for (it = rhs.begin(); it != rhs.end(); ++it){
		if (lhs.find(*it) != lhs.end()){
			ret.insert(*it);
		}
	}
	return ret;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s){
	os << "{ ";
	typename std::set<T>::const_iterator it;
	for (it = s.begin(); it != s.end(); ++it){
		os << *it << " ";
	}
	os << "}";

	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::set<T>& s){
	int size;
	is >> size;
	for (int i = 0; i < size; ++i){
		T input;
		is >> input;
		s.insert(input);
	}
	return is;
}

template <typename T, typename S>
std::set<T> Cast(const std::set<S>& s){
	std::set<T> ret;
	typename set<S>::const_iterator it;
	for (it = s.begin(); it != s.end(); ++it){
		ret.insert(static_cast<T>(*it));
	}
	return ret;
}
