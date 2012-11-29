#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;


template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs){//set은 중복되지 않으므로 lhs와 rhs원소를 다 넣음 
    set<T> s;
    for(typename set<T>::const_iterator it = lhs.begin(); it!= lhs.end(); ++it){
        s.insert(*it);
    }
    for(typename set<T>::const_iterator its = rhs.begin(); its!=rhs.end(); ++its){
        s.insert(*its);
    }
    return s;
}

template <typename T>
set<T> operator-(const set<T>& lhs, const set<T>& rhs){//lhs의 원소를 새로운 set에 넣은후 중복된 원소를 erase 
    set<T> s;
    for(typename set<T>::const_iterator it = lhs.begin(); it!= lhs.end(); ++it){
        s.insert(*it);
    }
    for(typename set<T>::const_iterator it = lhs.begin(); it !=lhs.end(); ++it){
        for(typename set<T>::const_iterator its = rhs.begin(); its != rhs.end(); ++its){
            if(*it == *its){
                s.erase(*it);
            }
        }
    }
    return s;
}

template <typename T>
set<T> operator*(const set<T>& lhs, const set<T>& rhs){ // lhs와 rhs의 중복된 원소를 s에 넣음 
    set<T> s;
    for(typename set<T>::const_iterator it = lhs.begin(); it !=lhs.end(); ++it){
        for(typename set<T>::const_iterator its = rhs.begin(); its != rhs.end(); ++its){
            if(*it == *its){
                s.insert(*it);
            }
        }
    }
    return s;
}

template <typename T>
ostream& operator<<(ostream& os, const set<T>& s){ // S의 원소 출력 
    os<<"{ ";
    for(typename set<T>::const_iterator it = s.begin(); it!= s.end(); ++it){
        os<<*it<<" ";
    }
    os<<"}";
    return os;
}

template <typename T>
istream& operator>>(istream& is, set<T>& s){ // S의 원소를 입력받음 
    int num;
    T a;
    is>>num;
    for(int i=0; i<num; i++){
        is>>a;
        s.insert(a);
    }
    return is;
}

template <typename T, typename S> // set<S> 를 set<T>로 변환 
set<T> Cast(const set<S>& s){
    set<T> se;
    for(typename set<S>::const_iterator it = s.begin(); it!=s.end();++it){
        se.insert(static_cast<T>(*it));
    }
    return se;
}

