/**************************************
 * Tran Le
 * CSS342 Project #3 LinkedList Stack
 * 2 hours for .h and .ipp
 * 8 hours total for project
 * Vim on Cygwin
 * ************************************/

#ifndef LLSTACK_H
#define LLSTACK_H
#include <stdexcept>

template <class Type> 
class LLStack {
public: 
	// Constructor 
	LLStack(); 
	// Copy Constructor 
	LLStack(const LLStack<Type>& obj);

	// Destructor 
	virtual ~LLStack<Type>(); 
	
	// Operator Overload
	LLStack<Type>& operator=(const LLStack<Type>& rhs); 

	// Functions 
	void push(const Type& newItem); 
	void pop(); 
	Type& top() const throw(std::logic_error); 
	bool empty() const; 
	int size() const; 

private: 
	struct StackNode {
		Type value; 
		StackNode* next; 
		/******StackNode Constructor******/
		StackNode(Type value, StackNode* next = NULL) {
			this->value = value; 
			this->next = next; 
		}
	}; 
	StackNode* head;
   	int count; 	
}; 
#include "llStack.ipp"
#endif  // !LLSTACK_H
