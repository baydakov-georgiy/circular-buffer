#include <cstddef>
#include <stdexcept>

class CircularDeque
{
    int *buffer;
    size_t capacity;
    bool is_push_force;
    size_t head;
    size_t tail;
    size_t count;
public:
    explicit CircularDeque(size_t N, bool push_force = false);
    void push_front(int x);
    void push_back(int x);
    int pop_front();
    int pop_back();
    int& front();
    int& back();
    int size() const;
    bool empty() const;
    bool full() const;
    void resize(size_t new_cap);
    ~CircularDeque();
private:
    size_t nextIdx(size_t idx);
    size_t prevIdx(size_t idx);
};
