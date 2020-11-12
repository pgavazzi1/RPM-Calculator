/*
*
*  COMP 15 Pr 1  RPNcalc
*
*  RPNcalc.h: Class definition for RPNcalc
*
*  Modified By (UTLN): pgavaz01
*           On       : 2/19/20
*
*/
#include "DatumStack.h"
#include <stdexcept>
#include <fstream>
#include <cstdlib>

using namespace std;

class RPNCalc{
    public:
        RPNCalc();
        ~RPNCalc();
        void run();

    //uncomment out to run testRPNCalc
    private:

        void get_data( istream &input );
        bool interprate_commands( string data, istream &input );

        //functions that add's elements to the stack
        bool add_to_stack( string data );
        bool number_on_stack( string data );
        void bool_on_stack( bool truth_val );
        void duplicate();
        void bool_inverse();

        //functions that deal with the stack's order or attributes
        bool stack_info( string data );
        void print();
        void clear();
        void drop_top();
        void swap();

        //integer functions
        bool operations( string data );
        void execut_math( string operation );
        int get_new_int( string operation );
        void execut_compare( string data );
        bool get_correct_bool( string data );


        //equal  for any datum
        void execut_equal();
        bool equal();


        //Rstring functions
        bool R_String( string data, istream &input );
        void add_RString( istream &input );
        string parseRString( istream &input );
        void interprate_data( string *data, int *brack_counter,
                             vector<string> *line_data );
        void complie_string( string *to_return, vector<string> *line_data,
                             int complie_size );
        void exec_string();
        void run_string_commands( istream &input );
        void read_file();
        string get_filename( istream &input );
        void exec_if();

        //helper functions
        bool get_top( int amount );
        bool int_test();
        bool bool_test();
        bool RString_test();

        //variables to help store Datum and see when the game is over
        DatumStack *storage;
        vector<Datum> *temp_datum;
        bool end_calc;



};
