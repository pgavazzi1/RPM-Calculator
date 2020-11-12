/*
 *
 *  COMP 15 Pr 1  RPNcalc
 *
 *  DatumStack.h
 *  Modified By (UTLN): pgavaz01
 *           On       : 2/14/20
 *
 */
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <string>
 #include "Datum.h"

 using namespace std;

 class DatumStack{
    public:

        DatumStack();
        DatumStack(Datum *array, int size);
        void push(Datum element);
        bool isEmpty();
        void clear();
        int size();
        Datum top();
        void pop();

    private:
      vector<Datum> stack;
};
