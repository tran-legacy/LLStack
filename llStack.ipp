/***********************
 * Tran Le
 * CSS342 - Project #3 Linked List Stack
 * 2 hours for .h and .ipp
 * Vim on Cygwin
************************/

/********Constructors*************/
template<typename Type>
LLStack<Type>::LLStack() {
	this->head = NULL;
	this->count = 0; 	
}
//// Deep copy ////
template<typename Type> 
LLStack<Type>::LLStack(const LLStack& obj) {
	if (obj.head == NULL) 
		return; 
	// Initialize a pointer pointing to the passed in rhs
	StackNode* objPtr = obj.head; 
	// Start a head node that is the same as the passed in rhs node
	this->head = new StackNode(objPtr->value);
	StackNode* thisPtr = this->head; 
	objPtr = objPtr->next; 
	while (objPtr) {
		thisPtr->next = new StackNode(objPtr->value);
	   	// Move pointers to next
		thisPtr = thisPtr->next; 
		objPtr = objPtr->next; 
	}
	this->count = obj.count; 	
}

/************Destructor************/
template<typename Type>
LLStack<Type>::~LLStack() {
	StackNode* thisPtr = head; 
	while (thisPtr) {
		// Set a garbage ptr to the current thisPtr
		StackNode* garbage = thisPtr; 
		// Increment thisPtr to the next one
		thisPtr = thisPtr->next;
		// Delete garbage, which was thisPtr current
		delete garbage;
	}	
	this->count = 0; 
}

/***********Functions**************/ 
//// Push adds a new item to the top (head) of the stack ////
template<typename Type>
void LLStack<Type>::push(const Type& newItem) {
	// If this is the first node in stack, make new node
	if (this->head == NULL) {
		this->head = new StackNode(newItem);
	    ++count; 	
	} else { // Else there's at least one node in the stack
		// Create temp ptr pointing to head of this stack
		StackNode* thisPtr = this->head; 
		// Allocate new item and connect it to the rest of the stack
		this->head = new StackNode(newItem, thisPtr);
		++count; 
	}
}

//// Pop takes off the top item of the stack ////
template<typename Type>
void LLStack<Type>::pop() {
	if (this->head == NULL) 
		return; 

	StackNode* garbage = this->head; 
	this->head = this->head->next; 
	delete garbage;
	--count; 	
}

//// Top returns a reference to the top element in the stack ////
template<typename Type>
Type& LLStack<Type>::top() const throw (std::logic_error) {
	// If stack is empty, throw logic_error
	if (this->head == NULL) 
		throw std::logic_error("The Stack is empty.");
	return this->head->value;
}

//// Empty returns whether or not the stack is empty ////
template<typename Type>
bool LLStack<Type>::empty() const {
	if (this->head == NULL) 
		return true;
	return false; 
}

//// Size returns how many elements are in the stack //// 
template<typename Type>
int LLStack<Type>::size() const {
	return this->count; 
}
/***********Operator Overload************/
template<typename Type> 
//// Deep copy of the rhs LLStack object ////
LLStack<Type>& LLStack<Type>::operator=(const LLStack<Type>& rhs) {
	// If rhs is null or rhs is the same as stack, don't do anything
	if (rhs.head == NULL || this->head == rhs.head)
		return *this; 

	// Delete current stack 
	delete this->head; 
	this->head = NULL;
	//// Delete everything in this first 
	//StackNode* deleting = this->head; 
	//while(deleting) {
	//	StackNode* garbage = deleting; 
	//	deleting = deleting->next;
	//	delete garbage; 
	//}
	
	// Initialize a pointer pointing to the passed in rhs
	StackNode* rhsPtr = rhs.head; 
	// Start a head node that is the same as the passed in rhs node
	this->head = new StackNode(rhsPtr->value);
	StackNode* thisPtr = this->head; 
	rhsPtr = rhsPtr->next; 
	while (rhsPtr) {
		thisPtr->next = new StackNode(rhsPtr->value);
	   	// Move pointers to next
		thisPtr = thisPtr->next; 
		rhsPtr = rhsPtr->next; 
	}
	this->count = rhs.count; 	
	return *this; 	
}


