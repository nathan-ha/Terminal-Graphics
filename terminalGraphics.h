#pragma once
#include <vector>

void ShowConsoleCursor(bool showFlag);

class terminalGraphics {
private:
    std::vector<std::vector<char>> screen;
    int width;
    int height;
    char background;
public:
    terminalGraphics(int width = 0, int height = 0, char background = '*');
    ~terminalGraphics();
    /*Actual Drawing*/
    void clear() const; //clear terminal (does not clear array)
    void draw() const;  //draw screen

    /*Setters*/
    void resize(int newWidth, int newHeight);
    void setHeight(int newHeight);
    void setWidth(int setWidth);
    void changeBackground(char c);
    void reset(); //sets all elements of vector to background chararcter

    /*Getters*/
    int getHeight() const;
    int getWidth() const;
    int numRows() const;
    int numCols() const;
    char &at(int r, int c);
    const char &at(int r, int c) const;
    char getBackgroundChar() const;
    //gets borders
    int top() const;
    int bottom() const;
    int left() const;
    int right() const;


};