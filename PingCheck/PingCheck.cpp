#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

int main() {

    time_t now = time(0);
    tm* localtm = localtime(&now);
    bool Is_Failed = false;

    while (true)
    {
        int x = system("ping 8.8.8.8 > log.txt");
        if (x == 0) {
            system("Color 0A");
            cout <<  "success" << "\n";
            cout << "\n";
        }
        else {
            if (!Is_Failed)
            {
                Is_Failed = true;
                system("Color 04");
                cout << "FAILED" << "\n";
                cout << "Error time : " << asctime(localtm) << "\n";
                cout << "Waiting for connect..." << "\n";
                cout << "\n";
            }
        }
    }
}