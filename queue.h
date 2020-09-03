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
    queue(const queue& objB);
    queue& operator = (const queue& objB);
    int operator [](int i) const;

    int dequeue();
    void enqueue(int);
    void heapify(node** arr, int arrSize, int curIndex);

    bool isempty() const;
    bool isfull() const;
    int size() const;
    int peek() const;
    int tail() const;
    int front() const;
    int rear() const;
    int curSize() const;
    int maxSize() const;

    node** arr{ NULL };
private:
    int m_MAXSIZE{ 0 };
    int m_front{ -1 };
    int m_rear{ -1 };
    int m_size{ 0 };
    int m_curIndex{ 0 };    // Used only for heap function
    
    bool swap(node* a, node* b);
};
#endif
