#pragma once
#ifndef GENERIC_STACK
#define GENERIC_STACK 1
#include <utility>
namespace generic_stack
{
    typedef unsigned long long usize;
    typedef signed long long isize;
    template <class T>
    class Stack {
        usize capacity;
        isize top;
        bool is_slice_ref = false;
        T * array;

        public:
        Stack(); // this constructor creates stack with array uninitialized, used for creation of slice
        Stack(usize _max_size); // constructor declaring the maximum size 
        Stack(const Stack & stack); // copy constructor
        Stack(Stack && stack); // move constructor
        ~Stack(); // Destructor, deletes only when not a ref, resets pointer to nullptr

        usize len(); // gets filled length of the stack
        usize max_size(); // gets capacity of the stack
        bool is_full(); // checks if the stack is full (t)
        bool is_empty(); // checks if the stack is empty

        bool push(T value); // push the value onto the stack, if it's full, returns non-zero i.e. true
        std::pair<T, bool> pop(); // pop the top value from stack and validate with a zero (false) on second data of the pair
        std::pair<T&, bool> peek(); // returns the reference to the value on the top of the stack, 

        std::pair<Stack, bool> slice_upto(usize len); // slices the stack to the specified depth, allows modifications upto it, and not below
        bool is_sliced();
        const T * indexable_list(); // gives something to index all the data stored for debugging purposes
    };
}
#endif