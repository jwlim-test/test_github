#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs){
       set<T> result_=lhs;
       
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it){
                    bool check=false;
                    for(typename set<T>::const_iterator it2=result_.begin();it2!=result_.end();++it2)
                                 if(*it==*it2) check=true;
                    if(check) continue;
                    result_.insert(*it);
                    }
       return result_;
}
       
template <typename T>
set<T> operator-(const set<T>& lhs, const set<T>& rhs){
       set<T> result_=lhs;
       
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it){
                    for(typename set<T>::const_iterator it2=result_.begin();it2!=result_.end();++it2){
                                                                                                     if(*it==*it2) {result_.erase(it2); break;}
                                                                                                     }
                    }
       return result_;
}
template <typename T>
set<T> operator*(const set<T>& lhs, const set<T>& rhs){
       set<T> result_;
       
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it){
                    for(typename set<T>::const_iterator it2=lhs.begin();it2!=lhs.end();++it2){
                                                                                             if(*it==*it2) {result_.insert(*it); break;}
                                                                                             }
                    }
       return result_;
}

template <typename T>
ostream& operator<<(ostream& os, const set<T>& s){
         os<<"{";
         for(typename set<T>::const_iterator it=s.begin();it!=s.end();++it)
                      os<<" "<<*it;
         os<<" }";
         
         return os;
}
template <typename T>
istream& operator>>(istream& is,  set<T>& s){
         int number;
         T add;
         is>>number;
         for(int i=0; i<number ; i++){
                 
                 is>>add;
                 s.insert(add);
                 }
         
         return is;
}

template <typename T, typename S>
set<T> Cast(const set<S>& s){
       set<T> result_;
       for(typename set<S>::const_iterator it=s.begin();it!=s.end();++it)
                    result_.insert(static_cast<T>(*it));
                    
       return result_;
}
