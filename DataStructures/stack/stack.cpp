#include "stack.h"


int main(int argc, char const *argv[])
{
	int n;

	std::cout << "Enter n" << std::endl;
	std::cin >> n;
	TStack<char> st(n);
	int c = 0;
	char ch;

	while(c++ < n)
	{
		std::cin >> ch;
		st.Push(ch);
	}
	std::cout << std::endl;

	st.StackPrint();
	std::cout << std::endl;
	st.Pop();
	std::cout << std::endl;
	st.StackPrint();

	return 0;
}
