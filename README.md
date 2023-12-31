# Typo

This is my take on a touchscreen keyboard typo corrector. It reads in a
series of points  where the user touched the screen,  compare these with the
positions of the keys on the screen, and determine which words that the user was
most likely trying to type.

### The Heap

There's a nice visualization on Wikipedia:
<https://en.wikipedia.org/wiki/Binary_tree#Arrays>

### Percolation

A min-heap has the property that every item is smaller than its children.  So if
you add or remove items from the head, they move around.



### Functions


- `capacity()` returns the maximum capacity of the heap.
- `count()` returns the number of items in the heap.
- `lookup()` returns a reference to the entry at a given index.
  If the index is invalid, it throws a `std::out_of_range` exception.
- `pop()` removes the entry with the lowest score and returns it.
  If there are no items in the heap, it throws a `std::underflow_error`.
- `push()` function adds a new entry to the heap.  If there is no space for
  the new item, it throws a `std::overflow_error`.
- `pushpop()` is a more efficient version of a `pop()` followed by
  a `push()`.  Instead of replacing the popped entry with the last entry in the
  vector, it replaces it with the pushed entry, and then percolates that down.
  If there are no items in the heap, it throws a `std::underflow_error`.
- `top()` returns a reference to the entry with the lowest score.
  If there are no items in the heap, it throws a `std::underflow_error`.


## The Word List

The word list is  declared in `WordList.h`. It holds a list of all valid words, and owns the `correct()`
function that translates sequences of points into probable words.

- The `correct()` function  is where the important stuff happens.  It takes in a
  sequence of points; these are the points where the user touched the screen. It
  then finds all the words of the  correct length,  scores them according to the
  scoring algorithm below, and uses a `Heap` with capacity `maxcount` to collect
  the most likely words.  Words with scores lower than `cutoff` are not included
  in the output.


### Scoring

For every sequence  of touch points,  we can calculate  a similarity score for a
word of the same length. First I use the `QWERTY` map  in `Point.cpp`
to look up the location of the letters in the word on a QWERTY keyboard. Now there is
 two sequences of points:  one sequence of touch points, and one sequence of
key locations.

Then, calculate the Euclidean distance `d` between the first touch point and the
first key location.  Then convert this to a score `s` using the scoring equation
`s = 1 / (10 d² + 1)`. Repeat this for the second touch point and the second key
location, and then the third, and so on.

The score for a word is the average (mean) score of all its letters;  these will
range from near-zero to one.  The higher the score, the better the match.

### Example

  [johndoe@crib typo]$ ./helper.py | ./a.out /usr/share/dict/words
  > holster
   - 0.524: holster
   - 0.493: hoister
   - 0.483: bolster
   - 0.454: booster
   - 0.451: fooster
   - 0.451: toaster
   - 0.450: jouster
   - 0.450: rooster
  ```
