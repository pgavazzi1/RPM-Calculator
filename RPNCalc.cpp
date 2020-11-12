/*
*
*  COMP 15 Pr 1  RPNcalc
*
*  RPNcalc.cpp: Class implementation for RPNcalc
*
*  Modified By (UTLN): pgavaz01
*           On       : 2/14/20
*
*/
#include <iostream>
#include "RPNCalc.h"


//function name: RPNCalc construcor
//Parameters: none
//Returns: nothing
//Does: Allocates data and sets variables to user later in the program
RPNCalc::RPNCalc(){
    storage = new DatumStack;
    temp_datum = new vector<Datum>;
    end_calc = false;
}

//function name: RPNCalc destructor
//Parameters: none
//Returns: nothing
//Does: delets all user allocated data made during program
RPNCalc::~RPNCalc(){
    delete storage;
    delete temp_datum;
}

//function name: run
//Parameters: none
//Returns: nothing
//Does: Calls function that runs calculator with input from cin, prints out
//      a message when the calculator is finished.
void RPNCalc::run(){
    get_data( cin );
    cerr << "Thank you for using CalcYouLater." << endl;
}

//function name: get_data
//Parameters: an input stream to get commands from
//Returns: nothing
//Does: Gets data from an input stream nd calls functions that check each
//      input to see if we should execute comands on the string... runs
//      till the end of the input stream or until the user quits.
void RPNCalc::get_data( istream &input ){

    //Get whole line of info from user and initiat string stream with
    //the line
    string info, data;

    //interprate the data from the string stream
    while ( !input.eof() ) {

        input >> data;

        if ( input.eof() ) {
            break;
        }

        if ( !interprate_commands( data, input ) ) {
            end_calc = true;
        }

        if ( end_calc ) {
            return;
        }
    }
}

//function name: interprate_commands
//Parameters: a string with the current data we are executing, and an input
//            stream to pass to more functions that may need it
//Returns: false if the user wants to quit the program, true otherwise
//Does: Checks input against some commands, or calls functions to
//      check against comands. Outputs message if command was not recognized
bool RPNCalc::interprate_commands( string data, istream &input ){

    //check to see if the user has typed in recognized inputs, then send
    //to functions to test other inputs
    if ( data == "quit" ) {
        return false;
    //just return if the user types in nothing
    } else if ( data == "" ) {
        return true;
    } else if ( add_to_stack( data) or stack_info(data) or
         operations( data ) or R_String( data, input )) {
        temp_datum->clear();
        return true;
    } else {
        cerr << data << ":  unimplemented\n";
    }

    return true;
}

//function name: add_to_stack
//Parameters: a string with the current data we are executing.
//Returns: true if the data matches with the correct command, false if none
//         of the commands match data
//Does: Calls the functions to execute comands that relate to adding
//      datum to the stack, returns true regardless of what happens in each of
//      those functions.
bool RPNCalc::add_to_stack(string data){

    if ( number_on_stack( data ) ) {
        return true;
    }

    //check to see if the user has entered a correct bool or not
    if ( data == "#t" ) {
        bool_on_stack( true );
        return true;
    } else if ( data == "#f" ) {
        bool_on_stack( false );
        return true;
    } else if ( data == "#" ) {
        cerr << "Error: invalid boolean #" << endl;
        return true;
    //see if user has entered in sepcial commands
    } else if ( data == "not" ) {
        bool_inverse();
        return true;
    } else if ( data == "dup" ) {
        duplicate();
        return true;
    }

    return false;
}

//function name: number_on_stack
//Parameters: an string to check if it is an integer or not
//Returns: true if we successful convert the sting to an int, false if the
//         string could not be converted into an int
//Does: Tries to convert a string to an int using the STOI function included
//      in the string class. Catches errors if the string is too big of an
//      int or it is not an int.
bool RPNCalc::number_on_stack(string data){

    try {
        std::string::size_type sz;
        int new_int = stoi(data, &sz);

        //Make sure the string we entered and the number of converted letters
        // match
        if ( sz == data.length() ) {
            Datum to_add(new_int);
            storage->push( to_add );
            return true;
        }

    } catch ( const std::out_of_range& e ) {
        cerr << "Error: stoi" << endl;
        return true;
    } catch ( const std::invalid_argument& ia ) {
        //do nothing cause we want to keep checking data againts other things
    }

    return false;
}

//function name: bool_on_stack
//Parameters: an bool with the type of datam bool we want to create
//Returns: nothing
//Does:  Creats a bool based off the truth value, adds to the top of the
//       stack
void RPNCalc::bool_on_stack(bool truth_val){
    if ( truth_val == true ) {
        Datum new_datum( true );
        storage->push( new_datum );
    } else {
        Datum new_datum( false );
        storage->push( new_datum );
    }
}

//function name: duplicate
//Parameters: none
//Returns: nothing
//Does:  creates a duplicate of the first datum on the stack and adds it to
//       the top of the stack. Returns early if the stack is empty
void RPNCalc::duplicate(){
    if ( storage->isEmpty() ) {
        cerr << "Error: empty_stack" << endl;
        return;
    } else {
        Datum dupliacte( storage->top() );
        storage->push( dupliacte );
    }
}

//function name: bool_inverse
//Parameters: none
//Returns: nothing
//Does:  creates a datum bool with the reverse of the top datum bool on
//       the stack, then deletes the original bool. Returns early if the
//       stack is empty or if the top datam is a bool.
void RPNCalc::bool_inverse(){
    if ( storage->isEmpty() ) {
        cerr << "Error: empty_stack" << endl;
        return;
    } else if ( !storage->top().isBool() ) {
        cerr << "Error: datum_not_bool" << endl;
        return;
    }

    if ( storage->top().getBool() ) {
        storage->pop();
        Datum new_false( false );
        storage->push( new_false );
    } else {
        storage->pop();
        Datum new_true( true );
        storage->push( new_true );
    }
}

//function name: stack_info
//Parameters: a string with the current data we are executing.
//Returns: true if the data matches with the correct command, false if none
//         of the commands match data
//Does: Calls the functions to execute comands that relate to info about
//      the stack, returns true regardless of what happens in each of
//      those functions.
bool RPNCalc::stack_info(string data){

    if ( data == "print" ) {
        print();
        return true;
    } else if ( data == "drop" ) {
        drop_top();
        return true;
    } else if ( data == "clear" ) {
        clear();
        return true;
    } else if ( data == "swap" ) {
        swap();
        return true;
    }

    return false;
}

//function name: drop_top
//Parameters: none
//Returns: nothing
//Does:  gets rid of the first datum on the stack. Returns early if the
//       stack is empty
void RPNCalc::drop_top(){
    if ( storage->isEmpty() ) {
        cerr << "Error: empty_stack" << endl;
        return;
    }
    storage->pop();
}

//function name: print
//Parameters: none
//Returns: nothing
//Does:  prints the top datum on the stack. Returns early if the
//       stack is empty
void RPNCalc::print(){
    if ( storage->isEmpty() ) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    cout << storage->top().toString() << endl;
}

//function name: clear
//Parameters: none
//Returns: nothing
//Does:  clears all the datum in the stack
void RPNCalc::clear(){
    storage->clear();
}

//function name: swap
//Parameters: none
//Returns: nothing
//Does: Takes the top two datam off the stack and swaps their position
void RPNCalc::swap(){
    if ( !get_top( 2 ) ){
        return;
    }

    storage->push( temp_datum->at( 0 ) );
    storage->push( temp_datum->at( 1 ) );
}

//function name: operations
//Parameters: a string with the current data we are executing.
//Returns: true if the data matches with the correct command, false if none
//         of the commands match data
//Does: Calls the functions to execute comands that relate to doing math
//      equations with the stack, returns true regardless of what happens
//      in each of those functions.
bool RPNCalc::operations(string data){

    if ( data == "+" or data == "-" or data == "/" or data == "*"
        or data == "mod" ){
        execut_math( data );
        temp_datum->clear();
        return true;

    } else if ( data == "==" ) {
        execut_equal();
        temp_datum->clear();
        return true;

    } else if ( data == "<" or data == ">" or data == "<=" or data == ">=" ) {
        execut_compare( data );
        temp_datum->clear();
        return true;
    }

    //clear the temporary stack
    temp_datum->clear();
    return false;
}

//function name: execut_math
//Parameters: a string with the type of opperation we want to preform
//Returns: nothing
//Does: Gets top two Datum off the stack and preforms equation of the user's
//      choosing on the datum and adds the result to the stack. returns early
//      if there is not enough datum on the stack or if the datum are
//      not string.
void RPNCalc::execut_math(string operation){
    // check for dividing by zero.
    if ( operation == "/" or operation == "mod" ) {
        if ( storage->top().toString() == "0" ) {
            cerr << "Error: division by 0.\n";
            return;
        }
    }

    //get top two items from stack, if there are not enough items and make
    //sure everything is an int.
    if ( !get_top( 2 ) ){
        return;
    } else if  ( !int_test() ) {
        cerr << "Error: datum_not_int" << endl;
        return;
    }

    //if no errors, get new int
    int new_int = get_new_int( operation );
    Datum new_datum( new_int );
    storage->push( new_int );
    return;
}

//function name: get_new_int
//Parameters: a string with the type of opperation we want to preform
//Returns: the new integer value
//Does: Takes the two datum we have a preforms an operation on the of the
//      users chosing
int RPNCalc::get_new_int( string operation ){

    if ( operation == "+" ) {
        return temp_datum->at( 0 ).getInt() + temp_datum->at( 1 ).getInt();

    } else if ( operation == "-" ) {
        return temp_datum->at( 1 ).getInt() - temp_datum->at( 0 ).getInt();

    } else if ( operation == "*" ) {
        return temp_datum->at( 0 ).getInt() * temp_datum->at( 1 ).getInt();

    } else if ( operation == "/" ) {
        return temp_datum->at( 1 ).getInt() / temp_datum->at( 0 ).getInt();

    } else if ( operation == "mod" ) {
        return temp_datum->at( 1 ).getInt() % temp_datum->at( 0 ).getInt();
    }

    return 0;
}

//function name: execut_equal
//Parameters: none
//Returns: nothing
//Does: Calls functions to test if two datum are equal, then calls other
//      functions to add a datum with a bool on the stack. Returns earlier
//      if there are not enough datum on the stack
void RPNCalc::execut_equal(){
    if ( !get_top( 2 ) ) {
        return;
    }

    if ( equal() ) {
        bool_on_stack( true );
        return;
    }

    bool_on_stack( false );
    return;
}

//function name: equal
//Parameters: none
//Returns: nothing
//Does: Calls functions to test if two datum are equal, then calls other
//      functions to add a datum with a bool on the stack. Returns earlier
//      if there are not enough datum on the stack
bool RPNCalc::equal(){

    //compare the two datum if they are the same type
    if ( int_test() ) {
        if ( temp_datum->at( 1 ).getInt() == temp_datum->at( 0 ).getInt() ) {
            return true;
        }

    } else if ( bool_test() ) {
        if ( temp_datum->at( 1 ).getBool() == temp_datum->at( 0 ).getBool() ) {
            return true;
        }

    } else if ( RString_test() ) {
        if ( temp_datum->at( 1 ).getRString() ==
             temp_datum->at( 0 ).getRString() ) {
            return true;
        }
    }

    return false;
}


//function name: execut_compare
//Parameters: a string with the operation we are supposed to preform
//Returns: nothing
//Does: Calls functions to compare two datum, then calls other
//      functions to add a datum with a bool on the stack. Returns earlier
//      if there are not enough datum on the stack
void RPNCalc::execut_compare( string data ){
    //get top two items from stack, if there are not enough items and make
    //sure everything is an int
    if ( !get_top( 2 ) ){
        return;
    } else if  ( !int_test() ) {
        cerr << "Error: datum_not_int" << endl;
        return;
    }

    bool bool_to_add = get_correct_bool( data );


    //add the bool to the stack that we want
    bool_on_stack( bool_to_add );
    return;
}

//function name: get_correct_bool
//Parameters: a string with the operation we are supposed to preform
//Returns: a bool with the valuse we want to add to the stack
//Does: Executes a command to compare two ints baised off of the user's input
bool RPNCalc::get_correct_bool( string data ){

    if ( data == "<") {
        if ( temp_datum->at( 1 ).getInt() < temp_datum->at( 0 ).getInt() ) {
            return true;
        }
    } else if ( data == ">" ) {
        if ( temp_datum->at( 1 ).getInt() > temp_datum->at( 0 ).getInt() ) {
            return true;
        }
    } else if ( data == ">=" ) {
        if ( temp_datum->at( 1 ).getInt() > temp_datum->at( 0 ).getInt()
             or equal() ) {
            return true;
        }
    } else if ( data == "<=" ) {
        if ( temp_datum->at( 1 ).getInt() < temp_datum->at( 0 ).getInt()
             or equal() ) {
            return true;
        }
    }

    //return false if none of the commands end up trues
    return false;
}


//function name: R_String
//Parameters: takes in an input stream to pass to the functions and a
///           string with the current data we are executing.
//Returns: true if the data matches with the correct command, false if none
//         of the commands match data
//Does: Calls the functions to ececute comands that relate to strings,
//      returns true regardless of what happens in each of those functions.
bool RPNCalc::R_String( string data, istream &input){

    //check to see if the user has entered a correct bool or not
    if ( data == "{" ) {
        add_RString( input );
        return true;

    } else if ( data == "exec" ) {
        exec_string();
        return true;

    } else if ( data == "file" ) {
        read_file();
        return true;

    } else if ( data == "if" ) {
        exec_if();
        return true;
    }

    return false;
}

//function name: add_RString
//Parameters: takes in an input stream to pass to the parser function.
//Returns: nothing
//Does: Calls the paser and gets a string to add to the stack, adds to the
//      stack only if the RString was formated correctly.
void RPNCalc::add_RString( istream &input ){

    string to_add = parseRString( input );

    if ( to_add != "" ) {
        Datum new_rstring( to_add );
        storage->push( new_rstring );
    }
}

//function name: parseRString
//Parameters: takes in an input stream
//Returns: A string with either an RString or an empty string;
//Does: Gets a new peice of data from the input stream. Calls functions to
//      interprate what the input stream and and complie the data into
//      an RString to return if the brackets line up.
string RPNCalc::parseRString( istream &input ){
    //variables to use
    string data;
    string to_return = "";
    int brack_counter = 1;
    vector<string> line_data;

    //keep geting user input until the user has typed in the correct amount
    //of bracket pairs.
    while ( brack_counter != 0 ) {
          while ( !input.fail() ) {
              input >> data;

              interprate_data( &data, &brack_counter, &line_data );

              if (brack_counter == 0) {
                  to_return += "{ ";
                  //size minus one cause we have a extra space at the end
                  //of our string name we do not want
                  int vec_size = line_data.size() - 1;
                  complie_string( &to_return, &line_data, vec_size);
                  break;
              }
          }
    }

    return to_return;
}

//function name: interprate_data
//Parameters: takes in pointers to a string of data, an int with the number
//            of brackets, and a vector with the strings to turn into an
//            RString
//Returns: Nothing
//Does: Adds or takes away to the brack counter depending on the data, and
//      adds to the vector if we are collecting for the RString
void RPNCalc::interprate_data(string *data, int *brack_counter,
                     vector<string> *line_data){
    if ( *data == "{" ) {
        *brack_counter += 1;
    }

    //add to the stack if we do not have correct amount of braces
    if ( *brack_counter > 0 ) {
        line_data->push_back(*data);
        line_data->push_back(" ");
    }

    if ( *data == "}" ) {
        *brack_counter -= 1;
    }
}

//function name: complie_string
//Parameters: takes in pointers to a string to return and a vector with the
//            strings to turn into an RString, and an int that tells us
//            how much of the vetor to compile
//Returns: Nothing
//Does: Loops through the vector and adds all of the individual strings into
//      one complete RString.
void RPNCalc::complie_string( string *to_return, vector<string> *line_data,
                              int complie_size){

    //add up all of the elements in vector into one long string
    for (int i = 0; i < complie_size; i++) {
        *to_return += line_data->front();
        line_data->erase(line_data->begin());
    }
}

//function name: exec_string
//Parameters: nothing
//Returns: nothing
//Does: Gets an RString, gets ride of the starting and closing brackets, and
//      executes the statments inside. Quits if there are not enough elements
//      or the wrong type on the stack.
void RPNCalc::exec_string(){

    //error check
    if ( !get_top( 1 ) ){
        return;
    } else if  (!RString_test() ) {
        cerr << "Error: cannot execute non rstring\n";
        return;
    }

    //Get whole RSTRING and initiat string stream
    istringstream string_stream;
    string_stream.str( temp_datum->at( 0 ).getRString() );

    run_string_commands( string_stream );
}

//function name: run_string_commands
//Parameters: takes in an input stream to a string stream
//Returns: nothing
//Does: Gets an RString, executes the statments inside the brackets.
//      Quits if there are not enough elements
//      or the wrong type on the stack.
void RPNCalc::run_string_commands( istream &input ){

    //variables to use
    int brack_counter = 1;
    string data;
    input >> data;

    //interprate the data from the string stream
    while (!input.eof()) {
        input >> data;

        if ( data == "{") {
            brack_counter += 1;
        } else if ( data == "}" ) {
            brack_counter -= 1;
            continue;
        }

        if ( brack_counter == 0) {
            break;
        } else if ( !interprate_commands( data , input ) ) {
            end_calc = true;
            break;
        }
    }
}

//function name: read_file
//Parameters: nothing
//Returns: nothing
//Does: Calls function that gets a file name form an r sting, reads in from
//      the file and Executes the file's commands.
//      Quits if there are not enough elements or the wrong type on the stack.
void RPNCalc::read_file(){
    //error check
    if ( !get_top( 1 ) ){
        return;
    } else if  (!RString_test() ) {
        cerr << "Error: cannot execute non rstring\n";
        return;
    }

    //open file to get data from
    istringstream string_stream;
    string_stream.str( temp_datum->at( 0 ).getRString() );
    string filename = get_filename( string_stream );

    ifstream instream;
    instream.open ( filename );

    if ( instream.fail() ) {
        cerr << "Unable to read " << filename << "\n";
        return;
    }

    get_data( instream );

    instream.close();
}

//function name: read_file
//Parameters: an input stream
//Returns: nothing
//Does: Gets an RString, executes the statments inside the brackets.
//      Quits if there are not enough elements
//      or the wrong type on the stack.
string RPNCalc::get_filename( istream &input ){

    //variables to use and get rid of first bracket
    int brack_counter = 1;
    string data, filename;
    vector<string> line_data;
    input >> data;

    //interprate the data from the string stream
    while (!input.eof()) {
        input >> data;

        if ( data == "{" ) {
            brack_counter += 1;
        } else if ( data == "}" ) {
            brack_counter -= 1;
        }

        if ( brack_counter > 0 ) {
            line_data.push_back(data);
        }
    }
    //complie and return file name
    int vec_size = line_data.size();
    complie_string( &filename, &line_data, vec_size);
    return filename;
}

//function name: exec_if
//Parameters: nothing
//Returns: nothing
//Does: Gets and three datum, one bool and two Rstrings. Executes on of the
//      Rstrings depending on the truth value of the the bool. Quits if
//      there are not enough elements or the wrong type on the stack
void RPNCalc::exec_if(){
    //error check
    if ( !get_top( 3 ) ){
        return;
    } else if ( !temp_datum->back().isBool() ) {
        cerr << "Error: expected boolean in if test\n";
        return;
    }

    bool truth_value = temp_datum->back().getBool();
    temp_datum->erase(  temp_datum->begin() + 2 );

    if  (!RString_test() ) {
        cerr << "Error: expected rstring in if branch\n";
        return;
    }

    //add the string we want back on top of the stack to be executeds
    if ( truth_value ) {
        storage->push( temp_datum->at(1) );
    } else {
        storage->push( temp_datum->at(0) );
    }

    //clear temp_datum and run commands in the string
    temp_datum->clear();
    exec_string();
}

//function name: get_top
//Parameters: takes in integer with amount of datum to get
//Returns: true if there are enough ints to get, false if there are not
//         enough datum in the stack
//Does: Removes datum from the stack and puts them into a temporary datum
//      vector to use for operations
bool RPNCalc::get_top( int amount ){
    //get Datum from top of array
    for (int i = 0; i < amount; i++) {
        if (storage->isEmpty()) {
            cerr << "Error: empty_stack" << endl;
            return false;
        }
        temp_datum->push_back( storage->top() );
        storage->pop();
    }

    return true;
}

//function name: int_test
//Parameters: nothing
//Returns: true if every Datum in temp_datum contains an integr, false if
//         there is a datum storing a different type
//Does: Should iterate only through the list's length, calls a function in
//      the datum class to find out if it is an int or not
bool RPNCalc::int_test(){

    int vec_size = temp_datum->size();

    for (int i = 0; i < vec_size; i++) {
        if ( !temp_datum->at(i).isInt() ) {
            return false;
        }
    }

    return true;
}

//function name: bool_test
//Parameters: nothing
//Returns: true if every Datum in temp_datum contains an bool, false if
//         there is a datum storing a different type
//Does: Should iterate only through the list's length, calls a function in
//      the datum class to find out if it is an bool or not
bool RPNCalc::bool_test(){

    int vec_size = temp_datum->size();

    for (int i = 0; i < vec_size; i++) {
        if ( !temp_datum->at(i).isBool() ) {
            return false;
        }
    }

    return true;
}

//function name: RString_test
//Parameters: nothing
//Returns: true if every Datum in temp_datum contains an RString, false if
//         there is a datum storing a different type
//Does: Should iterate only through the list's length, calls a function in
//      the datum class to find out if it is an RString or not
bool RPNCalc::RString_test(){

    int vec_size = temp_datum->size();

    for (int i = 0; i < vec_size; i++) {
        if ( !temp_datum->at(i).isRString() ) {
            return false;
        }
    }

    return true;
}
