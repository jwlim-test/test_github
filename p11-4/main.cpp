#include <map>
#include <set>
#include "set_op.h"

using namespace std;

int main(void) {
    map<string, set<double> > sets;        //set의 이름과 배열을 저장하는 map 
    while(true) {
    string cmd;
    cin >> cmd;
    if (cmd == "int_set") {                  // int형 set을 입력받음 
        string name;
        set<int> s; 
        cin >> name >> s;
        sets[name] = Cast<double, int>(s);   // int_set을 입력받아도 typecast를이용해 double로 바꿔 계산이 가능하도록함! 
        cout << name << " : " << sets[name] << endl;
    } 
    else if (cmd == "double_set") {          // double형 set을 입력받음 
        string name;
        set<double> s;
        cin >> name >> s;
        sets[name] = s;
        cout << name << " : " << sets[name] << endl;
    } 
    else if (cmd == "eval") {                // set끼리의 연산을 수행하는 곳 
        string name1, op, name2;
        cin >> name1 >> op >> name2;
        if (op == "+") cout << (sets[name1] + sets[name2]) << endl;
        else if (op == "-") cout << (sets[name1] - sets[name2]) << endl;
        else if (op == "*") cout << (sets[name1] * sets[name2]) << endl;
        else cout << "Invalid operator: " << op << endl;
    }  
    else if (cmd == "dump") {                // 현재 추가된 set들을 출력해주는 곳 
        map<string, set<double> >::const_iterator it;
        for (it = sets.begin(); it != sets.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }
    } 
    else if (cmd == "quit") {
        break;
    } 
    else {      // 잘못된 command가 들어왔을경우 error메시지 출력! 
        cout << "Invalid command: " << cmd << endl;
        }
    }
    return 0;
}
