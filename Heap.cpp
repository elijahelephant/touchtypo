#include "Heap.h"
#include <iostream>



Heap::Heap(size_t max_size) {
    mCapacity = max_size;
    mCount = 0;
    mData = new Entry[max_size];
}

Heap::Heap(const Heap& other) {
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    mData = new Entry[mCapacity];
    for (size_t i = 0; i < mCount; i++) {
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other) {
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    mData = other.mData;
    other.mData = nullptr;
}

Heap::~Heap() {
    delete[] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

size_t parent(size_t index) {
    return (index - 1) / 2;
}

size_t left(size_t index) {
    return 2 * index + 1;
}

size_t right(size_t index) {
    return 2 * index + 2;
}



const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("Index out of range");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    Entry temp = mData[0];
    mData[0] = mData[mCount - 1];
    mCount--;
    size_t index = 0;
    while (index < mCount) {
        size_t l = 2 * index + 1;
        size_t r = 2 * index + 2;
        if (l >= mCount) {
            break;
        }
        if (r >= mCount) {
            if (mData[index].score > mData[l].score) {
                Entry temp = mData[index];
                mData[index] = mData[l];
                mData[l] = temp;
            }
            break;
        }
        if (mData[index].score > mData[l].score || mData[index].score > mData[r].score) {
            if (mData[l].score < mData[r].score) {
                Entry temp = mData[index];
                mData[index] = mData[l];
                mData[l] = temp;
                index = l;
            }
            else {
                Entry temp = mData[index];
                mData[index] = mData[r];
                mData[r] = temp;
                index = r;
            }
        }
        else {
            break;
        }
    }
    return temp;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry top = mData[0];
    mData[0] = Entry{ value, score };

    size_t index = 0;
    while (true) {
        size_t l = 2 * index + 1;
        size_t r = 2 * index + 2;
        size_t next = index;

        if (l < mCount && mData[l].score < mData[next].score) {
            next = l;
        }

        if (r < mCount && mData[r].score < mData[next].score) {
            next = r;
        }

        if (next != index) {
            std::swap(mData[index], mData[next]);
            index = next;
        } else {
            break;
        }
    }

    return top;
}


void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    mData[mCount].value = value;
    mData[mCount].score = score;
    size_t index = mCount;
    mCount++;
    while (index > 0) {
        size_t p = (index - 1) / 2;
        if (mData[p].score > mData[index].score) {
            Entry temp = mData[p];
            mData[p] = mData[index];
            mData[index] = temp;
            index = p;
        }
        else {
            break;
        }
    }
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}

