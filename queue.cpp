#include "queue.h"

node::node(){}
node::node(int d, int p) : data(d), priority(p){}

queue::queue() { /*Empty*/ }
queue::queue(int size) : m_MAXSIZE(size) {
    m_front = m_rear = 0;
    arr = new node*[m_MAXSIZE];
    for(int i = 0; i < m_MAXSIZE; i++)
    arr[i] = new node;
}
queue::~queue(){
    for(int i = 0; i < m_MAXSIZE; i++)
        delete arr[i];
    delete[] arr;
}
const node& queue::operator [](int i) const{
    return *arr[i];
}
bool queue::isfull() { 
    if(m_front == 0 && m_rear == m_MAXSIZE - 1 || m_rear == m_front - 1)
        return true;
    return false;
}
bool queue::isempty() { return (m_front == -1) ? true : false; }
node* queue::dequeue() {
    if (isempty())
        return arr[0];

    node* temp = arr[m_front];  // preserve
    arr[m_front]->data = -1;    // reset
    arr[m_front]->priority = -1;
    if (m_front == m_rear)
        m_front = m_rear = -1;
    else if (m_front == m_MAXSIZE - 1)
        m_front = 0;
    else
        m_front++;

    return arr[m_front];
}
node* queue::enqueue(node* newNode) {
    if (isfull()) 
        return arr[0];
    else if (m_front == -1) { // First element only
        m_front = m_rear = 0;
        arr[m_rear] = newNode;
    }
    else if (m_rear == m_MAXSIZE - 1) {
        m_rear = 0;
        arr[m_rear] = newNode;
    } else {
        m_rear++;
        arr[m_rear] = newNode;
    }
}
void queue::update(node** a, int arrSize, int curIndex) { //heapifies min heap
    bool swapped_left = false;
    bool swapped_right = false;

   //Recursion
    if (2 * curIndex + 1 < arrSize)   // left
        update(a, arrSize, 2 * curIndex + 1);

    if (2 * curIndex + 2 < arrSize)   // right
        update(a, arrSize, 2 * curIndex + 2);

   //Swapping
    if (2 * curIndex + 1 < arrSize)   // left
        if (a[2 * curIndex + 1]->priority < a[curIndex]->priority)
            swapped_left = swap(a[curIndex], a[2 * curIndex + 1]);

    if (2 * curIndex + 2 < arrSize)   // right
        if (a[2 * curIndex + 2]->priority < a[curIndex]->priority)
            swapped_right = swap(a[curIndex], a[2 * curIndex + 2]);

   //Update sub-trees if altered
    if (swapped_left)
        update(a, arrSize, 2 * curIndex + 1);
    else if (swapped_right)
           update(a, arrSize, 2 * curIndex + 2);
}
//int queue::size() const { return m_size; }
bool queue::swap(node* a, node* b) {
    node temp;
    temp = *a;
    *a = *b;
    *b = temp;
return true;
}