#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>

#include "terminalGraphics.h"

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

terminalGraphics::terminalGraphics(int width, int height, char background)
    : width(width), //num columns
      height(height), //num rows
      background(background),
      screen(new char[width * height]) //declare block of memory instead of 2d array for memory purposes
{
    //assign each element with background char
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            //note: move vertically for switching rows, horizontally for columns
            at(r, c) = background;
        }
    }
    ShowConsoleCursor(false);
}

terminalGraphics::~terminalGraphics()
{
    delete[] screen;
    screen = nullptr;
    ShowConsoleCursor(true);
}

void terminalGraphics::draw() const
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            cout << at(r, c) << ' ';
        }
        cout << '\n';
    }
}

void terminalGraphics::clear() const
{
    system("cls");
}

int terminalGraphics::getHeight() const
{
    return height;
}

int terminalGraphics::getWidth() const
{
    return width;
}

void terminalGraphics::resize(int newWidth, int newHeight)
{
    // height = newHeight;
    // width = newWidth;
    // screen.resize(height);
    // for (auto &row : screen)
    // {
    //     row.resize(width, background);
    // }
}

void terminalGraphics::setHeight(int newHeight)
{
    // height = newHeight;
    // screen.resize(height, vector<char>(width, background));
}

void terminalGraphics::setWidth(int newWidth)
{
    // width = newWidth;
    // for (auto &row : screen)
    // {
    //     row.resize(width, background);
    // }
}

char &terminalGraphics::at(int r, int c) 
{
    return screen[r + width * c];
}

const char &terminalGraphics::at(int r, int c) const
{
    return screen[r + width * c];
}

//converts coordinates to index of array
int terminalGraphics::index(int r, int c) const
{
    return r + width * c;
}

int terminalGraphics::top() const
{
    return 0;
}

int terminalGraphics::bottom() const
{
    return height - 1;
}

int terminalGraphics::left() const
{
    return 0;
}

int terminalGraphics::right() const
{
    return width - 1;
}

void terminalGraphics::reset()
{
    // for (int r = 0; r < height; r++)
    // {
    //     for (int c = 0; c < width; c++)
    //     {
    //         screen[r][c] = background;
    //     }
    // }
}

int terminalGraphics::numRows() const
{
    return height;
}
int terminalGraphics::numCols() const
{
    return width;
}

char terminalGraphics::getBackgroundChar() const
{
    return background;
}
