#include <map>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <string>
#include <stdio.h>
using namespace std;

template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs)
{
    set<double> s;
    
    set<double>::iterator fir=lhs.begin();
    set<double>::iterator sec=rhs.begin();
    
    for(;fir!=lhs.end();fir++)
      s.insert(*fir);

    for(;sec!=rhs.end();sec++)
      s.insert(*sec);
    
    return s;
}
template <typename T>
set<T> operator-(const set<T>& lhs, const set<T>& rhs)
{
    set<double> s;
    
    set<double>::iterator fir=lhs.begin();
    set<double>::iterator sec=rhs.begin();
    
    for(;fir!=lhs.end();fir++)
      s.insert(*fir);

    set<double>::iterator it=s.begin();
    for (;it!=s.end();it++)
      for (sec=rhs.begin();sec!=rhs.end();sec++)
        if (*sec==*it)
          s.erase(it);

    return s;
    
}
template <typename T>
set<T> operator*(const set<T>& lhs, const set<T>& rhs)
{
    set<double> s;
    
    set<double>::iterator fir=lhs.begin();
    set<double>::iterator sec=rhs.begin();
    
    for(;fir!=lhs.end();fir++)
      for (sec=rhs.begin();sec!=rhs.end();sec++)
        if (*fir==*sec)
          s.insert(*fir);
    
    return s;
    
}
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s)
{
    os << "{ ";
    set<double>::iterator it=s.begin();
    for(;it!=s.end();it++)
    os << *it <<" ";
    os <<"}";
    
    return os;
}
template <typename T>
istream& operator>>(istream& is, set<T>& s)
{
    int i=0;
    int num=0;
    double val;
    is >> num;
    
    for(i=0;i<num;i++)
    {
        is >> val;
        s.insert(val);
    }
}
template <typename T, typename S>
set<T> Cast(const set<S>& s)
{

    int i=0;
    int j=0;
            
    set<T> ret;
    set<int>::iterator it=s.begin();
    for(;it!=s.end();it++)
    ret.insert(static_cast<S>(*it));
            
    return ret;   
}
