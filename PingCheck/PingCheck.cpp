#include <iostream>
using namespace std;
int main() {
    while (true)
    {
        int x = system("ping 8.8.8.8 > log.txt");
        if (x == 0) {
            cout << "success" << "\n";
        }
        else {
            cout << "failed" << "\n";
        }
    }
}