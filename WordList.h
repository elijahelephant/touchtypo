#ifndef WORDLIST_H
#define WORDLIST_H

#include <cstddef>
#include <istream>
#include <string>
#include <vector>

#include "Heap.h"
#include "Point.h"

// This is the word list class you need to implement.
// It stores a list of words, and predicts words from keypress points.


class WordList {
    std::vector<std::string> mWords;

public:
    WordList(std::istream& stream);

    Heap correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const;
};

#endif
