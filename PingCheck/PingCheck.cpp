#include "PingCheck.h"
#include "ping.h"

void ConnectionRestored();
void UpdateTime();
void ConnectionFailed();
void Info();
void menu();

time_t now = time(0);
tm* localtm = localtime(&now);
ping PingState;

int delay = 100;

std::ofstream writefile;

int main() {
    menu();
}

void monitoring() {
    while (true)
    {
        PingState.PingResult = system("ping 8.8.8.8 -n 1 > log_ping.txt");

        if (PingState.PingResult == 0 && PingState.WaitingConnect) {
            ConnectionRestored();
        }

        if (PingState.PingResult == 0) {
            PingState.WaitingConnect = false;
            //system("Color 0A");
            std::cout << "success" << std::endl;
            Sleep(delay);
            std::cout << std::endl;
        }
        else {
            ConnectionFailed();
        }
    }
}

void menu() {
    unsigned short option = 0;
    std::cout << "pick option: " << std::endl;
    std::cout << "  1 - start monitoring" << std::endl;
    std::cout << "  2 - set ping delay" << std::endl;
    std::cin >> option;
    if (option == 1) { monitoring(); }
    if (option == 2) {
        std::cout << "curret delay is " << delay << " new -> ";
        std::cin >> delay;
        system("cls");
        menu();
    }
}

void ConnectionRestored()
{
    //system("Color 0A");
    UpdateTime();
    std::cout << "Connection restored! : " << asctime(localtm) << std::endl;
}

void ConnectionFailed()
{
    PingState.IsFailed = true;
    if (!PingState.WaitingConnect) {
        PingState.WaitingConnect = true;
        //system("Color 04");
        std::cout << "FAILED" << std::endl;
        UpdateTime();
        std::cout << "Error time : " << asctime(localtm) << std::endl;
        PingState.FailedTime.push_back(asctime(localtm));
        std::cout << "Waiting for connect..." << std::endl;
        std::cout << std::endl;
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
            std::cout << "AN ERROR OCCURRED IN: " << i << " logged in log.txt" << std::endl;
        }
        writefile.close();
    }
    else {
        std::cout << "No errors!";
    }
}