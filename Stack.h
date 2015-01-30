/*
 * Stack.h
 *
 *  Created on: Jan 10, 2015
 *      Author: sujank
 */

#ifndef STACK_H_
#define STACK_H_

#include <cstdio>
#include <mutex>
#include <utility>

template <typename T>
class Stack
{
private:
	struct Node{
		Node* next;
		T data;
	};

	Node* top = NULL;

	std::mutex topMutex;
public:
	void Push(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;

		std::lock_guard<std::mutex> lock(topMutex);
		newNode->next = top;
		top =  newNode;
	}

	std::pair<T, bool> Pop()
	{
		std::lock_guard<std::mutex> lock(topMutex);
		Node* poppedNode = top;

		if(!poppedNode) return std::make_pair(0, false);

		top = top->next;
		return std::make_pair(poppedNode->data, true);
	}

};
#endif /* STACK_H_ */
