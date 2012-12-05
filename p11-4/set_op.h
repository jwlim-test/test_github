#include <map>
#include <set>
#include <iostream>

using namespace std;

template <typename T>
inline set<T> operator+(const set<T>& lhs, const set<T>& rhs){                     // <합집합> 
    set<T> ret(lhs);                                                    // 더하기 일때는 ret이라는 set을 만들어 거기다가 lhs, rhs모두추가한다 
    for(typename set<T>::iterator it= rhs.begin();it!=rhs.end();it++){
        ret.insert(*it);                                                    // 모두추가해도 상관이 없는게 set은 같은 key값이 있으면 받아들이지 않기때문 
    }      
    return ret; 
}

template <typename T>
inline set<T> operator-(const set<T>& lhs, const set<T>& rhs){                     // < 차집합 > 
    set<T> ret(lhs);
    typename set<T>::const_iterator check;
    for(typename set<T>::const_iterator it=rhs.begin();it!= rhs.end();it++){  //ret에서 rhs의 원소가 있으면 그 원소를 삭제한다. 
        if((check = ret.find((*it))) != ret.end())
            ret.erase(check);
    }
    return ret;                                            
}

template <typename T>
inline set<T> operator*(const set<T>& lhs, const set<T>& rhs){                       // < 교집합 > 
    set<T> ret;
    typename set<T>::const_iterator check;                                    //ret이라는 빈 set에 rhs,lhs의 공통원소를 insert해준다. 
    for(typename set<T>::const_iterator it=rhs.begin();it!= rhs.end();it++){
        if((check = lhs.find((*it))) != lhs.end())
            ret.insert(*check);
    }
    return ret;
}

template <typename T>
inline ostream& operator<<(ostream& os, const set<T>& s){                            //set 출력시 괄호하고 그 안에 원소들을 차례로 출력시켜준다 
    cout<<"{ ";                                                               //set은 자동으로 오름차순정렬해주기때문에 크기순 출력 
    for(typename set<T>::iterator it=s.begin();it!=s.end();it++)
        cout<<(*it)<<" ";
    cout<<"}";
    return os;
}
template <typename T>
inline istream& operator>>(istream& is, set<T>& s){                                  //set 입력시 먼저 크기를 입력받고 그크기만큼 set에다가 저장해준다 
    T size, number;                                                            
    cin>>size;
    for(int i=0;i<size;i++){
        cin>>number;
        s.insert(number);
    }
    return is;
}
template <typename T, typename S>
set<T> Cast(const set<S>& s) {
    set<T> ret;
    for(typename set<S>::const_iterator it=s.begin();it!=s.end();it++)
        ret.insert(static_cast<T>(*it));               // 타입을 변경해서 ret라는 set에 모두 넣어주는 typecast 함수이다! 
    return ret;                                        
}
//         ↑ ↑
// 여기서 ret은 scope적용되서 없어지지않나요?ㅠ_ㅠ질문!!! 
