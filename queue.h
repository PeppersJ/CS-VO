// Test space for AI
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
    const node& operator [](int i) const;
    int dequeue();
    void enqueue(int);
    bool isempty();
    bool isfull();
    void update(node** a, int arrSize, int curIndex);
    int size() const;
    node** arr{ NULL };
private:
    bool swap(node* a, node* b);
    int m_front;
    int m_rear;
    int m_MAXSIZE{ 0 };
    int m_curIndex{ 0 };
    int m_size{ 0 };
};
#endif
