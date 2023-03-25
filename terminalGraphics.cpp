#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>

#include "terminalGraphics.h"

using namespace std;

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

terminalGraphics::terminalGraphics(int width, int height, char background) :
    width(width),
    height(height),
    background(background),
    screen(height, vector<char>(width, background)) //init 2d vector
{
    ShowConsoleCursor(false);
}

terminalGraphics::~terminalGraphics() {
    ShowConsoleCursor(true);
}

void terminalGraphics::draw() const {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            cout << screen[r][c] << ' ';
        }
        cout << '\n';
    }
}

void terminalGraphics::clear() const {
    system("cls");
}

int terminalGraphics::getHeight() const {
    return height;
}

int terminalGraphics::getWidth() const {
    return width;
}

void terminalGraphics::resize(int newWidth, int newHeight) {
    height = newHeight;
    width = newWidth;
    screen.resize(height);
    for (auto &row : screen) {
        row.resize(width, background);
    } 
}

void terminalGraphics::setHeight(int newHeight) {
    height = newHeight;
    screen.resize(height, vector<char>(width, background));
}

void terminalGraphics::setWidth(int newWidth) {
    width = newWidth;
    for (auto &row : screen) {
        row.resize(width, background);
    } 
}

char &terminalGraphics::at(int r, int c) {
    return screen.at(r).at(c);
}

const char &terminalGraphics::at(int r, int c) const {
    return screen.at(r).at(c);
}

int terminalGraphics::top() const {
    return 0;
}

int terminalGraphics::bottom() const {
    return height - 1;
}

int terminalGraphics::left() const {
    return 0;
}

int terminalGraphics::right() const {
    return width - 1;
}

void terminalGraphics::reset() {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            screen[r][c] = background;
        }
    }
}

int terminalGraphics::numRows() const {
    return height;
}
int terminalGraphics::numCols() const {
    return width;
}

char terminalGraphics::getBackgroundChar() const {
    return background;
}
