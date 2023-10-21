#include "WordList.h"
#include "Point.h"
#include <cmath>
#include <cstddef>

WordList::WordList(std::istream& stream){
        std::string word;
        while (getline(stream, word)) {
            bool isLowerCase = true;
            for (char c : word) {
                if (!islower(c)) {
                    isLowerCase = false;
                    break;
                }
            }
            if (isLowerCase) {
                mWords.push_back(word);
            }
        }
    }


float calculateDistance(const Point& p1, const Point& p2) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);

    for (const std::string& word : mWords) {
        if (word.length() == points.size()) {
            float totalScore = 0.0;
            for (size_t i = 0; i < word.length(); ++i) {
                char c = std::tolower(word[i]);
                Point keyLocation = QWERTY[c - 'a'];
                float distance = calculateDistance(points[i], keyLocation);
                float letterScore = 1.0 / (10 * pow(distance,2) + 1);
                totalScore += letterScore;
            }

            float averageScore = totalScore / static_cast<float>(word.length());

            if (averageScore >= cutoff) {
                if (heap.count() < maxcount) {
                    heap.push(word, averageScore);
                } else {
                    const Heap::Entry& minEntry = heap.top();
                    if (averageScore > minEntry.score) {
                        heap.pop();
                        heap.push(word, averageScore);
                    }
                }
            }
        }
    }

    return heap;
}
