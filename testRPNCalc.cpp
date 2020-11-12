/*
*
*  COMP 15 Pr 1  RPNcalc
*
*  tetsRPNCalc.cpp: Runs tests on the RPN calc class. Functions must be moved
*                   from private to public in RPNCalc.h in order for the
*                   tests to work. No user input required required beyond that,
*                   sit back amd watch to see if the tests work or not
*
*  Modified By (UTLN): pgavaz01
*           On       : 2/14/20
*
*/
#include <iostream>
#include "RPNCalc.h"

// //functions that add's elements to the stack


void test_get_new_int( RPNCalc *tets_Calc );
void test_get_correct_bool( RPNCalc *tets_Calc );
void test_get_top( RPNCalc *tets_Calc );
void test_int_test( RPNCalc *tets_Calc );
void test_bool_test( RPNCalc *tets_Calc );


int main(){
      cerr <<  endl << "hello! Lets test the RPNCalc class! Hope you";
      cerr << " remembered to move functions from private to public";
      cerr << " or this will not work :( " << endl << endl;

      RPNCalc tets_Calc;

      test_get_new_int( &tets_Calc );
      test_get_correct_bool( &tets_Calc );
      test_get_top( &tets_Calc );

      cerr << "All done testing, have a great day!" << endl << endl;

}

//function name: test_get_new_int
//Parameters: a pointer to an RPNCalc to run tests on
//Returns: nothing
//Does: Adds ints to the stack and tests if the calculator preforms math
//      operations correctly
void test_get_new_int( RPNCalc *tets_Calc ){
  cerr << "Now let us test get_new_int" << endl;

  cerr << "   using 6 and 2 for every equation" << endl;
  Datum int_2( 2 );
  Datum int_6( 6 );
  tets_Calc->temp_datum->push_back(int_2);
  tets_Calc->temp_datum->push_back(int_6);

  cerr << "   Addition: should return 8, and does it work?  We got: ";
  cerr <<  tets_Calc->get_new_int( "+" );
  if ( tets_Calc->get_new_int( "+" ) == 8 ) {
      cerr << "...   yay it worked!" << endl;
  } else {
      cerr << "...   something went wrong" << endl;
  }

  cerr << "   Subtract: should return 4, and does it work?  We got: ";
  cerr <<  tets_Calc->get_new_int( "-" );
  if ( tets_Calc->get_new_int( "-" ) == 4 ) {
      cerr << "...   yay it worked!" << endl;
  } else {
      cerr << "...   something went wrong" << endl;
  }

  cerr << "   Multiplication: should return 12, and does it work?  We got: ";
  cerr <<  tets_Calc->get_new_int( "*" );
  if ( tets_Calc->get_new_int( "*" ) == 12 ) {
      cerr << "...   yay it worked!" << endl;
  } else {
      cerr << "...   something went wrong" << endl;
  }

  cerr << "   Division: should return 3, and does it work?  We got: ";
  cerr <<  tets_Calc->get_new_int( "/" );
  if ( tets_Calc->get_new_int( "/" ) == 3 ) {
      cerr << "...   yay it worked!" << endl;
  } else {
      cerr << "...   something went wrong" << endl;
  }
  tets_Calc->temp_datum->clear();
  cerr << endl;

  cerr << endl;
}

//function name: test_get_new_int
//Parameters: a pointer to an RPNCalc to run tests on
//Returns: nothing
//Does: Adds ints to the stack and tests if the calculator preforms
//      comparing operations correctly
void test_get_correct_bool( RPNCalc *tets_Calc ){
  cerr << "Now let us test get_correct_bool" << endl;

  cerr << "   using 6 and 2:" << endl;
  Datum int_2( 2 );
  Datum int_6( 6 );
  tets_Calc->temp_datum->push_back(int_2);
  tets_Calc->temp_datum->push_back(int_6);

  cerr << "   Is 6 > 2 We got: ";
  if ( tets_Calc->get_correct_bool( ">" ) == true ) {
      cerr << "#t...   yay it worked!" << endl;
  } else {
      cerr << "#f...   something went wrong" << endl;
  }

  cerr << "   Is 6 < 2 We got: ";
  if ( tets_Calc->get_correct_bool( "<" ) == false ) {
      cerr << "#f...   yay it worked!" << endl;
  } else {
      cerr << "#t...   something went wrong" << endl;
  }

  cerr << "   using 6 and 6:" << endl;
  tets_Calc->temp_datum->clear();
  tets_Calc->temp_datum->push_back(int_6);
  tets_Calc->temp_datum->push_back(int_6);

  cerr << "   Is 6 >= 6 We got: ";
  if ( tets_Calc->get_correct_bool( ">=" ) == true ) {
      cerr << "#t...   yay it worked!" << endl;
  } else {
      cerr << "#f...   something went wrong" << endl;
  }

  cerr << "   Is 6 <= 6 We got: ";
  if ( tets_Calc->get_correct_bool( ">=" ) == true ) {
      cerr << "#t...   yay it worked!" << endl;
  } else {
      cerr << "#f...   something went wrong" << endl;
  }

  tets_Calc->temp_datum->clear();
  cerr << endl;
}

//function name: test_get_new_int
//Parameters: a pointer to an RPNCalc to run tests on
//Returns: nothing
//Does: Adds ints and bools to the stack, tests if the function stores
//      datam from the stack in the temporary vector correctly. One commented
//      out test that produces error.
void test_get_top( RPNCalc *tets_Calc ){
  cerr << "Now let us test get_top" << endl;

  cerr << "   Now adding two ints onto the stack... did get_top work? ";
  tets_Calc->add_to_stack( "3" );
  tets_Calc->add_to_stack( "7" );
  if ( tets_Calc->get_top( 2 ) ) {
      cerr << "yay it worked!" << endl;
  } else {
      cerr << "something went wrong" << endl;
  }
  tets_Calc->temp_datum->clear();

  cerr << "   Now adding four bools onto the stack... did get_top work? ";
  tets_Calc->add_to_stack( "#t" );
  tets_Calc->add_to_stack( "#t" );
  tets_Calc->add_to_stack( "#t" );
  tets_Calc->add_to_stack( "#t" );
  if ( tets_Calc->get_top( 4 ) ) {
      cerr << "yay it worked!" << endl;
  } else {
      cerr << "something went wrong" << endl;
  }
  tets_Calc->temp_datum->clear();


  //should produce an error since nothing is in the stack;
  //tets_Calc->get_top( 4 );

  cerr << endl;
}
