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

    if( ((year_%4 ==0 && year_%100!=0)||year_%400==0))
    {
      if(month_ != 2 && day_ != 29)
      {
        if(calendar[month_-1]<day_)
        {
          InvalidDateException K(a);
          throw K
          return false;
        }
      }
    }

    if( month_>12 || month_<1)
    {
      InvalidDateException K(a);
      throw K;
      return false;
    }

    if( !((year_%4==0 && year_%100!=0) || year_%400==0) )
    {
      if(calendar[month_-1] < day_)
      {
        InvalidDateException K(a);
        throw K;
        return false;
      }
    }
    
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
    
    if( GetDaysInYear(year) == 366 && month >=2 )++sum;
    
        int sum=0;
        for(int i=0;i<month;i++)
        sum += calendar[i];
        
        sum += day;
        
        return sum;
}

istream& operator>>(istream& is, Date& c)
{
    string input;
    string a;
    is >> input;
    char *buf = strdup(input.c_str());
    
    char *token[3];
    
    token[0] = strtok(buf.".");
    token[1] = strtok(NULL,".");
    token[2] = strtok(NULL,".");

    
    a =token[0]+"."+token[1]+"."+token[2];
    //cout << a;
    
    
    int h,m,s;
    h = atoi(token[0]);
    m = atoi(token[1]);
    s = atoi(token[2]);
    
    
    c.SetDate(h,m,s);
    
    return is;  
}
