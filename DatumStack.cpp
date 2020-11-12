/*
*
*  COMP 15 Pr 1  RPNcalc
*
*  DatumStack.cpp: Holds a combination of Datum in a string
*
*  Modified By (UTLN): pgavaz01
*           On       : 2/14/20
*
*/
#include <iostream>
#include "DatumStack.h"

DatumStack::DatumStack(){
}


DatumStack::DatumStack(Datum *array, int size){
    for (int i = 0; i < size; i++) {
        push(array[i]);
    }
}

//function name: push
//Parameters: A Datum to add to the stack
//Returns: nothing
//Does: Adds Datum to the front of a stack
void DatumStack::push(Datum element){
   stack.insert(stack.begin(), element);
}

//function name: isEmpty
//Parameters: nothing
//Returns: a bool
//Does: returns true if the stack contains no Datum, returns false otherwise
bool  DatumStack::isEmpty(){
    if (stack.size() == 0) {
        return true;
    }
    return false;
}

//function name: clear
//Parameters: nothing
//Returns: nothing
//Does: get's rid of all Datum in the stack
void  DatumStack::clear(){
    stack.clear();
}

//function name: size
//Parameters: nothing
//Returns: int with the stack's size
//Does: returns the amount of Datum in the stack
int  DatumStack::size(){
    return stack.size();
}

//function name: top
//Parameters: nothing
//Returns: a Datum
//Does: returns the first Datum in the stack. Throw's an error is the stack
//      is empty
Datum  DatumStack::top(){
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }

    return stack.front();
}

//function name: pop
//Parameters: nothing
//Returns: nothing
//Does: Gets rid of the first Datum in the stack. Throw's an error is
//      the stack is empty
void  DatumStack::pop(){
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }

    stack.erase(stack.begin());
}
