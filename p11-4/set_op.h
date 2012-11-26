#include <iostream>
#include <string>
#include <set>

using namespace std;

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
