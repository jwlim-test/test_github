#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Date{
    public:
        Date(): year_(0), month_(0), day_(0) {}
        Date(int year, int month, int day): year_(year), month_(month), day_(day) {}
        
        void NextDay(int n=1);
        bool SetDate(int year, int month, int day);
        
        int year() const {return year_;}
        int month() const {return month_;}
        int day() const {return day_;}
        
    private:
        
        static int GetDaysInYear(int year){
            //������ ��� 366���� ��ȯ 
            if(year%4==0 && year%100!=0)
                                         return 366; 
             
            else if(year%400==0) 
                                 return 366;
            //������ �ƴ� ��� 365���� ��ȯ 
            else return 365; 
        }
        static int ComputeDayFromYearStart(int year, int month, int day){
            int Feb_, sum=0;
            //�������� �ƴ����� ���� 2���� �� �� �� ���� 
            if(GetDaysInYear(year)==365) Feb_=28;
            else Feb_=29;
    
            //�� �� ���� ����Ѵ� 
            for(int i=1; i<month; i++){
                if(i==1) sum+=31;
                else if(i==2) sum+=Feb_;
                else if(i==3) sum+=31;
                else if(i==4) sum+=30;
                else if(i==5) sum+=31;
                else if(i==6) sum+=30;
                else if(i==7) sum+=31;
                else if(i==8) sum+=31;
                else if(i==9) sum+=30;
                else if(i==10) sum+=31;
                else if(i==11) sum+=30;
                else if(i==12) sum+=31;
            }
            sum+=day;
    
            return sum;
        }
        
        
        int year_,month_,day_;
};


struct InvalidDataException {
    string input_date;
    InvalidDataException(const string& str) : input_date(str) {}
};

ostream& operator<< (ostream& os, const Date& c);
istream& operator>> (istream& is, Date& c);
                                             
