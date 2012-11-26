#include "date.h"

void Date::NextDay(int n){
    int days_=n+ComputeDayFromYearStart(year_,month_,day_);
    
    
    while(days_>GetDaysInYear(year_) || days_<=0){
        if(days_>GetDaysInYear(year_)){ 
            days_-=GetDaysInYear(year_);
            year_++;
        }
        else if(days_<=0){ 
            year_--;
            days_+=GetDaysInYear(year_);
        }
    }
    
    int i=1,Feb_;
    if(GetDaysInYear(year_)==365) Feb_=28;
    else Feb_=29;
    

    while(1){
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
