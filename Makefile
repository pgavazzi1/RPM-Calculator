###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  patrick gavazzi (pgavaz01)

CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3

INCLUDES = $(shell echo *.h)
EXECS    = MetroSim

testStack: testDatumStack.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} $^ -o $@

parser: parser.o
	${CXX} ${CXXFLAGS} $^ -o $@

testcalc: testRPNCalc.o RPNCalc.o DatumStack.o Datum.o
	${CXX} ${CXXFLAGS} $^ -o $@

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o
	${CXX} ${CXXFLAGS} $^ -o $@

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c -o $@ $<


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
