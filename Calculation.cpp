#include "Calculation.h"
#include "Array_Stack.cpp"

bool Is_Number(char c)
{
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool Is_Operation(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/') return true;
	return false;
}

bool Check_Arithmetic_Expressions(std::string s)
{
	size_t len = s.length();
	int pos = 0;
	int Now = 0; // ������������������
	while (pos < len)
	{
		// ����
		if (Is_Number(s[pos]))
		{
			int flag = 0;
			if (s[pos] == '0' && pos + 1 < len && Is_Number(s[pos + 1])) return 0; // ǰ�� 0 �Ǵ�����ʽ
			while (pos < len)
			{
				if (Is_Number(s[pos]))
				{
					if (flag == 1) flag = 2;
					pos++;
				}
				else if (s[pos] == '.')
				{
					if (flag == 0) flag = 1;
					else return 0; // ���С�����Ǵ�����ʽ
					pos++;
				}
				else break;
			}
			if (flag == 1) return 0; // ֻ��С����û��С��λ�Ǵ�����ʽ
			Now = 1;
		}
		// �����
		else if (Is_Operation(s[pos]))
		{
			if (Now == 0 && s[pos] != '-') return 0;
			Now = 0;
			pos++;
		}
		// ������
		else if (s[pos] == '(')
		{
			if (Now == 1) return 0;
			Array_Stack<int> AStack = Array_Stack<int>(1e5);
			AStack.Push(pos++);
			while (true)
			{
				if (AStack.Length() == 0) break; // ����ƥ�������
				else if (pos >= len) return 0;// ���ʽ������Ҳû��������ƥ�����
				else if (s[pos] == '(') AStack.Push(pos);
				else if (s[pos] == ')')
				{
					if (AStack.Length() == 1)
					{
						int begin = AStack.Pop() + 1, end = pos;
						std::string temp = s.substr(begin, end - begin);
						if (Check_Arithmetic_Expressions(temp) == 0) return 0;// ������ߵ��Ǹ�������ʽ
					}
					else AStack.Pop();
				}
				pos++;
			}
			Now = 1;
		}
		// �������
		else return 0;
	}
	if (Now == 0) return 0;
	return 1;
}

int Level(char c)
{
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
}

double Calculation(double Num_A, double Num_B, char Operator)
{
	if (Operator == '+') return Num_A + Num_B;
	if (Operator == '-') return Num_A - Num_B;
	if (Operator == '*') return Num_A * Num_B;
	if (Operator == '/')
	{
		assert(Num_B != 0, "����Ϊ0");
		return Num_A / Num_B;
	}
}

std::string Arithmetic_Expressions_To_Postfix(std::string s)
{
	size_t len = s.length();
	int pos = 0;
	Array_Stack<char> Postfix_Stack = Array_Stack<char>(1e5);
	Array_Stack<double> Value_Stack = Array_Stack<double>(1e5);
	std::string Postfix;
	while (pos < len)
	{
		int Now;
		// ����
		if (Is_Number(s[pos]))
		{
			int flag = 0;
			double Times = 1;
			double Item = 0;
			int Start = pos;
			while (pos < len)
			{
				if (Is_Number(s[pos]))
				{
					if (flag == 1)
					{
						Times *= 10;
						Item += (s[pos] - '0') / Times;
					}
					else
						Item = Item * 10 + (s[pos] - '0');
					pos++;
				}
				else if (s[pos] == '.')
				{
					flag = 1;
					pos++;
				}
				else break;
			}
			Value_Stack.Push(Item);
			Postfix += s.substr(Start, pos - Start) + " ";
		}
		// �����
		else if (Is_Operation(s[pos]))
		{
			if (pos == 0 || s[pos - 1] == '(')
			{
				pos++;
				int flag = 0;
				double Times = 1;
				double Item = 0;
				int Start = pos;
				while (pos < len)
				{
					if (Is_Number(s[pos]))
					{
						if (flag == 1)
						{
							Times *= 10;
							Item += (s[pos] - '0') / Times;
						}
						else
							Item = Item * 10 + (s[pos] - '0');
						pos++;
					}
					else if (s[pos] == '.')
					{
						flag = 1;
						pos++;
					}
					else break;
				}
				Item *= -1;
				Value_Stack.Push(Item);
				Postfix += s.substr(Start, pos - Start) + " ";
			}
			else
			{
				char Item = s[pos++];
				char Temp;
				while (Postfix_Stack.Length() != 0 && (Temp = Postfix_Stack.Top_Value()) != '(' && Level(Item) <= Level(Temp))
				{
					Postfix += Temp;
					Postfix += ' ';
					Postfix_Stack.Pop();

					double Num_A, Num_B, Num_Ans;
					Num_B = Value_Stack.Pop();
					Num_A = Value_Stack.Pop();
					Num_Ans = Calculation(Num_A, Num_B, Temp);
					Value_Stack.Push(Num_Ans);
				}
				Postfix_Stack.Push(Item);
			}
		}
		// ������
		else if (s[pos] == '(')
		{
			char Item = s[pos++];
			Postfix_Stack.Push(Item);
		}
		else if (s[pos] == ')')
		{
			char Temp;
			while (Postfix_Stack.Length() != 0 && (Temp = Postfix_Stack.Pop()) != '(')
			{
				Postfix += Temp;
				Postfix += ' ';
				double Num_A, Num_B, Num_Ans;
				Num_B = Value_Stack.Pop();
				Num_A = Value_Stack.Pop();
				Num_Ans = Calculation(Num_A, Num_B, Temp);
				Value_Stack.Push(Num_Ans);
			}
			pos++;
		}
	}
	while (Postfix_Stack.Length())
	{
		char Temp;
		Postfix += (Temp = Postfix_Stack.Pop());
		Postfix += ' ';
		double Num_A, Num_B, Num_Ans;
		Num_B = Value_Stack.Pop();
		Num_A = Value_Stack.Pop();
		Num_Ans = Calculation(Num_A, Num_B, Temp);
		Value_Stack.Push(Num_Ans);
	}
	return Postfix;
}


std::string Calculation_Arithmetic_Expressions(std::string s)
{
	size_t len = s.length();
	int pos = 0;
	Array_Stack<char> Postfix_Stack = Array_Stack<char>(1e5);
	Array_Stack<double> Value_Stack = Array_Stack<double>(1e5);
	while (pos < len)
	{
		// ����
		if (Is_Number(s[pos]))
		{
			int flag = 0;
			double Times = 1;
			double Item = 0;

			while (pos < len)
			{
				if (Is_Number(s[pos]))
				{
					if (flag == 1)
					{
						Times *= 10;
						Item += (s[pos] - '0') / Times;
					}
					else
						Item = Item * 10 + (s[pos] - '0');
					pos++;
				}
				else if (s[pos] == '.')
				{
					flag = 1;
					pos++;
				}
				else break;
			}
			Value_Stack.Push(Item);
		}
		// �����
		else if (Is_Operation(s[pos]))
		{
			if (pos == 0 || s[pos - 1] == '(')
			{
				pos++;
				int flag = 0;
				double Times = 1;
				double Item = 0;
				while (pos < len)
				{
					if (Is_Number(s[pos]))
					{
						if (flag == 1)
						{
							Times *= 10;
							Item += (s[pos] - '0') / Times;
						}
						else
							Item = Item * 10 + (s[pos] - '0');
						pos++;
					}
					else if (s[pos] == '.')
					{
						flag = 1;
						pos++;
					}
					else break;
				}
				Item *= -1;
				Value_Stack.Push(Item);
			}
			else
			{
				char Item = s[pos++];
				char Temp;
				while (Postfix_Stack.Length() != 0 && (Temp = Postfix_Stack.Top_Value()) != '(' && Level(Item) <= Level(Temp))
				{
					std::cout << Temp << ' ';
					Postfix_Stack.Pop();

					double Num_A, Num_B, Num_Ans;
					Num_B = Value_Stack.Pop();
					Num_A = Value_Stack.Pop();
					Num_Ans = Calculation(Num_A, Num_B, Temp);
					Value_Stack.Push(Num_Ans);
				}
				Postfix_Stack.Push(Item);
			}
		}
		// ������
		else if (s[pos] == '(')
		{
			char Item = s[pos++];
			Postfix_Stack.Push(Item);
		}
		else if (s[pos] == ')')
		{
			char Temp;
			while (Postfix_Stack.Length() != 0 && (Temp = Postfix_Stack.Pop()) != '(')
			{
				double Num_A, Num_B, Num_Ans;
				Num_B = Value_Stack.Pop();
				Num_A = Value_Stack.Pop();
				Num_Ans = Calculation(Num_A, Num_B, Temp);
				Value_Stack.Push(Num_Ans);
			}
			pos++;
		}
	}
	while (Postfix_Stack.Length())
	{
		char Temp;
		Temp = Postfix_Stack.Pop();
		double Num_A, Num_B, Num_Ans;
		Num_B = Value_Stack.Pop();
		Num_A = Value_Stack.Pop();
		Num_Ans = Calculation(Num_A, Num_B, Temp);
		Value_Stack.Push(Num_Ans);
	}
	return std::to_string(Value_Stack.Pop());
}