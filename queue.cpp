#include "queue.h"

node::node(){}
node::node(int d, int p) : data(d), priority(p){}

queue::queue() = default;
queue::queue(int size) : m_MAXSIZE(size) {
    m_front = m_rear = -1;
    arr = new node*[m_MAXSIZE];
    for(int i = 0; i < m_MAXSIZE; i++)
        arr[i] = new node;
}
queue::~queue(){
    for(int i = 0; i < m_MAXSIZE; i++) {
        delete arr[i];
        arr[i] = NULL;
    }
    delete[] arr;
    arr = NULL;
}
queue::queue(const queue& objB) {
    if(this != &objB) {
        *arr = *(objB.arr);
        m_MAXSIZE = objB.maxSize();
        m_front = objB.front();
        m_rear = objB.rear();
        m_size = objB.size();
    }
}
queue& queue::operator = (const queue& objB) {
    if(this != &objB) {
        *arr = *(objB.arr);
        m_MAXSIZE = objB.maxSize();
        m_front = objB.front();
        m_rear = objB.rear();
        m_size = objB.size();
    }
    return *this;
}
int queue::operator [](int i) const {
    return arr[i]->data;
}

int queue::dequeue() {
    if (isempty())
        return -1;

    node* temp = arr[m_front];  // preserve
    arr[m_front]->data = -1;    // reset
    arr[m_front]->priority = -1;

    if (m_front == m_rear)
        m_front = m_rear = -1;
    else if (m_front == m_MAXSIZE - 1)
        m_front = 0;
    else
        m_front++;
    m_size--;

    return temp->data;
}
void queue::enqueue(int newData) {
    if (isfull()) // Do nothing
        return;
    else if (m_front == -1) { // First element only
        m_front = m_rear = 0;
        arr[m_rear]->data = newData;
    }
    else if (m_rear == m_MAXSIZE - 1) { //Reset rear
        m_rear = 0;
        arr[m_rear]->data = newData;
    } else {
        m_rear++;
        arr[m_rear]->data = newData;
    }
    m_size++;
}
void queue::heapify(node** a, int arrSize, int curIndex) { //heapifies min heap
    bool swapped_left = false;
    bool swapped_right = false;

   //Recursion
    if (2 * curIndex + 1 < arrSize)   // left
        heapify(a, arrSize, 2 * curIndex + 1);

    if (2 * curIndex + 2 < arrSize)   // right
        heapify(a, arrSize, 2 * curIndex + 2);

   //Swapping
    if (2 * curIndex + 1 < arrSize)   // left
        if (a[2 * curIndex + 1]->priority < a[curIndex]->priority)
            swapped_left = swap(a[curIndex], a[2 * curIndex + 1]);

    if (2 * curIndex + 2 < arrSize)   // right
        if (a[2 * curIndex + 2]->priority < a[curIndex]->priority)
            swapped_right = swap(a[curIndex], a[2 * curIndex + 2]);

   //Update sub-trees if altered
    if (swapped_left)
        heapify(a, arrSize, 2 * curIndex + 1);
    else if (swapped_right)
           heapify(a, arrSize, 2 * curIndex + 2);
}

bool queue::isempty() const { return m_front == -1; }
bool queue::isfull() const { 
    if(m_front == 0 && m_rear == m_MAXSIZE - 1 || m_rear == m_front - 1)
        return true;
    return false;
}
int queue::size() const { return m_size; }
int queue::peek() const {
    if (isempty())
        return -1;
    return arr[m_front]->data;
}
int queue::tail() const {
    if (isempty())
        return -1;
    return arr[m_rear]->data;
}
int queue::front() const { return m_front; }
int queue::rear() const { return m_rear; }
int queue::curSize() const { return m_size; }
int queue::maxSize() const { return m_MAXSIZE; }

bool queue::swap(node* a, node* b) {
    node temp;
    temp = *a;
    *a = *b;
    *b = temp;
return true;
}