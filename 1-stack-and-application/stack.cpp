#include "stack.hpp"
using namespace generic_stack;

// using namespace Stack;

template <class T> // constructor declaring maximum size
Stack<T>::Stack(usize _capacity) : capacity(_capacity), top(-1) {
    array = new T[_capacity];
}

template <class T> // copy constructor
Stack<T>::Stack(const Stack<T> & stack) : 
    capacity(stack.capacity),
    top(stack.top)
{
    array = new T[stack.max_size];
    for (int i = 0; i<=stack.top; ++i) {
        array[i] = stack.array[i];
    }
}

template <class T> // move constructor
Stack<T>::Stack(Stack<T> && stack) :
    capacity(stack.capacity),
    top(stack.top),
    is_slice_ref(is_slice_ref),
    array(array)
{
    // invalidate the original stack
    top = -1;
    array = nullptr;
}

template <class T> // destructor
Stack<T>::~Stack() {
    if (!is_slice_ref) {
        delete array;
    }
}

template <class T> 
usize Stack<T>::len() {
    return top+1;
}

template <class T>
usize Stack<T>::max_size() {
    return capacity;
}

template <class T>
bool Stack<T>::is_full() {
    return len() == max_size();
}

template <class T>
bool Stack<T>::is_empty() {
    return len() == 0;
}


template <class T>
bool Stack<T>::push(T value) {
    auto filled = is_full();
    if (filled) {
        return filled;
    }
    array[++top] = std::move(value);
    return false;
}

template <class T>
std::pair<T, bool> Stack<T>::pop() {
    std::pair<T, bool> result;
    auto empty = is_empty();
    if (empty) {
        result.second = true;
        return std::move(result);
    }
    result.second = false;
    result.first = array[top--];
    return std::move(result);
}

template <class T>
std::pair<T&, bool> Stack<T>::peek() {
    std::pair<T, bool> result;
    auto empty = is_empty();
    if (empty) {
        result.second = true;
        return std::move(result);
    }
    result.second = false;
    result.first = array[top];
    return std::move(result);
}


template <class T>
std::pair<Stack<T>, bool> Stack<T>::slice_upto(usize len) {
    isize base_shift = this->len() - len; // i.e. (total length) - (slice length)

    std::pair<Stack<T>, bool> result;
    auto impossible = base_shift < 0;
    if (impossible) {
        result.second = true;
        return std::move(result);
    }

    Stack<T> reference_stack;
    reference_stack.capacity = capacity - base_shift;
    reference_stack.top = top - base_shift; 
    reference_stack.is_ref = true;
    reference_stack.array = array + base_shift;

    result.second = false;
}

template <class T>
bool Stack<T>::is_sliced() {
    return is_slice_ref;
}

template <class T>
const T * Stack<T>::indexable_list() {
    return array;
}