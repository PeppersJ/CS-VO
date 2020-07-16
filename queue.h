#ifndef QUEUE_H
#define QUEUE_H
#include <ncurses.h>    //I/O to terminal

struct node {
    node();
    node(int d, int p);
    int data { -1 };
    int priority{ -1 };
};
// Priority Queue
// Min heap
class queue {
public:
    queue();
    queue(int s);
    ~queue();

    int operator [](int i) const;

    int dequeue();
    void enqueue(int);
    void heapify(node** a, int arrSize, int curIndex);

    bool isempty() const;
    bool isfull() const;
    int size() const;
    int peek() const;
    int tail() const;

    node** arr{ NULL };
private:
    int m_front;
    int m_rear;
    int m_MAXSIZE{ 0 };
    int m_curIndex{ 0 };
    int m_size{ 0 };
    
    bool swap(node* a, node* b);
};
#endif
