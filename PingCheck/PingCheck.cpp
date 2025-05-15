#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
#include "ping.h"
#include <fstream>

void ConnectionRestored();
void UpdateTime();
void ConnectionFailed();
void Info();

time_t now = time(0);
tm* localtm = localtime(&now);
ping PingState;

std::ofstream writefile;

int main() {
    while (true)
    {
        PingState.PingResult = system("ping 8.8.8.8 -n 1 > log_ping.txt");

        if (PingState.PingResult == 0 && PingState.WaitingConnect) {
            ConnectionRestored();
        }

        if (PingState.PingResult == 0) {
            PingState.WaitingConnect = false;
            system("Color 0A");
            std::cout <<  "success" << "\n";
            std::cout << "\n";
        }
        else {
            ConnectionFailed();
        }
    }
}

void ConnectionRestored()
{
    system("Color 0A");
    UpdateTime();
    std::cout << "Connection restored! : " << asctime(localtm) << "\n";
}

void ConnectionFailed()
{
    PingState.IsFailed = true;
    if (!PingState.WaitingConnect) {
        PingState.WaitingConnect = true;
        system("Color 04");
        std::cout << "FAILED" << "\n";
        UpdateTime();
        std::cout << "Error time : " << asctime(localtm) << "\n";
        PingState.FailedTime.push_back(asctime(localtm));
        std::cout << "Waiting for connect..." << "\n";
        std::cout << "\n";
        Info();
    }
}

void UpdateTime()
{
    now = time(0);
    localtm = localtime(&now);
}

void Info()
{
    if (!PingState.FailedTime.empty()) {
        writefile.open("log.txt");
        for (std::string i : PingState.FailedTime)
        {
            if (writefile.is_open())
            {
                writefile << "AN ERROR OCCURRED IN: " << i << std::endl;
            }
            std::cout << "AN ERROR OCCURRED IN: " << i << " logged in log.txt" << "\n";
        }
        writefile.close();
    }
    else {
        std::cout << "No errors!";
    }
}