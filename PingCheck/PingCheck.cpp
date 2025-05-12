#include <iostream>
#include <ctime>
#include <windows.h>

time_t now = time(0);
tm* localtm = localtime(&now);
int PingResult;
bool IsFailed = false;
bool WaitingConnect = false;

int main() {
    while (true)
    {
        PingResult = system("ping 8.8.8.8 > log.txt");

        if (PingResult == 0) {
            WaitingConnect = false;
            system("Color 0A");
            std::cout <<  "success" << "\n";
            std::cout << "\n";
        }
        else {
            IsFailed = true;
            if (!WaitingConnect)
            {
                WaitingConnect = true;
                system("Color 04");
                std::cout << "FAILED" << "\n";
                std::cout << "Error time : " << asctime(localtm) << "\n";
                std::cout << "Waiting for connect..." << "\n";
                std::cout << "\n";
            }
        }
    }
}