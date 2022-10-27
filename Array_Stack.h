#pragma once
#include<assert.h>
template<typename E> class Array_Stack
{
private:
	int Max_Size; // 最大长度
	int top; // 栈顶的下标
	E* List_Array; // 栈内的元素
public:
	/**
	 * 构造函数.
	 */
	Array_Stack(int size);

	/**
	 * 清空栈.
	 */
	void Clear();

	/**
	 * 把元素压入栈.
	 * \param Item 对应元素
	 */
	void Push(const E& item);

	/**
	 * 弹出栈顶，返回栈顶元素
	 * \return 栈顶元素
	 */
	E Pop();

	/**
	 * 返回栈顶元素的指针.
	 * \return 栈顶元素的指针
	 */
	const E& Top_Value() const;

	/**
	 * 栈内元素数量.
	 * \return 元素数量
	 */
	int Length() const;
};