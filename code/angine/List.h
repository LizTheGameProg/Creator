#pragma once
#include "ListNode.h"

class List
{
public:
	List();
	~List();

	void Add(int value);
	ListNode* Find(int value);
	void InsertBefore(ListNode * node, int value);
	void InsertAfter(ListNode * node, int value);
	void Remove(ListNode * node);
	void Clear();

	ListNode SentinelBeginNode;
	ListNode SentinelEndNode;

	ListNode* begin() { return SentinelBeginNode.next; }
	ListNode* end() { return SentinelEndNode.prev; }
};