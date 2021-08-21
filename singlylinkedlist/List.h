#ifndef LIST_H
#define LiST_H

#include "Node.h"
#include <iostream>
#include <functional>
#include <vector>
#include <initializer_list>

template<typename T>
class List
{
	Node<T>* head = new Node<T>();
	int m_size = 0;
	
public:
	List() {}

	List(const List& list) 
	{
		extend(list);
	}

	List(const std::vector<T>& vector)
	{
		for (int i = 0; i < vector.size(); ++i)
		{
			append(vector.at(i));
		}
	}

	~List()
	{
		int currentIndex = 0;
		int size = m_size;
		while(currentIndex < size)
		{
			removeFirst();
			++currentIndex;
		}
		delete head;
	}

	List<T>& operator=(const List& list)
	{
		if (&list == this) { return *this; }
		
		int size = m_size;	
		for (int i = 0; i < size; ++i)
		{
			removeFirst();
		}
	
		Node<T>* current = list.head->next;
		while (current != nullptr)
		{
			append(current->data);
			current = current->next;
		}
		return *this;
	}
	
//adding operations

	void append(T data)
	{
		Node<T>* current = head;
		while(current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new Node<T> {data, nullptr};
		m_size++;
	}

	void appendFront(T data)
	{
		Node<T>* newNode = new Node<T> {data, head->next};
		head->next = newNode;
		m_size++;
	}

	void insert(int index, T data)
	{
		if (index < 0 || index > m_size)
		{
			throw std::out_of_range("insert(int index, T data) Index out of bounds");
		}
		
		int currentIndex = 0;
		Node<T>* current = head->next;
		Node<T>* prev = head;
		while (currentIndex < index)
		{
			current = current->next;
			prev = prev->next;
			++currentIndex;
		}
		Node<T>* newNode = new Node<T>{data, current};
		prev->next = newNode;
	}

//get operations

	T get(int index) const
	{
		Node<T>* current = head->next;
		int currentIndex = 0;
		while(currentIndex < m_size)
		{
			if (currentIndex == index)
			{
				return current->data;
			}
			current = current->next;
			++currentIndex;
		}
		throw std::out_of_range("get(int index). Index out of bounds");
	}
	
	T getFirst() const { return get(0); }
	T getLast() const { return get(m_size - 1); }

	T& at(int index)
	{
		if (index < 0 || index >= m_size)
		{
			throw std::out_of_range("at(int index) Index out of bounds");
		}
		Node<T>* current = head->next;
		int currentIndex = 0;
		while (currentIndex != index)
		{
			++currentIndex;
			current = current->next;
		}
		return current->data;
	}

	T& operator[](const int& index)
	{
		if (index < 0 || index >= m_size)
		{
			throw std::out_of_range("operator[int index] Index out of bounds");
		}
		return at(index);
	}

	List<T> getSubset(const int& start, const int& end) const
	{
		if (start >= end)
		{
			throw std::out_of_range("getSubset(int start, int end) Start index is bigger than end index");
		}
		if (start < 0 || start >= m_size)
		{
			throw std::out_of_range("getSubset(int start, int end) Start index out of bounds");
		}
		if (end <= 0 || end > m_size)
		{
			throw std::out_of_range("getSubset(int start, int end) End index out of bounds");
		}
		List<T> newList;
		Node<T>* current = head->next;
		int currentIndex = 0;
		while (currentIndex < end)
		{
			if (currentIndex >= start)
			{
				newList.append(current->data);
			}
			current = current->next;
			++currentIndex;
		}	
		return newList;
	}

//functionalities
	List<T> operator+(const List<T>& list) const
	{
		List<T> newList;
		Node<T>* current = head->next;
		while (current != nullptr)
		{
			newList.append(current->data);
			current = current->next;
		}

		current = list.head;
		while (current != nullptr)
		{
			newList.append(current->data);
			current = current->next;
		}

		return newList;
	}

	void extend(const List<T>& list)
	{
		Node<T>* current = list.head->next;
		while (current != nullptr)
		{
			append(current->data);
			current = current->next;
		}
	}

//delete operations

	void remove(int index)
	{
		if (index < 0 || index >= m_size)
		{
			throw std::out_of_range("remove(index). Index out of bounds");
		}

		Node<T> *current = head->next;
		Node<T> *prev = head;
		int currentIndex = 0;
		while (currentIndex < index)
		{
			++currentIndex;
			prev = current;
			current = current->next;
		}
		--m_size;
		prev->next = current->next;
		delete current;
	} 

	void removeFirst() { remove(0); }

	void removeLast() { remove(m_size - 1); } 

//utillities
	void printList() const 
	{
		std::cout << "[ ";
		Node<T>* current = head;
		while(current->next != nullptr)
		{
			current = current->next;
			std::cout << current->data << " ";
		}	
		std::cout << "]" << std::endl;
	}
	
	int size() const { return m_size; }

	bool contains(T data)
	{
		Node<T>* current = head->next;
		while (current != nullptr)
		{
			if (data == current->data)
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}
	bool containsBy(const std::function<bool(T)>& func)
	{
		Node<T>* current = head->next;
		while (current != nullptr)
		{
			if (func(current->data))
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}
	int count(T data)
	{
		int amount = 0;
		Node<T>* current = head->next;
		while (current != nullptr)
		{
			if (data == current->data) { ++amount; }
			current = current->next;
		}
		return amount;
	}
	
	int countBy(const std::function<bool(T)>& func)
	{
		int amount = 0;
		Node<T>* current = head->next;
		while (current != nullptr)
		{
			if (func(current->data)) { ++amount; }
			current = current->next;
		}
		return amount;
	} 

	friend std::ostream& operator<<(std::ostream& stream, const List<T> list)
	{
		stream << "[ ";
		Node<T>* current = list.head->next;
		while (current != nullptr)
		{
			stream << current->data << " ";
			current = current->next;
		}
		stream << "]\n";
		return stream;
	}
};


//summer-717
#endif
