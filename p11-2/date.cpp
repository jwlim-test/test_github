#include "date.h"

void Date::NextDay(int n){
    //�� ������ ��¥�� ��� 
    int days=n+ComputeDayFromYearStart(year_,month_,day_);
    int year=year_;
    
    while (days <= 0) days += GetDaysInYear(--year); //�� ������ ��¥�� 1���� ������ ���� �� 1���� ��¥�� ���ְ� �⵵���� ������Ų�� 
    while (days > GetDaysInYear(year_)) days -= GetDaysInYear(year++); //�� ������ ��¥�� ������ ��� �⵵���� ���ҽ�Ű�� 1���� ��¥�� �����ش�  
       
    //2���� �޼��� �����Ѵ� 
    int i=1,Feb_;
    if(GetDaysInYear(year)==365) Feb_=28;
    else Feb_=29;
    
    
    while(1){
        //������ �������鼭 �� ���� �ش��ϴ� ��¥ ���� ��� �����ְ� �������� ��� �� ���� ������Ų�� 
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
    
    //���� ���� ����� �Էµ��� �ʾ��� ��쿡 InvalidDataException �� �����Ų��. 
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
        //�Է¹��� char�� �迭�� ���� 
    std::string date;
    
    is>>date;
    //�Է¹޾Ƽ� ����� �ԷµǾ����� Ȯ���ϰ� �Է��� �ȉ��� ���  InvalidTimeException�� �����ϱ����� ���ڿ� ���� 
    char* buf=strdup(date.c_str());
    
    //��,��,�ʸ� ���� �߶� ����� �´��� Ȯ�� 
    char* ptr;
    ptr = strtok( buf, ":");
    int year = atoi(ptr);
    ptr = strtok( NULL,":");
    int month = atoi(ptr);
    ptr = strtok( NULL,":");
    int day = atoi(ptr);
    
    free(buf);
    //���� ������� InvalidTimeException�� ���� 
    if(!c.SetDate(year,month,day)) throw InvalidDataException(date);
    
    return is;
}
