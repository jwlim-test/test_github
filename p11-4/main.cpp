#include <map>
#include <set>
#include "set_op.h"

using namespace std;

int main(void) {
    map<string, set<double> > sets;        //set�� �̸��� �迭�� �����ϴ� map 
    while(true) {
    string cmd;
    cin >> cmd;
    if (cmd == "int_set") {                  // int�� set�� �Է¹��� 
        string name;
        set<int> s; 
        cin >> name >> s;
        sets[name] = Cast<double, int>(s);   // int_set�� �Է¹޾Ƶ� typecast���̿��� double�� �ٲ� ����� �����ϵ�����! 
        cout << name << " : " << sets[name] << endl;
    } 
    else if (cmd == "double_set") {          // double�� set�� �Է¹��� 
        string name;
        set<double> s;
        cin >> name >> s;
        sets[name] = s;
        cout << name << " : " << sets[name] << endl;
    } 
    else if (cmd == "eval") {                // set������ ������ �����ϴ� �� 
        string name1, op, name2;
        cin >> name1 >> op >> name2;
        if (op == "+") cout << (sets[name1] + sets[name2]) << endl;
        else if (op == "-") cout << (sets[name1] - sets[name2]) << endl;
        else if (op == "*") cout << (sets[name1] * sets[name2]) << endl;
        else cout << "Invalid operator: " << op << endl;
    }  
    else if (cmd == "dump") {                // ���� �߰��� set���� ������ִ� �� 
        map<string, set<double> >::const_iterator it;
        for (it = sets.begin(); it != sets.end(); ++it) {
            cout << it->first << " : " << it->second << endl;
        }
    } 
    else if (cmd == "quit") {
        break;
    } 
    else {      // �߸��� command�� ��������� error�޽��� ���! 
        cout << "Invalid command: " << cmd << endl;
        }
    }
    return 0;
}
