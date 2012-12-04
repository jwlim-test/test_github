#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

template  <typename T>
inline set<T> operator+(const set<T>& lhs, const set<T>& rhs){
       set<T> result_=lhs;
       //�������� ����� �� lhs�� ������ rhs�� �����߿� ���� ���� ������ �ǳʰ��� ���� ���� �ִ°�� �߰���Ų��
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it)
       {          
            typename set<T>::const_iterator it2=result_.find(*it);
            if(it2==result_.end()) result_.insert(*it); 
       }
       return result_;
}
       
template <typename T>
inline set<T> operator-(const set<T>& lhs, const set<T>& rhs){
       set<T> result_=lhs;
       //�������� ����� �� lhs�� ������ rhs�� �����߿� ���� ���� ���� �� ���� �ش�.
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it)
       {
                    typename set<T>::const_iterator it2=result_.find(*it);
                    if(it2!=result_.end())  result_.erase(it2); 
       }
       return result_;
}
template <typename T>
inline set<T> operator*(const set<T>& lhs, const set<T>& rhs){
       set<T> result_;
       //�������� ����� �� lhs�� rhs�� ������Ҹ� ã�´� 
       for(typename set<T>::const_iterator it=rhs.begin();it!=rhs.end();++it)
       {
                    for(typename set<T>::const_iterator it2=lhs.begin();it2!=lhs.end();++it2)
                    {
                         if(*it==*it2) {result_.insert(*it); break;}
                    }
       }
       return result_;
}
//��� �κ� 
template <typename T>
inline ostream& operator<<(ostream& os, const set<T>& s){
         os<<"{";
         for(typename set<T>::const_iterator it=s.begin();it!=s.end();++it)
                      os<<" "<<*it;
         os<<" }";
         
         return os;
}

template <typename T>
inline istream& operator>>(istream& is,  set<T>& s){
    //��� ���� ���� ���� �Է¹ް� �״����� ���ҵ��� ���ʷ� �Է� 
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
inline set<T> Cast(const set<S>& s){
    // s���� ������ t������ �ٲ��־� ����� �� �� �ְ� �� 
       set<T> result_;
       for(typename set<S>::const_iterator it=s.begin();it!=s.end();++it)
                    result_.insert(static_cast<T>(*it));
                    
       return result_;
}
