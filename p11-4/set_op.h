#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

template <typename T>
set<T> operator+(const set<T>& lhs, const set<T>& rhs){
       set<T> result_=lhs;
       //합집합을 계산할 때 lhs를 가지고 rhs의 원소중에 같은 것이 있으면 건너가고 없는 것이 있는경우 추가시킨다
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
       //차집합을 계산할 때 lhs를 가지고 rhs의 원소중에 같은 것이 있을 때 지워 준다.
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
       //교집합을 계산할 때 lhs와 rhs의 공통원소를 찾는다 
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it){
                    for(typename set<T>::const_iterator it2=lhs.begin();it2!=lhs.end();++it2){
                                                                                             if(*it==*it2) {result_.insert(*it); break;}
                                                                                             }
                    }
       return result_;
}
//출력 부분 
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
    //몇개를 넣을 건지 먼저 입력받고 그다음에 원소들을 차례로 입력 
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
    // s형의 집합을 t형으로 바꿔주어 계산을 할 수 있게 함 
       set<T> result_;
       for(typename set<S>::const_iterator it=s.begin();it!=s.end();++it)
                    result_.insert(static_cast<T>(*it));
                    
       return result_;
}
