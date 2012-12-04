#include <string.h>
#include <stdlib.h>
#include <iostream>



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
               return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 366 : 365; 
        }
        static int ComputeDayFromYearStart(int year, int month, int day){
            int Feb_, sum=0;
            //윤년인지 아닌지에 따라 2월의 달 수 를 결정 
            if(GetDaysInYear(year)==365) Feb_=28;
            else Feb_=29;
    
            //총 일 수를 계산한다 
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
    std::string input_date;
    InvalidDataException(const std::string& str) : input_date(str) {}
};

std::ostream& operator<< (std::ostream& os, const Date& c);
std::istream& operator>> (std::istream& is, Date& c);
                                             
