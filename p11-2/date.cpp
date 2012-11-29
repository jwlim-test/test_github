#include "date.h"

Date :: Date()
{
    calendar[0]=31;
    calendar[1]=28;
    calendar[2]=31;
    calendar[3]=30;
    calendar[4]=31;
    calendar[5]=30;
    calendar[6]=31;
    calendar[7]=31;
    calendar[8]=30;
    calendar[9]=31;
    calendar[10]=30;
    calendar[11]=31;
}

Date :: Date(int year, int month, int day)
{
    year_=year;
    month_=month;
    day_=day;
}
void Date :: NextDay(int n)
{
    int i=0;
    //int count = ComputeDaysFromYearStart(year_,month_,day_);
    
    if( n < 0 )
    {
        while (i>n)
        {
            day_=day_-2;
            NextDay();
            i--;
        }
    }
    
    if( n > 0 )
    {
        while (i<n)
        {
            NextDay();
            i++;
        }
    }

}

void Date :: NextDay()
{
    day_++;
    
    if( day_ <1 )
    {
        month_--;
        
         if( month_ <1 )
        {
            year_--;
            month_=12;
        }
        
        if( month_ == 2 && GetDaysInYear(year_) == 366 )
        day_=29;
        
        else
        day_=calendar[month_-1]; 
    }
    
 
    if( calendar[month_-1] < day_ )
    {        
        if( month_==2 && GetDaysInYear(year_)==366)
        {
            if(day_>29)
            {
                month_++;
                day_=1;
            }
        }
        
        else
        {
            month_++;
            day_=1;
        }
    }

    
    if( month_>12 )
    {
        year_++;
        month_=1;
    }
}

bool Date :: SetDate(int year, int month, int day)
{
    year_=year;
    month_=month;
    day_=day;
    
    return true;
}

int Date :: year() const
{
    return year_;
}

int Date :: month() const
{
    return month_;
}

int Date :: day() const
{
    return day_;
}
               
int Date :: GetDaysInYear(int year)
{
    if( (year%4==0 && year%100!=0) ||year%400==0 )
    return 366;
    
    return 365;
}
        
int Date :: ComputeDaysFromYearStart(int year, int month, int day)
{
    
    if( GetDaysInYear(year) == 366 )
    {
        int sum=0;
        for(int i=0;i<month-1;i++)
        sum += calendar[i];
        
        if(month>=2)
        sum++;
        
        sum += day;   
        
        return sum;
    }
    
    else
    {
        int sum=0;
        for(int i=0;i<month;i++)
        sum += calendar[i];
        
        sum += day;
        
        return sum;
    }
    
}

ostream& operator<<(ostream& os, const Date& c)
{
    os << c.year()<<"."<<c.month()<<"."<<c.day();
    return os;   
}
istream& operator>>(istream& is, Date& c)
{
    char txt[100];
    string a;
    string b;
    string d;
    
    is >> txt;

    
    char *token[3];
    
    token[0] = strtok(txt,".");
    token[1] = strtok(NULL,".");
    token[2] = strtok(NULL,".");

    //cout << token[0] <<" "<< token[1] <<" "<< token[2] << endl;
    
    a = token[0];
    b = token[1];
    d = token[2];
    a =a+"."+b+"."+d;
    //cout << a;
    
    
    int h,m,s;
    h = atoi(token[0]);
    m = atoi(token[1]);
    s = atoi(token[2]);
    
    
    if( ((h%4==0 && h%100!=0) || h%400==0) )
    {
        if( m != 2 && s != 29 )
        {
            if( c.calendar[m-1] < s )
            {
                InvalidDateException K(a);
                throw K;
            }
        }
    }
    
    if( m>12 || m<1)
    {
        InvalidDateException K(a);
        throw K;
    }
    
    if( !((h%4==0 && h%100!=0) || h%400==0) )
    {
        if( c.calendar[m-1] < s )
        {
            InvalidDateException K(a);
            throw K;
        }
    }
    
    c.SetDate(h,m,s);
    
    return is;  
}
