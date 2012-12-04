#include "date.h"

void Date::NextDay(int n){
    //총 지나간 날짜를 계산 
    int days=n+ComputeDayFromYearStart(year_,month_,day_);
    int year=year_;
    
    while (days <= 0) days += GetDaysInYear(--year); //총 지나간 날짜가 1년의 수보다 많을 때 1년의 날짜를 빼주고 년도수를 증가시킨다 
    while (days > GetDaysInYear(year_)) days -= GetDaysInYear(year++); //총 지나간 날짜가 음수일 경우 년도수를 감소시키며 1년의 날짜를 더해준다  
       
    //2월의 달수를 생성한다 
    int i=1,Feb_;
    if(GetDaysInYear(year)==365) Feb_=28;
    else Feb_=29;
    
    
    while(1){
        //월별로 지나가면서 그 월에 해당하는 날짜 수를 계속 지워주고 지워졌을 경우 달 수를 증가시킨다 
        if(days==0) {days++; break;}
        if(i==1) { if(days<=31) break;  else days-=31; }
        else if(i==2) { if(days<=Feb_) break; else days-=Feb_; }
        else if(i==3) { if(days<=31) break; else days-=31;}
        else if(i==4) { if(days<=30) break; else days-=30;}
        else if(i==5) { if(days<=31) break; else days-=31;}
        else if(i==6) { if(days<=30) break; else days-=30;}
        else if(i==7) { if(days<=31) break; else days-=31;}
        else if(i==8) { if(days<=31) break; else days-=31;}
        else if(i==9) { if(days<=30) break; else days-=30;}
        else if(i==10) { if(days<=31) break; else days-=31;}
        else if(i==11) { if(days<=30) break; else days-=30;}
        else if(i==12) { if(days<=31) break; else days-=31;}
        
        
        i++;
    }
    
    year_=year;
    month_=i;
    day_=days;
}
        
bool Date::SetDate(int year, int month, int day){
    
    int Feb_;
    if(GetDaysInYear(year)==365) Feb_=28; 
    else Feb_=29;
    
    //월과 일이 제대로 입력되지 않았을 경우에 InvalidDataException 을 실행시킨다. 
    if(month<1 || month>12) return false;
    
    if(month==1) {if(day>31 || day<1) return false;}
    else if(month==2) {if(day>Feb_ || day<1) return false;}
    else if(month==3) {if(day>31 || day<1) return false;}
    else if(month==4) {if(day>30 || day<1) return false;}
    else if(month==5) {if(day>31 || day<1) return false;}
    else if(month==6) {if(day>30 || day<1) return false;}
    else if(month==7) {if(day>31 || day<1) return false;}
    else if(month==8) {if(day>31 || day<1) return false;}
    else if(month==9) {if(day>30 || day<1) return false;}
    else if(month==10) {if(day>31 || day<1) return false;}
    else if(month==11) {if(day>30 || day<1) return false;}
    else if(month==12) {if(day>31 || day<1) return false;}
    
    year_=year; month_=month; day_=day; 
    return true;
        
    }


std::ostream& operator<< (std::ostream& os, const Date& c){
    os<<c.year()<<"."<<c.month()<<"."<<c.day();
    
    return os;
}

std::istream& operator>> (std::istream& is, Date& c){
        //입력받을 char형 배열을 생성 
    std::string date;
    
    is>>date;
    //입력받아서 제대로 입력되었는지 확인하고 입력이 안됬을 경우  InvalidTimeException를 실행하기위한 문자열 생성 
    char* buf=strdup(date.c_str());
    
    //시,분,초를 각각 잘라서 제대로 맞는지 확인 
    char* ptr;
    ptr = strtok( buf, ":");
    int year = atoi(ptr);
    ptr = strtok( NULL,":");
    int month = atoi(ptr);
    ptr = strtok( NULL,":");
    int day = atoi(ptr);
    
    free(buf);
    //맞지 않을경우 InvalidTimeException를 실행 
    if(!c.SetDate(year,month,day)) throw InvalidDataException(date);
    
    return is;
}
