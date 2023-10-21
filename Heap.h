#ifndef HEAP_H
#define HEAP_H

#include <cstddef>
#include <string>

// It's a binary min-heap that stores its entries in an array.

class Heap {
public:
    struct Entry {
        std::string value;
        float       score;
    };

private:
    Entry* mData;
    size_t mCapacity;
    size_t mCount;

public:
    Heap(size_t capacity);
    Heap(const Heap& other);
    Heap(Heap&& other);
    ~Heap();

    size_t       capacity() const;
    size_t       count() const;
    const Entry& lookup(size_t index) const;
    Entry        pop();
    Entry        pushpop(const std::string& value, float score);
    void         push(const std::string& value, float score);
    const Entry& top() const;
};

#endif
