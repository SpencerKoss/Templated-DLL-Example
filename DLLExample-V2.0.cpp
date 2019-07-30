//This program DLL uses templates in order to use different data types. In my example in main it uses integers, however it can handle different
//types of data as well. This DLL shows the example of operator overloading, inserting data at the front, and back of the list, 
//reversing the list, finding a particular datum in the list, unlinking the desired datum, and removing said desired datum, and finally clearing
//the DLL 
#include "pch.h"
#include <iostream>
using namespace std;

template<typename AnyType>
class Doublely_Linked_list{
class Node {
public:
	AnyType data;
	Node* next;
	Node* prev;

	
	Node() :next(nullptr), prev(nullptr) {

	}

	Node(AnyType d) : data(d), next(nullptr), prev(nullptr) {

	}

	~Node() {};

	};//End of Node
Node* head = nullptr;
Node* tail = nullptr;

public:
	friend ostream& operator <<(ostream& output, Doublely_Linked_list<AnyType> obj){
			Node* tempPtr = obj.head;
			output << "Printing the list:  \n";

			while (tempPtr) {
				output << tempPtr->data << " ";
				tempPtr = tempPtr->next;
			}//End of While

			cout << endl;
			return output;
		}//end of overloaded <<


	//Function Prototypes
	void insertAtHead(AnyType const&);
	void insertAtTail(AnyType const&);
	Node* find_node_by_data(AnyType const& information)const;
	void unlinkData(Doublely_Linked_list<AnyType>::Node* n);
	void remove(AnyType info);
	bool is_list_empty();
	void reverse();
	void clear_List();

	

}; //End of DLL 

template<typename AnyType>
void Doublely_Linked_list<AnyType>::insertAtHead(AnyType const& information) {
	//Allocating dynamic memory on the heap
	Node* current = new Node(information);
	
	if (head == nullptr) {
		head = current;
		tail = current;
	}
	else {
		head->prev = current;
		current->next = head;
		head = current;
	}

}

template<typename AnyType>
void Doublely_Linked_list<AnyType>::insertAtTail(AnyType const& information) {
	//Allocating dynamic memory on the heap
	Node* current = new Node(information);

	if (head == nullptr) {
		head = current;
	}
	else {
		tail->next = current;
		current->prev = tail;
	}
	tail = current;
}


template<typename AnyType>
typename Doublely_Linked_list<AnyType>::Node* Doublely_Linked_list<AnyType>::find_node_by_data(AnyType const& information)const {
	Node* current = head;

	while (current) {
		if (current->data == information) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}


template<typename AnyType>
void Doublely_Linked_list<AnyType>::unlinkData(Doublely_Linked_list<AnyType>::Node* n) {
	if (n->prev) {
		n->prev->next = n->next;
	}
	else {
		head = n->next;
		head->prev = nullptr;
	}

	if (n->next) {
		n->next->prev = n->prev;
	}
	else {
		tail = n->prev;
		tail->next = nullptr;
	}
}


template<typename AnyType>
void Doublely_Linked_list<AnyType>::remove(AnyType info) {
	Node* target_node = find_node_by_data(info);

	if (target_node) {
		unlinkData(target_node);
		delete target_node;
	}
}



template<typename AnyType>
bool Doublely_Linked_list<AnyType>::is_list_empty(){
	return head == nullptr && tail == nullptr;
}

template<typename AnyType>
void Doublely_Linked_list<AnyType>::reverse() {
	Node* current = tail;
	Node* future_next = nullptr;
	while (current) {
		future_next = current->prev;
		if (current == tail) {
			head = tail;
			current->prev = nullptr;
			current->next = future_next;
		}//End of outer if
		else {
			current->next = future_next;
			current->prev = tail;
		}//End of else
		tail = current;
		current = future_next;
	}
}

template<typename AnyType>
void Doublely_Linked_list<AnyType>::clear_List() {
	for (Node* current = head, *next; current;) {
		next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	tail = nullptr;
}


int main() {
	Doublely_Linked_list<int> list1;
	int temp;
	int info = 2;
	while (1)
	{
		cin >> temp;
		if (temp == -1) break;
		else
		{
			list1.insertAtHead(temp);
		}
	}
	cout << list1;
	list1.remove(info);
	cout << list1;
	list1.insertAtHead(4);
	list1.insertAtTail(1);
	cout << list1;
	list1.reverse();
	cout << list1;
	list1.clear_List();
}


/*Output:
1
3
4
5
2
- 1
Printing the list :
2 5 4 3 1
Printing the list :
5 4 3 1
Printing the list :
4 5 4 3 1 1
Printing the list :
1 1 3 4 5 4
*/