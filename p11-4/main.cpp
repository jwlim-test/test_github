#include "set_op.h"
#include <map>
using namespace std;
int main() {
    map<string, set<double> > sets;
    while(true){
        string cmd;
        cin >> cmd;
        if (cmd == "int_set") { // intset을 입력받은후 double형태로 바꿈 
            string name;
            set<int> s;
            cin >> name >> s;
            sets[name] = Cast<double, int>(s);
            cout << name << " : " << sets[name] << endl;
        } else if (cmd == "double_set") { //doublset을 입력받은후 sets에 저장 
            string name;
            set<double> s;
            cin >> name >> s;
            sets[name] = s;
            cout << name << " : " << sets[name] << endl;
        } else if (cmd == "eval") {
            string name1, op, name2;
            cin >> name1 >> op >> name2;
        if (op == "+") cout << (sets[name1] + sets[name2]) << endl;
        else if (op == "-") cout << (sets[name1] - sets[name2]) << endl;
        else if (op == "*") cout << (sets[name1] * sets[name2]) << endl;
        else cout << "Invalid operator: " << op << endl;
        } else if (cmd == "dump") {
            map<string, set<double> >::const_iterator it;
        for (it = sets.begin(); it != sets.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }
        } else if (cmd == "quit") {
            break;
        } else {
            cout << "Invalid command: " << cmd << endl;
        }
    }
    return 0;
}


