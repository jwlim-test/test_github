#include <iostream>
#include <string>

using namespace std;

class Date {
    public:
        Date() {        // ������ ���� YM�迭�� �� ������ ��¥���� ������ѳ���
                        // ������ �ƴ� ���� ���� M�迭�� �� ������ ��¥���� ���� 
            YM[1]=YM[3]=YM[5]=YM[7]=YM[8]=YM[10]=YM[12]=31;
            YM[4]=YM[6]=YM[9]=YM[11]=30;
            YM[2]=29;
            M[1]=M[3]=M[5]=M[7]=M[8]=M[10]=M[12]=31;
            M[4]=M[6]=M[9]=M[11]=30;
            M[2]=28;       
        }
        Date(int year, int month, int day){   // constructor�� ����� parametor�� ���� ��,��,���� ������ ���� 
            year_ = year;
            month_ = month;
            day_ = day;
            YM[1]=YM[3]=YM[5]=YM[7]=YM[8]=YM[10]=YM[12]=31;
            YM[4]=YM[6]=YM[9]=YM[11]=30;
            YM[2]=29;
            M[1]=M[3]=M[5]=M[7]=M[8]=M[10]=M[12]=31;
            M[4]=M[6]=M[9]=M[11]=30;
            M[2]=28;  
        }
        void NextDay(int n = 1){             // defalut������ 1�� �����߱� ������ parametor������ ������� n=1�� ��޵Ǿ� ����  
            if(n ==1){
                if(GetDaysInYear(year_) == 366){
                    day_++;
                    if(day_ > YM[month_]){              //���⼭ �������� �ƴ��� �κз��� �з��ؼ� ����ϴ°��� point!!! 
                        day_ -= YM[month_];             // �����Ͻ� day_++���� �� ���� ��¥���� day_�� ������ �� ���� ��¥����ŭ���� month_++�Ѵ�.   
                        month_++;
                    }
                    if(month_ > 12){                            //month_�� 12�� ������ month_-12���� year_ ++ 
                        month_ -=12;
                        year_ ++;
                    }
                }
                else {                                          //������ �ƴѰ�� M���� ����ϴ°͸���� ���͵���!  
                    day_++;
                    if(day_ > M[month_]){
                        day_ -= M[month_];
                        month_++;
                    }
                    if(month_ > 12){
                        month_ -=12;
                        year_ ++;
                    }
                }       
            }
            else {                                    // n=1�� �ƴϰ� �ٸ����� ���ð�� ����ϴ� ��� !! 
                int days=0;
                days = ComputeDaysFromYearStart(year_,month_,day_) + n;    // days��� ������ ���� ������ ��,��,�� ������ ������ n������ ���� 
                // ���� �þ�� ���� 
                if( days > GetDaysInYear(year_)){                    // 1. days�� year�� �������� Ŭ��� 
                    while( days > GetDaysInYear(year_)){
                        days -= GetDaysInYear(year_);                // <point> while���� �߿��ѵ� while������ ������ ������ ����. 
                        year_++;                                     // ���ٶ� ������ 365�� ���°��̾ƴ� year�� ������Ų ���� ������ ����� ���ش�. 
                    }                                                // ���ְ��� ���� days�� ���ð��̹Ƿ� �װ����� ������ ��¥�� ���!!! 
                    if(GetDaysInYear(year_) == 366){                 
                        int MONTH=1;
                        while (1){
                            if(days > YM[MONTH]){                    // 1���� ������ ���ϰ� �����Ͻ� YM�� �̿��� �ſ� ������ ������ month ���Ѵ� 
                                days -= YM[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;                         // ���ϱ� �Ҷ��� 1��1�Ͽ��� ���ϴ°��̹Ƿ� 1���� �����ش�!! 
                                break;
                            }
                        }     
                    }
                    else {                                           //������ �ƴҽÿ��� M�� �̿��ϴ� ���̿� ���͵���! 
                        int MONTH=1;
                        while (1){
                            if(days > M[MONTH]){
                                days -= M[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }          
                    }
                }
                // ���� �پ��� ���� 
                else if( days <= 0){
                    while( days <= 0){                     //�����پ��� ������ ����Ʈ�� while���� �Ἥ �� �پ�� ���� ������ ���ִ°�������Ʈ!! 
                        year_--;
                        days += GetDaysInYear(year_);
                    }
                    if(GetDaysInYear(year_) == 366){
                        int MONTH=1;
                        while (1){
                            if(days > YM[MONTH]){           // ���������� ���������ϴ� ������ ���� ���� days�� ������  
                                days -= YM[MONTH];          // �ű⼭���� ����,������ �ƴ��� �ľ��� �Ŵ� YM,M���̿��� ���༭ ���Ѵ�. 
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }     
                    }
                    else {
                        int MONTH=1;
                        while (1){
                            if(days > M[MONTH]){
                                days -= M[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }          
                    } 
                }
                // �ϳ� ���ǹ���  
                else {
                    if(GetDaysInYear(year_) == 366){                //�ϳ� �̳��� �����Ͻÿ��� while����� ������ ������ �����ʿ� �����Ƿ� �ٷν��� 
                        int MONTH=1;
                        while (1){
                            if(days > YM[MONTH]){
                                days -= YM[MONTH];
                                MONTH++;                           //�������� �ƴ����� �Ǵ��� ���Ͱ��� ������� ��¥������ش�! 
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }     
                    }
                    else {
                        int MONTH=1;
                        while (1){
                            if(days > M[MONTH]){
                                days -= M[MONTH];
                                MONTH++;
                                if(MONTH>12)
                                    MONTH-=12;
                            }
                            else {
                                month_=MONTH;
                                day_=days+1;
                                break;
                            }
                        }          
                    }   
                }
            }
        }
        bool SetDate(int year, int month, int day);              //�ùٸ� ��¥�� ���ð�� true return �ƴҰ�� false return 
        int year() const { return year_; }                       // year return
        int month() const { return month_; }                     // month return
        int day() const { return day_; }                         // day return
    private:
// ������ �Ǵ��Ͽ� �־��� ������ �ش��ϴ� ��¥ ��(365 �Ǵ� 366)�� ����.
        static int GetDaysInYear(int year);
// �ش� ��¥�� �ش� ������ ó��(1�� 1��)���� ��ĥ°������ ���.
        static int ComputeDaysFromYearStart(int year, int month, int day);
        int year_, month_, day_;
        int M[12], YM[12];                                        // �ſ� ��¥���� �ִ� array  
};

struct InvalidDateException {
    string input_date;
    InvalidDateException(const string& str) : input_date(str) {}
};
