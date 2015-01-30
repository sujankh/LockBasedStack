#include "Stack.h"
#include <iostream>
#include <utility>
#include <thread>

std::mutex countMutex;
int ELEM = 10000;
int totalCount = 0;

void Producer(Stack<int>& stack, int count)
{
	while(count)
	{
		stack.Push(count);
		count--;
	}
}

void Consumer(Stack<int>& stack)
{
	while(true)
	{
		std::pair<int, bool> popped = stack.Pop();

		if(popped.second)
		{
			{
				std::lock_guard<std::mutex> lock(countMutex);
				totalCount++;
				std::cout << popped.first << "\t";
			}


			if(totalCount == ELEM)
				break;
		}
	}
}

int main()
{
	Stack<int> stack;

	std::thread p0(Producer, std::ref(stack), ELEM);
	std::thread c0(Consumer, std::ref(stack));
	std::thread c1(Consumer, std::ref(stack));

	p0.join();
	c0.join();
	c1.join();

	std::cout << "\n\nDone." << std::endl;
//
//	stack.Push(5);
//	stack.Push(6);
//	stack.Push(7);
//
//	std::cout << "Hello\n";
//
//	std::cout << stack.Pop().first << "\n";
//	std::cout << stack.Pop().first << "\n";
//	std::cout << stack.Pop().first << "\n";
//	std::cout << stack.Pop().first << "\n";
//	std::cout << stack.Pop().first << "\n";
//
//	std::cout << "Test" << std::endl;



	return 0;
}
