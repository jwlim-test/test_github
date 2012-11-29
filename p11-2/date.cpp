#include "date.h"

void Date::NextDay(int n){
    //총 지나간 날짜를 계산 
    int days_=n+ComputeDayFromYearStart(year_,month_,day_);
    
     
    while(days_>GetDaysInYear(year_) || days_<=0){
        //총 지나간 날짜가 1년의 수보다 많을 때 1년의 날짜를 빼주고 년도수를 증가시킨다 
        if(days_>GetDaysInYear(year_)){ 
            days_-=GetDaysInYear(year_);
            year_++;
        }
        //총 지나간 날짜가 음수일 경우 년도수를 감소시키며 1년의 날짜를 더해준다 
        else if(days_<=0){ 
            year_--;
            days_+=GetDaysInYear(year_);
        }
    }
    
    //2월의 달수를 생성한다 
    int i=1,Feb_;
    if(GetDaysInYear(year_)==365) Feb_=28;
    else Feb_=29;
    
    
    while(1){
        //월별로 지나가면서 그 월에 해당하는 날짜 수를 계속 지워주고 지워졌을 경우 달 수를 증가시킨다 
        if(days_==0) {days_++; break;}
        if(i==1) { if(days_<=31) break;  else days_-=31; }
        else if(i==2) { if(days_<=Feb_) break; else days_-=Feb_; }
        else if(i==3) { if(days_<=31) break; else days_-=31;}
        else if(i==4) { if(days_<=30) break; else days_-=30;}
        else if(i==5) { if(days_<=31) break; else days_-=31;}
        else if(i==6) { if(days_<=30) break; else days_-=30;}
        else if(i==7) { if(days_<=31) break; else days_-=31;}
        else if(i==8) { if(days_<=31) break; else days_-=31;}
        else if(i==9) { if(days_<=30) break; else days_-=30;}
        else if(i==10) { if(days_<=31) break; else days_-=31;}
        else if(i==11) { if(days_<=30) break; else days_-=30;}
        else if(i==12) { if(days_<=31) break; else days_-=31;}
        
        
        i++;
    }
    
     
    month_=i;
    day_=days_;
}
        
bool Date::SetDate(int year, int month, int day){
    
    int Feb_;
    stringstream a,b,c;
    a<<year; b<<month; c<<day;
    string Date_=a.str()+"."+b.str()+"."+c.str();
    if(GetDaysInYear(year)==365) Feb_=28; 
    else Feb_=29;
    
    //월과 일이 제대로 입력되지 않았을 경우에 InvalidDataException 을 실행시킨다. 
    if(month<1 || month>12) throw InvalidDataException(Date_);
    
    if(month==1) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    else if(month==2) {if(day>Feb_ || day<1) throw InvalidDataException(Date_);}
    else if(month==3) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    else if(month==4) {if(day>30 || day<1) throw InvalidDataException(Date_);}
    else if(month==5) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    else if(month==6) {if(day>30 || day<1) throw InvalidDataException(Date_);}
    else if(month==7) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    else if(month==8) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    else if(month==9) {if(day>30 || day<1) throw InvalidDataException(Date_);}
    else if(month==10) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    else if(month==11) {if(day>30 || day<1) throw InvalidDataException(Date_);}
    else if(month==12) {if(day>31 || day<1) throw InvalidDataException(Date_);}
    
    year_=year; month_=month; day_=day; 
    return true;
        
    }


ostream& operator<< (ostream& os, const Date& c){
    os<<c.year()<<"."<<c.month()<<"."<<c.day();
    
    return os;
}

istream& operator>> (istream& is, Date& c){
    //char 배열로 날짜를 입력받아 년 월 일로 잘라서 SetDate를 호출 
    char date[1000];
    
    is>>date;
    
    char* ptr;
    ptr = strtok( date, ".");
    int year = atoi(ptr);
    ptr = strtok( NULL,".");
    int month = atoi(ptr);
    ptr = strtok( NULL,".");
    int day = atoi(ptr);
    
    
    if(c.SetDate(year,month,day)) ;
    
    return is;
}
