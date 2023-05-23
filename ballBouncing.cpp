#include <cstdlib>
#include <windows.h>
#include <vector>
#include <ctime>
#include <iostream>

#include "terminalCanvas.h"

struct ball
{
    int r, c;
    char icon;
    bool rDirection, cDirection; // true means moving in positive direction
    ball(int r = 0, int c = 0, bool rdir = true, bool cdir = true, char icon = '0')
        : r(r),
          c(c),
          rDirection(rdir),
          cDirection(cdir),
          icon(icon)
    {
    }
};
void frame(terminalCanvas &s, std::vector<ball> &balls, int delay_ms);
void move(terminalCanvas &s, ball &b);
int randIntInc(int min, int max);

int main()
{
    const int numBalls = 100;
    const int numFrames = 50;

    srand(time(0));

    terminalCanvas ctx(30, 20);
    std::vector<ball> balls;
    for (int i = 0; i < numBalls; i++)
    {
        //randomly generate a bunch of balls
        ball temp
        (
             randIntInc(ctx.top(), ctx.bottom()),
             randIntInc(ctx.left(), ctx.right()),
             static_cast<bool>(randIntInc(0, 1)),
             static_cast<bool>(randIntInc(0, 1)),
             static_cast<char>(randIntInc(33, 126))
        );
        balls.push_back(temp);
    }

    //actual animation
    for (int i = 0; i < numFrames; i++)
    {
        frame(ctx, balls, 80);
    }
}

void frame(terminalCanvas &s, std::vector<ball> &balls, int delay_ms)
{
    // set locations for balls
    for (int j = 0; j < balls.size(); j++)
    {
        auto curr = balls.at(j);
        s.at(curr.r, curr.c) = curr.icon;
    }
    
    s.draw();

    // undoes the last frame and moves the balls so it can be drawn on the next loop
    for (int j = 0; j < balls.size(); j++)
    {
        s.at(balls.at(j).r, balls.at(j).c) = s.getBackgroundChar();
        move(s, balls.at(j));
    }

    Sleep(delay_ms);
    s.clearTerminal();
}

//updates ball positoin
void move(terminalCanvas &s, ball &b)
{
    // detect collision with border
    if (b.r >= s.bottom() && b.rDirection == true)
    {
        b.rDirection = false;
    }
    else if (b.r <= s.top() && b.rDirection == false)
    {
        b.rDirection = true;
    }

    if (b.c >= s.right() && b.cDirection == true)
    {
        b.cDirection = false;
    }
    else if (b.c <= s.left() && b.cDirection == false)
    {
        b.cDirection = true;
    }

    // move ball
    if (b.rDirection)
    {
        b.r++;
    }
    else
    {
        b.r--;
    }
    if (b.cDirection)
    {
        b.c++;
    }
    else
    {
        b.c--;
    }
}

//returns random int (inclusive)
int randIntInc(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
