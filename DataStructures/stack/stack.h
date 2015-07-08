#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <iomanip>
#include <cstdlib>

template<class T>
class TStack
{
public:

	TStack(int);
	~TStack();
	void Push(const T& value);
	void Pop();
	int Size();
	const T& GetElementById(int num);
	void StackPrint();
	const T& operator [](int i) const;
	
private:

	int st_size;
	T* _sptr;
	int _cur;


};

template<class T>
TStack<T>::TStack(int n) : st_size(n)
{
	try
	{
		_sptr = new T[n];
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "No memory" << std::endl;
		std::exit(0);
	}


	_cur = 0;
}

template<class T>
TStack<T>::~TStack()
{
	delete [] _sptr;
}

template<class T>
void TStack<T>::Push(const T& value)
{
	if ( _cur < st_size)
	{
		_sptr[_cur++] = value;
	}
	else
	{
		std::cerr << "Stack overflow" << std::endl;
	}
}

template<class T>
void TStack<T>::Pop()
{
	if (_cur > 0)
	{	
		_sptr[--_cur];

	}
	else
	{
		std::cerr << "Stack is empty" << std::endl;
	}
}

template<class T>
int TStack<T>::Size()
{
	return st_size;
}

template<class T>
const T& TStack<T>::GetElementById(int number)
{
	if (number < _cur)
	{
		return _sptr[_cur - number];
	}
}
template<class T>
void TStack<T>::StackPrint()
{	
	std::cout << "Stack:" << std::endl;
	for (int i = _cur - 1; i >= 0; i--)
	{
		//std::cout << st_size << std::endl;
		std::cout << "|" << std::setw(3) << _sptr[i] << std::setw(3) <<  "|" << std::endl;
	}
}

template<class T>
const T& TStack<T>::operator [](int i) const
{
	return _sptr[i];
}
#endif