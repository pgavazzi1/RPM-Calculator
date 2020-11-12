/*
*
*  COMP 15 Pr 1  RPNcalc
*
*  parser.cpp: Takes in a line of data and orginizes it into an RString
*              if conditions are correct.
*
*  Modified By (UTLN): pgavaz01
*           On       : 2/14/20
*
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void run_with_user();
void run_with_file(string filename);
string parseRString(istream &input);
void interprate_data(string *data, int *brack_counter,
                     vector<string> *line_data);
void complie_string(string *to_return, vector<string> *line_data);


int main(int argc, char *argv[]) {

    if (argc == 1) {
        run_with_user();
    } else if (argc == 2) {
        run_with_file( argv[1] );
    } else {
        cout << "Too many arguments... bye :(" << endl;
    }
}

//function name: run_with_user
//Parameters: nothing
//Returns: nothing
//Does: Gets a new line of data from the user, and sends it to be parsed.
//      out puts string if data is an RSrting
void run_with_user(){

    istringstream string_stream;
    string info;

    while ( !cin.fail() ) {
        getline(cin, info);

        //run till user types stop
        if (info == "stop") {
            break;
        }

        //send string stream to parser and output RString if it is correct
        string_stream.str(info);
        string compile = parseRString(string_stream);
        if ( compile != "") {
            cout << compile << endl;
        }
        string_stream.clear();
    }
}

//function name: run_with_file
//Parameters: nothing
//Returns: nothing
//Does: Gets a new line of data from the file, and sends it to be parsed.
//      out puts string if data is an RSrting
void run_with_file(string filename){

    istringstream string_stream;
    string info;

    //open file to get data from
    ifstream instream;
    instream.open ( filename );

    //run till end of file
    while ( !instream.fail() ) {
        getline(instream, info);

        //send string stream to parser and output RString if it is correct
        string_stream.str(info);
        string compile = parseRString(string_stream);
        if ( compile != "") {
            cout << compile << endl;
        }
        string_stream.clear();
    }
}


//function name: parseRString
//Parameters: takes in an input stream
//Returns: A string with either an RString or an empty string;
//Does: Gets a new peice of data from the input stream. Calls functions to
//      interprate what the input stream and and complie the data into
//      an RString to return if the brackets line up.
string parseRString(istream &input){

    //variables to use
    string data;
    string to_return = "";
    int brack_counter = 0;
    vector<string> line_data;

    while (!input.eof()) {
        input >> data;
        interprate_data( &data, &brack_counter, &line_data);


        if (brack_counter == 0) {
            complie_string( &to_return, &line_data);
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
void interprate_data(string *data, int *brack_counter,
                     vector<string> *line_data){
    if ( *data == "{" ) {
        *brack_counter += 1;
    }

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
//            strings to turn into an RString
//Returns: Nothing
//Does: Loops through the vector and adds all of the individual strings into
//      one complete RString.
void complie_string(string *to_return, vector<string> *line_data){
    //get size of vector
    int vec_size = line_data->size();

    //add up all of the elements in vector into one long string
    for (int i = 0; i < vec_size; i++) {
        *to_return += line_data->front();
        line_data->erase(line_data->begin());
    }
}
