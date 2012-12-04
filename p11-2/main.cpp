#include "date.h"

using namespace std;

int main(){
    Date date;
    string cmd;
    
    while(cmd!="quit"){
        cin>>cmd;
        try{
            if(cmd=="set"){
                cin>>date;
                cout<<date<<endl;
            }
            else if(cmd=="next_day"){
                date.NextDay();
                cout<<date<<endl;
            }
            else if(cmd=="next"){
                int n_days=0;
                cin >> n_days;
                date.NextDay(n_days);
                cout<<date<<endl;
            }
        }
        catch(InvalidDataException& e){
            cout<<"Invalid date: "<<e.input_date<<endl;
        }
    }
    return 0;
}
