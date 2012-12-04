#include "world_clock.h"
WorldClock :: WorldClock ()
{
    time_difference_=0;
    time_h=0;
    time_m=0;
    time_s=0;
}

WorldClock :: WorldClock (int hour, int minute, int second)
{
    time_h = hour;
    time_m = minute;
    time_s = second;
    
}

void WorldClock :: Tick(int seconds)
{
    int c_h,c_m,c_s;
    c_h = seconds/3600;
    seconds = seconds%3600;
    
    c_m = seconds/60;
    seconds = seconds%60;
    
    c_s = seconds;
    
    time_h += c_h;
    time_m += c_m;
    time_s += c_s;
}

bool WorldClock :: SetTime(int hour, int minute, int second)
{
    
}

bool WorldClock :: LoadTimezoneFromFile(const string& file_path)
{    
   
}
bool WorldClock :: SetTimezone(const string& timezone)
{
    if( ig[timezone] == 0)
    {
        cout<<(time_h+ig[timezone])%24<<":"<<time_m<<":"<<time_s<<endl;
        return true;
    }
    
    
    cout<<(time_h+ig[timezone])%24<<":"<<time_m<<":"<<time_s<<" (+"<<ig[timezone]<<")"<<endl;
    return true;
}

void WorldClock :: AddTimezoneInfo(const string& city, int diff)
{
    ig[city] = diff;
}

int WorldClock :: hour() const
{
    return time_h;   
}

int WorldClock :: minute() const
{
    return time_m;   
}

int WorldClock :: second() const
{
    return time_s;   
}

ostream& operator<<(ostream& os, WorldClock& c)
{
    int q=c.hour();
    int w=c.minute();
    int e=c.second();
    //os<<q<<":"<<w<<":"<<e<<endl;  
    
    if( e >= 60 )
    {
        w = w + e/60;
        
        e = e-60*(e/60);
    }
    if( w >= 60 )
    {
        q = q + w/60;
        w = w-60*(w/60);
    }
    if( q>= 24 )
    {
        q = q % 24;
    }
    
    while(1)
    {
        if( e < 0 )
        {
            e=e+60;
            w--;
        }
        
        if( w < 0 )
        {
            w=w+60;
            q--;
        }
        if( q < 0 )
        {
            q = 24+q;
        }
        
        if( q>=0 && w>=0 && e>=0 )
        break;
    }

    c.time_h = q;
    c.time_m = w;
    c.time_s = e;
    
    os<<q<<":"<<w<<":"<<e;    
    return os;
}

istream& operator>>(istream& is, WorldClock& c) // hh:mm
{
    char txt[100];
    string a;
    string b;
    string d;
    
    is >> txt;

    
    char *token[3];
    
    token[0] = strtok(txt,":");
    token[1] = strtok(NULL,":");
    token[2] = strtok(NULL,":");

    //cout << token[0] <<" "<< token[1] <<" "<< token[2] << endl;
    
    a = token[0];
    b = token[1];
    d = token[2];
    a =a+":"+b+":"+d;
    
    
    int h,m,s;
    h = atoi(token[0]);
    m = atoi(token[1]);
    s = atoi(token[2]);

    c.time_h = h;
    c.time_m = m;
    c.time_s = s;
    
    if( h<0 || h>=24 )
    {
        InvalidTimeException k(a);
        throw k;
    }
    
    if( m<0 || m>=60 )
    {
        InvalidTimeException k(a);
        throw k;
    }
    
    if( s<0 || s>=60 )
    {
        InvalidTimeException k(a);
        throw k;
    }
}
