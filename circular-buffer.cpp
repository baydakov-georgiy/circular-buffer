#include "circular-buffer.hpp"

CircularDeque::CircularDeque(size_t N, bool push_force):
capacity(N), is_push_force(push_force), head(0), tail(0), count(0)
{
    buffer = new int[N];
}

CircularDeque::~CircularDeque()
{
    delete[] buffer;
}

size_t CircularDeque::nextIdx(size_t idx)
{
    return (idx + 1) % capacity;
}

size_t CircularDeque::prevIdx(size_t idx)
{
    return (idx + capacity - 1) % capacity;
}

void CircularDeque::push_front(int x)
{
    if (full()) {
        if (!is_push_force) throw std::overflow_error("Deque is full");
        head = prevIdx(head);
        buffer[head] = x;
        tail = prevIdx(tail);
    } else {
        head = prevIdx(head);
        buffer[head] = x;
        count++;
    }
}

void CircularDeque::push_back(int x)
{
    if (full()) {
        if (!is_push_force) throw std::overflow_error("Deque is full");
        buffer[tail] = x;
        tail = nextIdx(tail);
        head = nextIdx(head);
    } else {
        buffer[tail] = x;
        tail = nextIdx(tail);
        count++;
    }
}

int CircularDeque::pop_front()
{
    if (empty()) throw std::underflow_error("Deque is empty");
    int val = buffer[head];
    head = nextIdx(head);
    count--;
    return val;
}

int CircularDeque::pop_back()
{
    if (empty()) throw std::underflow_error("Deque is empty");
    tail = prevIdx(tail);
    count--;
    return buffer[tail];
}

int& CircularDeque::front() {
    return buffer[head];
}

int& CircularDeque::back() {
    return buffer[prevIdx(tail)];
}

int CircularDeque::size() const
{
    return count;
}

bool CircularDeque::empty() const
{
    return count == 0;
}

bool CircularDeque::full() const
{
    return count == capacity;
}

void CircularDeque::resize(size_t new_cap)
{
    if (new_cap == 0) throw std::invalid_argument("Capacity must be positive");
    int *new_buffer = new int[new_cap];
    size_t new_count = std::min(count, new_cap);
    for (int i = 0; i < new_count; i++) {
        new_buffer[i] = buffer[(head + i) % capacity];
    }
    delete[] buffer;
    buffer = new_buffer;
    capacity = new_cap;
    head = 0;
    tail = new_count % new_cap;
    count = new_count;
}
