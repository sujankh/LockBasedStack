CXX = g++

all: LockBasedStack

LockBasedStack: main.cpp Stack.h
	$(CXX) -ggdb -O2 -std=c++11 -pthread main.cpp -o LockBasedStack
	
clean:
	rm -f LockBasedStack
