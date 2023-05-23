#include <cstdlib>
#include <windows.h>
#include <vector>
#include <ctime>
#include "terminalGraphics.h"

struct ball
{
    int r, c;
    char icon;
    bool rDirection, cDirection; // true means moving in positive direction
    ball(int r = 1, int c = 1, bool rdir = true, bool cdir = true, char icon = '0') : r(r),
                                                                                      c(c),
                                                                                      icon(icon),
                                                                                      rDirection(rdir),
                                                                                      cDirection(cdir)
    {
    }
};

void drawFrame(terminalGraphics &s, std::vector<ball> &balls, int delay_ms);
void move(terminalGraphics &s, ball &b);
int randIntInc(int min, int max);

int main()
{
    srand(time(0));

    terminalGraphics ctx(15, 8);
    // ball b(0,1);
    // ball b(randIntInc(ctx.top(), ctx.bottom()), randIntInc(ctx.left(), ctx.right()), randIntInc(0, 1));
    std::vector<ball> balls;
    for (int i = 0; i < 5; i++)
    {
        ball temp(randIntInc(ctx.top(),
                             ctx.bottom()),
                  randIntInc(ctx.left(), ctx.right()),
                  randIntInc(0, 1),
                  randIntInc(0, 1),
                  randIntInc(33, 126));
        balls.push_back(temp);
    }

    for (int i = 0; i < 200; i++)
    { // number of frames
        drawFrame(ctx, balls, 60);
    }
}

void drawFrame(terminalGraphics &s, std::vector<ball> &balls, int delay_ms)
{
    // set locations for balls
    for (int j = 0; j < balls.size(); j++)
    {
        s.at(balls.at(j).r, balls.at(j).c) = balls.at(j).icon;
    }
    s.draw(); // draws balls
    // undoes the last frame and moves the balls so it can be drawn on the next loop
    for (int j = 0; j < balls.size(); j++)
    {
        s.at(balls.at(j).r, balls.at(j).c) = s.getBackgroundChar();
        move(s, balls.at(j));
    }
    Sleep(delay_ms);
    s.clear();
}

void move(terminalGraphics &s, ball &b)
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

int randIntInc(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
