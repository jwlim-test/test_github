#include <map>
#include <set>
#include <iostream>

using namespace std;

template <typename T>
inline set<T> operator+(const set<T>& lhs, const set<T>& rhs){                     // <������> 
    set<T> ret(lhs);                                                    // ���ϱ� �϶��� ret�̶�� set�� ����� �ű�ٰ� lhs, rhs����߰��Ѵ� 
    for(typename set<T>::iterator it= rhs.begin();it!=rhs.end();it++){
        ret.insert(*it);                                                    // ����߰��ص� ����� ���°� set�� ���� key���� ������ �޾Ƶ����� �ʱ⶧�� 
    }      
    return ret; 
}

template <typename T>
inline set<T> operator-(const set<T>& lhs, const set<T>& rhs){                     // < ������ > 
    set<T> ret(lhs);
    typename set<T>::const_iterator check;
    for(typename set<T>::const_iterator it=rhs.begin();it!= rhs.end();it++){  //ret���� rhs�� ���Ұ� ������ �� ���Ҹ� �����Ѵ�. 
        if((check = ret.find((*it))) != ret.end())
            ret.erase(check);
    }
    return ret;                                            
}

template <typename T>
inline set<T> operator*(const set<T>& lhs, const set<T>& rhs){                       // < ������ > 
    set<T> ret;
    typename set<T>::const_iterator check;                                    //ret�̶�� �� set�� rhs,lhs�� ������Ҹ� insert���ش�. 
    for(typename set<T>::const_iterator it=rhs.begin();it!= rhs.end();it++){
        if((check = lhs.find((*it))) != lhs.end())
            ret.insert(*check);
    }
    return ret;
}

template <typename T>
inline ostream& operator<<(ostream& os, const set<T>& s){                            //set ��½� ��ȣ�ϰ� �� �ȿ� ���ҵ��� ���ʷ� ��½����ش� 
    cout<<"{ ";                                                               //set�� �ڵ����� ���������������ֱ⶧���� ũ��� ��� 
    for(typename set<T>::iterator it=s.begin();it!=s.end();it++)
        cout<<(*it)<<" ";
    cout<<"}";
    return os;
}
template <typename T>
inline istream& operator>>(istream& is, set<T>& s){                                  //set �Է½� ���� ũ�⸦ �Է¹ް� ��ũ�⸸ŭ set���ٰ� �������ش� 
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
        ret.insert(static_cast<T>(*it));               // Ÿ���� �����ؼ� ret��� set�� ��� �־��ִ� typecast �Լ��̴�! 
    return ret;                                        
}
//         �� ��
// ���⼭ ret�� scope����Ǽ� ���������ʳ���?��_������!!! 
