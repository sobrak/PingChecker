#include <iostream>
#include <ctime>
using namespace std;
int main() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    while (true)
    {
        int x = system("ping 8.8.8.8 > log.txt");
        if (x == 0) {
            cout << "success" << "\n";
            cout << "\n";
        }
        else {
            cout << "FAILED" << "\n";
            cout << "Error time : " << asctime(localtm) << "\n";
            cout << "\n";
        }
    }
}