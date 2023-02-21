#include "stack.hpp"
#include <iostream>
using usize = generic_stack::usize;
template <class T>
std::ostream & operator << (std::ostream & o, const generic_stack::Stack<T> & stack) {
    o << "This is a " 
    << (stack.is_sliced() ? "sliced" : "whole" )
    << " stack.\n";
    o << "Capacity = " << stack.max_size() << '\n';
    o << "Top = " << (stack.len() - 1) << '\n';
    o << "Sliced = " << stack.is_sliced() << '\n';
    o << "Datas stored : ";
    usize i = stack.len();
    while(i) {
        o << stack.indexable_list()[--i];
    }
    o << '\n';
    return o;
}

int main() {
    generic_stack::Stack<int> stack(10);
    return 0;
}