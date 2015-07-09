#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>
#include <iomanip>

template <class T>
class TList
{
public:
	TList();
	~TList();

	void Push_to_front(const T& value);
	void Push_to_end(const T& value);
	void Push(const T& value, int pos);

	void Erase(const T& value);

	void Clear();

	void PrintList();


private:
	int lsize;
	struct TNode
	{
		TNode* next;
		T val;
	};
	TNode* _head;
	TNode* _tail;	
};

template<class T>
TList<T>::TList()
{
	_tail = NULL;
	_head = NULL;

	lsize = 0;
}

template<class T>
TList<T>::~TList()
{
	while(_head)
	{
		_tail = _head->next;
		delete _head;
		_head = _tail;
	}
}

template<class T>
void TList<T>::Push_to_front(const T& value)
{
	TNode* tmp;
	try
	{
		tmp = new TNode;
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "No memory" << std::endl;
		std::exit(0);
	}

	tmp->val = value;
	tmp->next = _head;
	_head = tmp;
	

	lsize++;
}

template<class T>
void TList<T>::Push_to_end(const T& value)
{
	TNode* tmp;
	

	try
	{
		tmp = new TNode;
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << "No memory" << std::endl;
		std::exit(0);
	}

	tmp->val = value;

	if(_head == NULL)
	{
		_head = tmp;
		_tail = tmp;
		return;
	}

	_tail->next = tmp;
	_tail = tmp;

	lsize++;
}

template<class T>
void TList<T>::Push(const T& value, int pos)
{
	if (pos < 0)
	{
		std::cerr << "Incorrect number of the position";
		return;
	}

	if (_head == NULL)
	{
		Push_to_front(value);
		lsize++;
		return;
	}

	TNode* node = this->_head;

	for(int i = 1; i < pos && node->next; ++i)
	{
		node = node->next;
	}

	TNode* tmp;

	try
	{
		tmp = new TNode;
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << "No memory";
		std::exit(0);
	}

	tmp->val = value;

	tmp->next = node->next;
	node->next = tmp;


	lsize++;
}

template<class T>
void TList<T>::Erase(const T& value)
{
	if (_head == NULL)
	{
		std::cerr << "List is empty";
		return;
	}

	TNode* _prev;
	try
	{
		_prev = new TNode;
	}
	catch(std::bad_alloc& e)
	{
		std::cerr << "No memory";
		std::exit(0);
	}

	for(TNode* ptr = _head; ptr != NULL; ptr = ptr->next)
	{
		if(ptr->val == value)
		{
			_prev->next = ptr->next;
			delete ptr;
			break;
		}

		_prev = ptr;
	}

	lsize--;
}

template<class T>
void TList<T>::Clear()
{
	if(_head == NULL)
	{
		std::cerr << "Stack is empty";
	}
	while(_head != NULL)
	{
		TNode* tmp = _head;
		_head = _head->next;
		delete tmp;
	}

	lsize = 0;

}

template<class T>
void TList<T>::PrintList()
{
	if(_head == NULL)
	{
		std::cerr << "Stack is empty";
		return;
	}
	for(TNode* tmp = _head; tmp != NULL; tmp = tmp->next)
	{
		std::cout << "|" << std::setw(3) << tmp->val << std::setw(3) << "|" << std::endl;
	}
}
#endif

