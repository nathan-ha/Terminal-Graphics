#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <stdexcept>

#include "terminalCanvas.h"

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

//note: move vertically for switching rows, horizontally for columns
//r is analagous to a flipped y-axis (down is positive direction)
//c is analagous to the x-axis (right is positive directoin)
terminalCanvas::terminalCanvas(int width, int height, char background)
    : width_(width), //num columns
      height_(height), //num rows
      background_(background),
      screen_(new char[width * height]) //declare block of memory instead of 2d array for memory purposes
{
    //fill canvas with background_
    int numElements = width * height;
    for (int i = 0; i < numElements; i++)
    {
        screen_[i] = background;
    }
    ShowConsoleCursor(false);
}

terminalCanvas::~terminalCanvas()
{
    delete[] screen_;
    screen_ = nullptr;
    ShowConsoleCursor(true);
}

//draws the canvas into the terminal
void terminalCanvas::draw() const
{
    for (int r = 0; r < height_; r++)
    {
        for (int c = 0; c < width_; c++)
        {
            cout << at(r, c) << ' ';
        }
        cout << '\n';
    }
}

//clears the terminal
void terminalCanvas::clearTerminal() const
{
    system("cls");
}

//gets the height (number of rows) of canvas
int terminalCanvas::getHeight() const
{
    return height_;
}

//gets the width (number of columns) of canvas
int terminalCanvas::getWidth() const
{
    return width_;
}

//resizes the canvas (warning: all old data will be lost)
void terminalCanvas::resize(int newWidth, int newHeight)
{
    width_ = newWidth;
    height_ = newHeight;
    delete screen_;
    screen_ = new char[newWidth * newHeight];
}

void terminalCanvas::changeBackground(char newBG)
{
    background_ = newBG;
}

//changes the height of the canvas (warning: all old data will be lost)
void terminalCanvas::setHeight(int newHeight)
{
    resize(width_, newHeight);
}

//changes the width of the canvas (warning: all old data will be lost)
void terminalCanvas::setWidth(int newWidth)
{
    resize(newWidth, height_);
}

//gets the element at (r,c)
char &terminalCanvas::at(int r, int c) 
{
    return screen_[width_ * r + c];
}

//gets the element at (r,c)
const char &terminalCanvas::at(int r, int c) const
{
    return screen_[width_ * r + c];
}

//converts r-c coordinates to index of array
int terminalCanvas::rcToIndex(int r, int c) const
{
    return width_ * r + c;
}

//returns r-coordinate of the top of the canvas
int terminalCanvas::top() const
{
    return 0;
}

//returns r-coordinate of the bottom of the canvas
int terminalCanvas::bottom() const
{
    return height_ - 1;
}

//returns c-coordinate of left edge of canvas
int terminalCanvas::left() const
{
    return 0;
}

//returns c-coordinate of right edge of canvas
int terminalCanvas::right() const
{
    return width_ - 1;
}

//overwrites everything in the canvas with the default background
void terminalCanvas::reset()
{
    int numElements = height_ * width_;
    for (int i = 0; i < numElements; i++)
    {
        screen_[i] = background_;
    }
}

//returns number of rows in canvas (height)
int terminalCanvas::numRows() const
{
    return height_;
}

//returns number of rows in columns (width)
int terminalCanvas::numCols() const
{
    return width_;
}

//returns character used as the default background
char terminalCanvas::getBackgroundChar() const
{
    return background_;
}
