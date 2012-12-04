#include <string>
#include <set>
#include <iostream>

using namespace std;

template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs){
    set<T> temp;
    for(set<double>::iterator it=lhs.begin();it!=lhs.end();++it){
        temp.insert(*it);
    }
    for(set<double>::iterator it=rhs.begin();it!=rhs.end();++it){
        if(lhs.find(*it)==lhs.end()){
            temp.insert(*it);
        }
    }
    return temp;
}
template <typename T>
set<T> operator-(const set<T>& lhs, const set<T>& rhs){
    set<T> temp;
    for(set<double>::iterator it=lhs.begin();it!=lhs.end();++it){
        temp.insert(*it);
    }
    for(set<double>::iterator it=rhs.begin();it!=rhs.end();++it){
        if(lhs.find(*it)!=lhs.end()){
            temp.erase(*it);
        }
    }
    return temp;
}
template <typename T>
set<T> operator*(const set<T>& lhs, const set<T>& rhs){
    set<T> temp;
    for(set<double>::iterator lt=lhs.begin();lt!=lhs.end();++lt){
        for(set<double>::iterator rt=rhs.begin();rt!=rhs.end();++rt){
            if((*lt)==(*rt)){
                temp.insert(*lt);
            }
        }
    }
    return temp;
}
template <typename T>
ostream& operator<<(ostream& os, const set<T>& s){
    os<<"{ ";
    for(set<double>::iterator it=s.begin();it!=s.end();++it){
        os<<*it<<" ";
    }
    os<<"}";
    return os;
}
template <typename T>
istream& operator>>(istream& is, set<T>& s){
    int n;
    T t;
    is>>n;
    for(int i=0;i<n;++i){
        is>>t;
        s.insert(t);
    }
    return is;
}
template <typename T, typename S>
set<T> Cast(const set<S>& s){
    set<T> temp;
    
    for(typename set<S>::iterator it=s.begin();it!=s.end();++it){
        temp.insert((T)*it);
    }
    return temp;
}

