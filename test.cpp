#include <iostream>
using namespace std;

#include "terminalCanvas.h"

int main()
{
    terminalCanvas screen(25, 10);
    for (int r = screen.top(); r <= screen.bottom(); r++)
    {
        for (int c = screen.left(); c <= screen.right(); c++)
        {
            screen.at(r,c) = 'a';
        }
    }
    screen.at(screen.top(), screen.right()) = '!';
    screen.draw();

}