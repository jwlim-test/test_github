#include "world_clock.h"

void WorldClock::Tick(int second){
    
    int NowTimeSecond_=hour_*3600+minute_*60+second_; //���� ������ �ð��� ���� �ʷ� ȯ�� 
    
    NowTimeSecond_+=second; 

    while(NowTimeSecond_<0) //���� �ð��� ������ ��� �Ϸ� ������ �ð��� �߰����ش� 
        NowTimeSecond_+=24*3600;
    
    while(NowTimeSecond_>24*3600) //���� �ð��� �Ϸ簡 �Ѵ� ��� �Ϸ��� �ð��� ���ش� 
        NowTimeSecond_-=24*3600;
        
    hour_=(NowTimeSecond_/3600)%24; //�ð��� 3600�ʷ� ���� ���� 24�ð����� �ٽ� ������ �������� �ȴ� 
    NowTimeSecond_%=3600;
    minute_=NowTimeSecond_/60; //���� 60���� ���� ���̴� 
    second_=NowTimeSecond_%60; //�ʴ� 60���� ���� �������̴� 

    
}

bool WorldClock::SetTime(int hour, int minute, int second){
    
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


void WorldClock::AddTimezoneInfo(const string& city, int diff){     
            //�ð����� ����� ������ �� ������ timezone_���  map�� ���� 
            timezone_[city]=diff;
        
        
        }
        
bool WorldClock::SetTimezone(const string& timezone){
    
    (*this).Tick(-time_difference_*3600); //������ 0�̾��� �ʱ�ð����� ���� 
    if(timezone!="GMT" && timezone_[timezone]==0) //timezone�� ������ �ԷµǾ����� Ȯ�� 
        return false;
        
    time_difference_=timezone_[timezone]; //������ �� ������ ������ ���� 
    
    
    
    (*this).Tick(time_difference_*3600); //�� ������ŭ Tick �Լ� ȣ�� 
    return true;

}

ostream& operator<<(ostream& os, const WorldClock& c){
    if(c.time_difference()==0) //������ 0�� ��� �׳� ��������� 0�� �ƴҰ�� (+ )�� ������ ǥ�� 
        os<<c.hour()<<":"<<c.minute()<<":"<<c.second();
    else
        os<<c.hour()<<":"<<c.minute()<<":"<<c.second()
        <<" (+"<<c.time_difference()<<")";
        
    return os;
}

istream& operator >>(istream& is, WorldClock& c){
    //�Է¹��� char�� �迭�� ���� 
    char time[1000];
    
    is>>time;
    //�Է¹޾Ƽ� ����� �ԷµǾ����� Ȯ���ϰ� �Է��� �ȉ��� ���  InvalidTimeException�� �����ϱ����� ���ڿ� ���� 
    string time_;
    for(int i=0; time[i]!='\0'; i++) time_.push_back(time[i]);
    
    //��,��,�ʸ� ���� �߶� ����� �´��� Ȯ�� 
    char* ptr;
    ptr = strtok( time, ":");
    int hour = atoi(ptr);
    ptr = strtok( NULL,":");
    int minute = atoi(ptr);
    ptr = strtok( NULL,":");
    int second = atoi(ptr);
    
    //���� ������� InvalidTimeException�� ���� 
    if(!c.SetTime(hour,minute,second)) throw InvalidTimeException(time_);
    
    return is;
}
