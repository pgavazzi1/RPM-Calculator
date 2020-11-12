/*
*
*  COMP 15 Pr 1  RPNcalc
*
*  testDatumStack.cpp
*  Modified By (UTLN): pgavaz01
*           On       : 2/14/20
*
*/
#include <iostream>
#include "DatumStack.h"

void test_push(DatumStack *test);
void test_size(DatumStack *test);
void test_isEmpty(DatumStack *test);
void test_clear(DatumStack test);
void clear_check(DatumStack test);
void test_top(DatumStack *test);
void test_pop(DatumStack test);


int main() {
    cout << endl << "Hello, let us test the DatumStack!" << endl << endl;

    DatumStack test;

    //run tests
    test_push(&test);
    test_size(&test);
    test_isEmpty(&test);
    test_clear(test);
    test_top(&test);
    test_pop(test);

    cout << endl;
}

//function name: test_push
//Parameters: A pointer to a DatumStack to use for testing
//Returns: nothing
//Does: Test's the DatumStack push feature by adding Datum to the front
//      of the stack and comparing expected vs actual outputs.
void test_push(DatumStack *test){
    cout << "First, let us test 'push'" << endl;

    cout << "    Adding int 3 to the front... ";
    Datum data_1(3);
    test->push(data_1);
    cout << "And what is at the front?: '" << test->top().toString();
    cout << "' With a stack size of 1: '" << test->size() << "'";
    if (test->top().getInt() == 3 && test->size() == 1) {
        cout << "... yes everything is correct" << endl;
    } else {
        cout << "... no, something is wrong" << endl;
    }

    cout << "    Adding bool false to the front... ";
    Datum data_2(false);
    test->push(data_2);
    cout << "And what is at the front?: '" << test->top().toString();
    cout << "' With stack size of 2: '" << test->size() << "'";
    if (test->top().getBool() == false && test->size() == 2) {
        cout << "... yes everything is correct" << endl;
    } else {
        cout << "... no, something is wrong" << endl;
    }

    cout << "    Adding srting 'hey dude' to the front... ";
    Datum data_3("hey dude");
    test->push(data_3);
    cout << "And what is at the front?: '" << test->top().toString();
    cout << "' With stack size of 3: '" << test->size() << "'";
    if (test->top().getRString() == "hey dude" && test->size() == 3) {
        cout << "... yes everything is correct" << endl;
    } else {
        cout << "... no, something is wrong" << endl;
    }

}

//function name: test_size
//Parameters: A pointer to a DatumStack to use for testing
//Returns: nothing
//Does: Test's the DatumStack size feature calling it on empty and non-
//      empty stacks and comparing expected vs actual results
void test_size(DatumStack *test){
    cout << endl << "Next, let us test 'sizes'" << endl;

    cout << "    expected size is '3' and the stack has a size of: '";
    cout << test->size() << "'";
    if (test->size() == 3) {
        cout << "... which is correct" << endl;
    } else {
        cout << "... which is not correct" << endl;
    }

    cout << "    expected size is '0' and the stack has a size of: '";
    DatumStack empty_test;
    cout << empty_test.size() << "'";
    if (empty_test.size() == 0) {
        cout << "... which is correct" << endl;
    } else {
        cout << "... which is not correct" << endl;
    }
}

//function name: test_isEmpty
//Parameters: A pointer to a DatumStack to use for testing
//Returns: nothing
//Does: Test's the DatumStack isEmpty feature calling it on empty and non-
//      empty stacks and comparing expected vs actual results
void test_isEmpty(DatumStack *test){
    cout << endl << "Next, let us test 'isEmpty'" << endl;

    cout << "    Testing on a non-empty DatumStack which has a size of: '";
    cout << test->size() << "' and should return false... ";
    if (test->isEmpty()) {
        cout << "returns true!" << endl;
    } else {
        cout << "returns false!" << endl;
    }

    cout << "    Testing on an empty DatumStack which has a size of: '";
    DatumStack empty_test;
    cout << empty_test.size() << "' and should return true... ";
    if (empty_test.isEmpty()) {
        cout << "returns true!" << endl;
    } else {
        cout << "returns false!" << endl;
    }
}

//function name: test_clear
//Parameters: A copy of a DatumStack to use for testing
//Returns: nothing
//Does: Test's the DatumStack clear feature by calling other functions
//      with an empty or non-empty stack.
void test_clear(DatumStack test){
    cout << endl << "Next, let us test 'clear'" << endl;
    clear_check(test);

    //double check calling clear does not do anything funky with an
    //already empty function
    DatumStack empty_test;
    clear_check(empty_test);
}

//function name: clear_check
//Parameters: A copy of a DatumStack to use for testing
//Returns: nothing
//Does: Test's if a DatumStack is actually clear after we try and call clean
//      it out.
void clear_check(DatumStack test){

    //check what it is before we clear
    cout << "    Before clear: Size = '" << test.size() << "' and isEmpty says";
    if (test.isEmpty()) {
        cout << " 'Nothing in here!'... ";
    } else {
        cout << " 'Still Datum left!'... ";
    }

    //Clear the DatumStack and see what it holds.
    test.clear();
    cout << "After clear: Size = '" << test.size() << "' and isEmpty says";
    if (test.isEmpty()) {
        cout << " 'Nothing in here! Evering works fine!' " << endl;
    } else {
        cout << " 'Whoops, still Datum left!' " << endl;
    }
}

//function name: test_top
//Parameters: A pointer to a DatumStack to use for testing
//Returns: nothing
//Does: Test's the DatumStack top feature by retreving the top of the data
//      stack and then comapring expected vs actual results
void test_top(DatumStack *test){
    cout << endl << "Next, let us test 'top'" << endl;

    cout << "    Expected Datum at front: string 'hey dude'... and what is ";
    cout << "actually at the front?: string '" << test->top().toString();
    if ( test->top().isRString() && test->top().getRString() == "hey dude" ) {
        cout << "'... Everything works fine!" << endl;
    } else {
        cout << "'... Whoops something went wrong :(" << endl;
    }

    //does it get the front after we add new data
    Datum new_data(467);
    test->push(new_data);
    cout << "    NEW expected Datum at front: int '467'... and what is ";
    cout << "actually at the front?: int '" << test->top().toString();
    if ( test->top().isInt() && test->top().getInt() == 467 ) {
        cout << "'... Everything works fine!" << endl;
    } else {
        cout << "'... Whoops something went wrong :(" << endl;
    }

    //crashes tests because string is empty
    // DatumStack empty_test;
    // cout << "    Expected Datum at front: nothing ... and what is ";
    // cout << "actually at the front?: '" << empty_test.top().toString();
}

//function name: test_pop
//Parameters: A copy of a DatumStack to use for testing
//Returns: nothing
//Does: Test's the DatumStack pop feature by poping the top of the Stack
//       and then comapring expected vs actual results
void test_pop(DatumStack test){
    cout << endl << "Next, let us test 'pop'" << endl;

    cout << "    Before pop: Size = '" << test.size() << "' and top is: ";
    cout << test.top().toString() << "... ";
    test.pop();
    cout << " After pop we expect top: 'hey dude' with size '3' and top";
    cout << " really is: '" << test.top().toString() << "' with size: '";
    cout << test.size();
    if (test.top().getRString() == "hey dude" && test.size() == 3) {
        cout << "' ... everything is correct!" << endl;
    } else {
        cout << "' ... Something went wrong :(" << endl;
    }

    cout << "    Before Double pop: Size = '" << test.size();
    cout << "' and top is: "<<  test.top().toString() << "... ";
    test.pop();
    test.pop();
    cout << " After pop we expect top: '3' with size '1' and top";
    cout << " really is: '" << test.top().toString() << "' with size: '";
    cout << test.size();
    if (test.top().getInt() == 3 && test.size() == 1) {
        cout << "' ... everything is correct!" << endl;
    } else {
        cout << "' ... Something went wrong :(" << endl;
    }


    //crashes tests because string is empty
    // DatumStack empty_test;
    //cout << "    Before pop: Size = '" << empty_test.size() << "' and top is: ";
    //cout << empty_test.top().toString();
    //empty_test.pop();
}
