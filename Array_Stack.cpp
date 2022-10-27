#include "Array_Stack.h"
template<typename E>
Array_Stack<E>::Array_Stack(int Size)
{
	Max_Size = Size;
	top = 0;
	List_Array = new E[Size];
}

template<typename E>
void Array_Stack<E>::Clear()
{
	top = 0;
}

template<typename E>
void Array_Stack<E>::Push(const E& Item)
{
	assert(top != Max_Size, "Stack is full");
	List_Array[top++] = Item;
}

template<typename E>
E Array_Stack<E>::Pop()
{
	assert(top != 0, "Stack is empty");
	return List_Array[--top];
}

template<typename E>
const E& Array_Stack<E>::Top_Value() const
{
	assert(top != 0, "Stack is empty");
	return List_Array[top - 1];
}

template<typename E>
int Array_Stack<E>::Length() const
{
	return top;
}