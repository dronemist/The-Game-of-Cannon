#include <sstream>
#include <iostream>

using namespace  std;

int main() {
    string move = "S 1 2 M 3 4";    
    istringstream ss(move);
    string token;

    while(ss>>token) {
        cout << token << '\n';
    }
    return 0;
}
