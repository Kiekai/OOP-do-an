#include "TienHanh.h"
using namespace std;

int main() {

    Setting();
    FirstPage();

    while (PlayAgain()) {
        StartGame();
    }

    LastPage();

    system("pause");
    return 0;
}
