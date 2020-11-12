# RPM-Calculator

/**********************************************************
* Project 1 (part 2): CalcYouLater
* Comp 15
* README
* By Patrick Gavazzi (pgavaz01)
*
*********************************************************/

Compile/run:
     - Compile using
            make testcalc
            make CalcYouLater
            make testStack
     - run executable with
            ./testcalc
            ./CalcYouLater
            ./testStack



Program Purpose:
    In this homework assignment, I learned how to built a Stack and used this
    knowledge to build a DatumStack I used to create a RPN calculator.
    Also, I learned how to parse RStrings and built a function that can
    read them in to use later in my RPN Calculator.



Acknowledgements:
    I used the vector class from the cpp library. Got my implementation
    plan checked by TA Sawyer Paccione.

    I used the below site to help use the stoi function (included in the
    RPNCalc class) to determine when I could convert a string to an int:
            - http://www.cplusplus.com/reference/string/stoi/

    I used the below site to help brush up on trying and catching exceptions:
            - http://www.cplusplus.com/doc/tutorial/exceptions/



Files:

    DatumStack.cpp:
        Contains the class implementation for the DatumStack class. Can create
        stack with no arguments or an array of Datum. It can
        add, access, and remove items exclusively from the front of the
        stack and also clear the entire stack. It can return
        information about the stack including its size and if it is empty.

    DatumStack.h:
        Contains the class definition for the DatumStack class. It is where
        the vector is held that I used to represent the stack.

    RPNCalc.h:
        Contains the class definition for the RPNCalc class. It is where
        the pointer to the stack is held, and also where I have a pointer to
        a vector that holds temporary datum. There is also a bool that tells
        us if the run program is over or not.

    RPNCalc.cpp:
        Contains the class implementation for the RPNCalc class. This
        calculator can preform 5 mathematical equations( +,-, *, /, %), 5
        comparison tests( ==, >, <, <=, >=), work with three different types of
        data (bools, ints, and RStrings), read input from a file, return info
        about/manipulate the stack, and execute if statements. If any problems
        with the user input occur, the program will tell the user what went
        wrong. Program should not crash.


    main.cpp:
        Contains the execution for running the RPNCalc with user input.

    testRPNCalc.cpp:
        Contains testing for the RPNCalc class. No user input needed,
        run program and then read output messages to make sure everything
        is working correctly

    testDatumStack.cpp:
        Contains testing for the DatumStack class. No user input needed,
        run program and then read output messages to make sure everything
        is working correctly

    test_commands.cyl:
        basic list of commands, used to make sure that my RPNCalc quits after
        reading in a file or for to easily call in the RString file
        function

    fact.cyl:
        provided for use, computes a factorial as long as it is called in
        the rstring file function with an int placed before it

    Test_string_commands.cyl
        list of commands that test the following queries related to strings
        - adding RStrings to the stack
        - exec
        - file
        - if

    Test_stack_commands.cyl
        list of commands that test the following queries related to the
        stack...
        - print
        - adding numbers to the stack
        - adding bools to the stack
        - adding strings to the stack
        - drop
        - swap
        - not
        - dup

    Test_math_commands.cyl
        list of commands that test the following queries related to math...
        - +
        - -
        - *
        - /
        - mod
        - >
        - <
        - >=
        - <=
        - ==



Data Structures:
    In this assignment, I used a Stack's and vectors to hold my data.

    Stack: The stack means you can only add and take off members from the
           front of the data struct. This was beneficial for the
           calculator function because when working in reverse I can easily
           keep track of the most recent item I need to account for. Using
           a stack in a situation like this was beneficial in the sense that
           I did not have to search through a whole list of elements to
           know what to get when the user inputed a query, made the
           complexity of running it very simple.

    Vectors: Used the standard Library. Used to store Datum in a stack like
             way. Made it easy to add or remove items from the front to lists,
             and it was easy to limit it's other applications by keeping it
             in the private section of my Stack class. I also used a
             vector to temporarily hold datum in my RPNCalc class so I could
             interact with datum any which way I need to when preforming
             queries.



Testing:
    - For testing DatumStack, I wrote a file that runs unit tests on each
      individual function in the class. All the user needs to do is run
      ./testStack and the program will output messages about expected
      results of functions vs actual results. The user can look at the
      messages and then decide what is working and what is not.

    - For testing RPNCalc, I did two things...

        1) There is the testRPNCalc.cpp that runs through some tests with the
           RPNCalc class. I did not test a lot of the main functions since
           they are executed when the user inputs a specific query and thoses
           results can be seen in the .cyl files. All my tests just
           run through all of the commands and make sure they are working,
           no user input needed. Outputs a message if the program is not
           working as expected *note* in order for the test file to compile
           properly and work, you need to comment out private in RPNCalc.h

        2) I provided 4 input files ( and also used one that
           was provided for us ) to run commands on my test to see if they
           worked as expected and also to diff against the demo. *note*
           these are .cyl files so to get rid of the comments, run .cylc.
           The file names are as follows and a better description of what
           is contained in each file is provided in the files section
           of the read me...
               - fact.cyl
               - Test_math_commands.cyl
               - Test_stack_commands.cyl
               - Test_string_commands.cyl
               - test_commands.cyl
