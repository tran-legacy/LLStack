/********************
 * Tran Le
 * CSS342 
 * Project #3 Linked List Stack
 * 6 hours for this file
 * 8 hours total
 * Vim on Cygwin
 *
 * Update since turn in: 
 * 1. Check if user entered file name exists and opened 
 ********************/

#include <iostream>
#include <fstream>
#include <string>
#include "llStack.h" 

// Prototypes 
int postFixCalc(const std::string& str); 
void performOperator(const char oper, LLStack<int>& stack);
bool isSpace(const char c, std::string& temp, LLStack<int>& stack); 
bool isNumber(const char c, std::string& temp, LLStack<int>& stack);
bool isOperator(const char c, LLStack<int>& stack);
bool isEndLine(const char c, const std::string& temp, LLStack<int>& stack);

int main(int argc, char* *argv) {
	std::string line = ""; 
	// If argc is 2, that means there's a file
	if (argc == 2) {
		std::ifstream infile(argv[1]); // open the file
		if (infile.is_open() && infile.good()) { 
			std::getline(infile, line);
			// getline does not get the newline character
			// I add '\n' in so my postFixCalc method could work properly
			line += '\n';
			std::cout << postFixCalc(line) << std::endl;
		} else {
			std::cout << "Error: File does not exist" << std::endl; 
		}
	}
   	// Else if argv is 1, that means prompt user for input	
	else if (argc == 1) {
		std::cout << "Enter the post-fix expression: "; 
		std::getline(std::cin,line);
		line += '\n';
		std::cout << postFixCalc(line) << std::endl; 
	
	} 
	// Else there is more than one file that was inputted on the cmd line
	else {
		std::cout << "One argument at a time please" << std::endl;
	}
	return 0; 
}

//// Function for outputting the calculation //// 
int postFixCalc(const std::string& str) {
	std::string temp = ""; 
	LLStack<int> stack; 
   
	// Iterating through each char in str
	for (int i = 0; i < str.size(); ++i) {
		// If current char is a space and temp contains something, convert
		// temp into an int and push it onto the stack 
		if (isSpace(str[i], temp, stack)) {}

		// Else if current char is a number, append to temp
		else if (isNumber(str[i], temp, stack)) {}

		// else if the current char is an operator
		else if (isOperator(str[i], stack)) {}

		// else if this is the newline char
		else if(isEndLine(str[i], temp, stack)) {}

		// else user tried to input characters that aren't digits or operators 	
	   	else {
			std::cout << "ERROR: Invalid input(s)." << std::endl;
			throw std::logic_error("");
		}
	}	

	// Return result	
	return stack.top(); 	
}

bool isSpace(const char c, std::string& temp, LLStack<int>& stack) {
	if (c == ' ') {
		if (!temp.empty()) {
			stack.push(std::stoi(temp)); 
			temp = ""; // Reset temp 
		}
		return true; 
	}
	return false;
}

bool isNumber(const char c, std::string& temp, LLStack<int>& stack) {
    if (c >= '0' && c <= '9') {
          temp += c;
  		return true;
      }
    return false; 
}

bool isOperator(const char c, LLStack<int>& stack) {
	if (c == '+' || c == '-' || c == '*' || c == '/') { 
		// If the stack has at least 2 items in it, perform the operator
		if (stack.size() >= 2) {
			performOperator(c, stack);
		// else the stack has 1 and therefore can't perform the operator
		} else {
		    std::cout << "ERROR: Too many operators" << std::endl;	
			throw std::logic_error(""); 
		}
		return true;
	}
	return false;
}

bool isEndLine(const char c, const std::string& temp, LLStack<int>& stack) {
	if (c == '\n') {
		// If stack size is more than 1, there are too many numbers 
	   	if (stack.size() > 1 || (!temp.empty())) {
			std::cout << "ERROR: Too many numbers" << std::endl;
		   	throw std::logic_error("");	
		// else the stack size is 1, then break and return final result
		}
		return true; 
	}
	return false; 	
}
//// Pop the two int on top of the stacks, perform the operator, and push result ////
void performOperator(const char oper, LLStack<int>& stack) {
	int num1 = stack.top(); 
	stack.pop(); 
	int num2 = stack.top(); 
	stack.pop(); 
	switch (oper) {
		case '+': 
			stack.push(num1 + num2);
			break;
		case '-':
			stack.push(num2 - num1); 
			break; 
		case '*': 
			stack.push(num1 * num2);
			break;
		case '/':
			stack.push(num2 / num1); 
			break; 
		default: 
			std::cout << "Error! Operator is not correct" << std::endl;
			break;
	}
}
