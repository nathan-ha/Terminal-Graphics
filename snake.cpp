#include <windows.h>
#include <iostream>
using namespace std;

#include "terminalCanvas.h"

const int CANVAS_WIDTH = 10;
const int CANVAS_HEIGHT = 10;
enum action {LEFT, RIGHT, UP, DOWN};

struct node
{
    int r, c;
    char symbol;
    node *next;

    node(int r = 0, int c = 0, char symbol = 'O') : r(r), c(c), next(nullptr) {}
};

class snake 
{
    private:
        node *head_;
        node *tail_;
        action direction;
    public:
        snake();
        ~snake();
        void append();
        bool update();
    private:
        //banning copies
        snake operator=(const snake &);
        snake(const snake &);
};

action getInput()
{
    if (GetAsyncKeyState('A') & 0x0001)
    {
        return LEFT;
    }
    if (GetAsyncKeyState('D') & 0x0001)
    {
        return RIGHT;
    }
    if (GetAsyncKeyState('W') & 0x0001)
    {
        return UP;
    }
    if (GetAsyncKeyState('S') & 0x0001)
    {
        return DOWN;
    }
}

int main()
{
    
}

snake::snake()
    : head_(new node(CANVAS_HEIGHT / 2, CANVAS_WIDTH / 2)),
      tail_(head_),
      direction(LEFT)
{
}

snake::~snake()
{
    while (head_ != nullptr)
    {
        node *victim = head_;
        head_ = head_->next;
        delete victim;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

//makes snake longer
void snake::append()
{
    tail_->next = new node(*tail_); //TODO: figure out what to actually append
    tail_ = tail_->next;
    tail_->next = nullptr;
}

//updates position of entire snake
//returns false when a collision occurred
bool snake::update()
{
    #include <stdexcept>
    throw std::runtime_error("create update()");
}

