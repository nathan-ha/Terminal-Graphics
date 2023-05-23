#include <iostream>
using namespace std;

#include "terminalGraphics.h"

int main()
{
    terminalGraphics screen(10, 10);
    screen.at(1,3) = '1';
    screen.draw();

}