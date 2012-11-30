//메인함수는 주어진 형식과 동일하므로 주석skip 
#include "world_clock.h"
int main() {
    WorldClock clock;
    string cmd;
    while (cmd != "quit") {
          cin >> cmd;
       try {
          if (cmd == "set") {
             cin >> clock;
             cout << clock;
          }
          else if (cmd == "tick") {
               int tick = 1;
               cin >> tick;
               clock.Tick(tick);
               cout << clock;
          }
          else if (cmd == "set_timezone") {
               string name;
               cin >> name;
               clock.SetTimezone(name);
               cout << clock;
          }
          else if (cmd == "add_timezone_info") {
               string name;
               int time_difference;
               cin >> name >> time_difference;
               clock.AddTimezoneInfo(name, time_difference);
          }
       }
       catch (InvalidTimeException& e) {
            cout << "Invalid time: " << e.input_time << endl;
       }
    }
    return 0;
}
