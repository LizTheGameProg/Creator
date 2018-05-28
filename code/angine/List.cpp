#include "List.h"

List::List()
{
	SentinelBeginNode.next = &SentinelEndNode;
	SentinelEndNode.prev = &SentinelBeginNode;
}

List::~List()
{
	Clear();
}

void List::Add(int a_value)
{
	ListNode * foo = new ListNode();
	foo->value = a_value;
	
	foo->prev = SentinelEndNode.prev;
	foo->next = &SentinelEndNode;
	SentinelEndNode.prev->next = foo;
	SentinelEndNode.prev = foo;
}

ListNode* List::Find(int a_value)
{
	ListNode* curr = SentinelBeginNode.next;
	while (curr != &SentinelEndNode && curr->value != a_value)
	{		
		curr = curr->next;
	}
	return curr;
}

void List::InsertBefore(ListNode * a_node, int a_value)
{
	ListNode * foo = new ListNode();
	foo->value = a_value;
	
	foo->next = a_node;
	foo->prev = a_node->prev;
	
	a_node->prev->next = foo;
	a_node->prev = foo;
}

void List::InsertAfter(ListNode * a_node, int a_value)
{
	ListNode * foo = new ListNode();
	foo->value = a_value;

	foo->prev = a_node;
	foo->next = a_node->next;

	a_node->next->prev = foo;
	a_node->next = foo;
}

void List::Remove(ListNode * a_node)
{
	a_node->prev->next = a_node->next;
	a_node->next->prev = a_node->prev;

	delete a_node;
}

void List::Clear()
{
	ListNode* curr = SentinelBeginNode.next;
	while (curr != &SentinelEndNode)
	{
		ListNode * foo = curr->next;
		delete curr;
		curr = foo;
	}

	SentinelBeginNode.next = &SentinelEndNode;
	SentinelEndNode.prev = &SentinelBeginNode;
}