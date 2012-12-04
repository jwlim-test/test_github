#include "world_clock.h"

void WorldClock::Tick(int second)
{
    
    int now_time_second_=hour_*3600+minute_*60+second_; //���� ������ �ð��� ���� �ʷ� ȯ�� 
    
    now_time_second_+=second; 

    while(now_time_second_<0) //���� �ð��� ������ ��� �Ϸ� ������ �ð��� �߰����ش� 
        now_time_second_+=24*3600;
    
    while(now_time_second_>24*3600) //���� �ð��� �Ϸ簡 �Ѵ� ��� �Ϸ��� �ð��� ���ش� 
        now_time_second_-=24*3600;
        
    hour_=(now_time_second_/3600)%24; //�ð��� 3600�ʷ� ���� ���� 24�ð����� �ٽ� ������ �������� �ȴ� 
    now_time_second_%=3600;
    minute_=now_time_second_/60; //���� 60���� ���� ���̴� 
    second_=now_time_second_%60; //�ʴ� 60���� ���� �������̴� 

    
}

bool WorldClock::SetTime(int hour, int minute, int second)
{
    
    //�ð��� �߸� ���� ��쿡 false �� ���Ͻ��Ѽ� InvalidTimeException�� �߻���Ų�� 
    if(hour>=24 || hour<0) return false; 
    else if(minute>=60 || minute<0) return false;
    else if(second>=60 || second<0) return false;
    
    time_difference_=0;
    hour_=hour;
    minute_=minute;
    second_=second;
    
    return true;
}


void WorldClock::AddTimezoneInfo(const string& city, int diff)
{
     //�ð����� ����� ������ �� ������ timezone_���  map�� ���� 
     timezone_[city]=diff;   
}
        
bool WorldClock::SetTimezone(const string& timezone)
{
    
    (*this).Tick(-time_difference_*3600); //������ 0�̾��� �ʱ�ð����� ���� 
    map<string, int>::const_iterator check=timezone_.find(timezone);
    if(check==timezone_.end()) //timezone�� ������ �ԷµǾ����� Ȯ�� 
        return false;
        
    time_difference_=timezone_[timezone]; //������ �� ������ ������ ���� 
    
    
    
    (*this).Tick(time_difference_*3600); //�� ������ŭ Tick �Լ� ȣ�� 
    return true;

}

ostream& operator<<(ostream& os, const WorldClock& c)
{
    if(c.time_difference()==0) //������ 0�� ��� �׳� ��������� 0�� �ƴҰ�� (+ )�� ������ ǥ�� 
        os<<c.hour()<<":"<<c.minute()<<":"<<c.second();
    else
        os<<c.hour()<<":"<<c.minute()<<":"<<c.second()
        <<" (+"<<c.time_difference()<<")";
        
    return os;
}

istream& operator >>(istream& is, WorldClock& c)
{
    //�Է¹��� char�� �迭�� ���� 
    string time;
    
    is>>time;
    //�Է¹޾Ƽ� ����� �ԷµǾ����� Ȯ���ϰ� �Է��� �ȉ��� ���  InvalidTimeException�� �����ϱ����� ���ڿ� ���� 
    char* buf=strdup(time.c_str());
    
    //��,��,�ʸ� ���� �߶� ����� �´��� Ȯ�� 
    char* ptr;
    ptr = strtok( buf, ":");
    int hour = atoi(ptr);
    ptr = strtok( NULL,":");
    int minute = atoi(ptr);
    ptr = strtok( NULL,":");
    int second = atoi(ptr);
    
    free(buf);
    //���� ������� InvalidTimeException�� ���� 
    if(!c.SetTime(hour,minute,second)) throw InvalidTimeException(time);
    
    return is;
}
