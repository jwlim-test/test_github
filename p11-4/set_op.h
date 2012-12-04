#include <iostream>
#include <set>
#include <map>
#include <string>


template <typename T>
std::set<T> operator+(const std::set<T>& lhs, const std::set<T>& rhs){//set은 중복되지 않으므로 lhs와 rhs원소를 다 넣음 
  std::set<T> s(lhs);
  for(typename std::set<T>::const_iterator its = rhs.begin(); its!=rhs.end(); ++its){
    if(lhs.find(*its) == lhs.end()){
      s.insert(*its);
    }
  }
  return s;
}

template <typename T>
std::set<T> operator-(const std::set<T>& lhs, const std::set<T>& rhs){//lhs의 원소를 새로운 set에 넣은후 중복된 원소를 erase 
  std::set<T> s(lhs);
  for(typename std::set<T>::const_iterator its = rhs.begin(); its != rhs.end(); ++its){
      if(lhs.find(its)!=lhs.end()){
        s.erase(*its);
      }
  }
    return s;
}

template <typename T>
std::set<T> operator*(const std::set<T>& lhs, const std::set<T>& rhs){ // lhs와 rhs의 중복된 원소를 s에 넣음 
  std::set<T> s;
  for(typename std::set<T>::const_iterator its = rhs.begin(); its != rhs.end(); ++its){
    if(lhs.find(its)!=lhs.end()){
      s.insert(*its);
    }
  }
    return s;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s){ // S의 원소 출력 
    os<<"{ ";
    for(typename std::set<T>::const_iterator it = s.begin(); it!= s.end(); ++it){
        os<<*it<<" ";
    }
    os<<"}";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::set<T>& s){ // S의 원소를 입력받음 
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
std::set<T> Cast(const std::set<S>& s){
  std::set<T> se;
  for(typename std::set<S>::const_iterator it = s.begin(); it!=s.end();++it){
     se.insert(static_cast<T>(*it));
  }
  return se;
}
