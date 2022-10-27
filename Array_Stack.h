#pragma once
#include<assert.h>
template<typename E> class Array_Stack
{
private:
	int Max_Size; // ��󳤶�
	int top; // ջ�����±�
	E* List_Array; // ջ�ڵ�Ԫ��
public:
	/**
	 * ���캯��.
	 */
	Array_Stack(int size);

	/**
	 * ���ջ.
	 */
	void Clear();

	/**
	 * ��Ԫ��ѹ��ջ.
	 * \param Item ��ӦԪ��
	 */
	void Push(const E& item);

	/**
	 * ����ջ��������ջ��Ԫ��
	 * \return ջ��Ԫ��
	 */
	E Pop();

	/**
	 * ����ջ��Ԫ�ص�ָ��.
	 * \return ջ��Ԫ�ص�ָ��
	 */
	const E& Top_Value() const;

	/**
	 * ջ��Ԫ������.
	 * \return Ԫ������
	 */
	int Length() const;
};