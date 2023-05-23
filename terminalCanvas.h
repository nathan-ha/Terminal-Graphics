#pragma once

void ShowConsoleCursor(bool showFlag);

class terminalCanvas
{
    private:
        char *screen_;
        int width_;
        int height_;
        char background_;

    public:
        terminalCanvas(int width = 0, int height = 0, char background = '*');
        ~terminalCanvas();

        /*Actual Drawing*/
        void clearTerminal() const;
        void draw() const;

        /*Setters*/
        void resize(int, int);
        void setHeight(int);
        void setWidth(int);
        void changeBackground(char);
        void reset();

        /*Getters*/
        char &at(int, int);
        const char &at(int, int) const;
        int getHeight() const;
        int getWidth() const;
        int numRows() const;
        int numCols() const;
        char getBackgroundChar() const;

        // gets borders
        int top() const;
        int bottom() const;
        int left() const;
        int right() const;
        
    private:
        int rcToIndex(int, int) const;
        //banning copies for now
        terminalCanvas(const terminalCanvas &);
        terminalCanvas operator=(const terminalCanvas &);
};