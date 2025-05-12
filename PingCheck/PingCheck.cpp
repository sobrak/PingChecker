#include <iostream>
#include <ctime>
#include <windows.h>

void ConnectionRestored();
void UpdateTime();

time_t now = time(0);
tm* localtm = localtime(&now);
int PingResult;
bool IsFailed = false;
bool WaitingConnect = false;

int main() {
    while (true)
    {
        PingResult = system("ping 8.8.8.8 > log.txt");

        if (PingResult == 0 && WaitingConnect) {
            ConnectionRestored();
        }

        if (PingResult == 0) {
            WaitingConnect = false;
            system("Color 0A");
            std::cout <<  "success" << "\n";
            std::cout << "\n";
        }
        else {
            IsFailed = true;
            if (!WaitingConnect) {
                WaitingConnect = true;
                system("Color 04");
                std::cout << "FAILED" << "\n";
                UpdateTime();
                std::cout << "Error time : " << asctime(localtm) << "\n";
                std::cout << "Waiting for connect..." << "\n";
                std::cout << "\n";
            }
        }
    }
}

void ConnectionRestored()
{
    system("Color 0A");
    UpdateTime();
    std::cout << "Connection restored! : " << asctime(localtm) << "\n";
}

void UpdateTime()
{
    now = time(0);
    localtm = localtime(&now);
}