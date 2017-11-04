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
		if (str[i] == ' ') {
			if (!temp.empty()) {
				stack.push(std::stoi(temp));
				temp = ""; // Reset temp 
			}
		}

		// Else if current char is a number, append to temp
		else if (str[i] >= '0' && str[i] <= '9') {
			temp += str[i]; 
		}

		// else if the current char is an operator
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') { 
			// If the stack has at least 2 items in it, perform the operator
			if (stack.size() >= 2) {
				performOperator(str[i], stack);
			// else the stack has 1 and therefore can't perform the operator
			} else { 
				std::cout << "Too many operators" << std::endl; 
				throw std::logic_error(""); 
			}
		}

		// else if this is the newline char
		else if (str[i] == '\n') {
			// If stack size is more than 1, there are too many numbers 
		   	if (stack.size() > 1 || (!temp.empty())) {
				std::cout << "Too many numbers" << std::endl;
			   	throw std::logic_error("");	
			// else the stack size is 1, then break and return final result
			} else {
				break; 
			}
		}

		// else user tried to input characters that aren't digits or operators 	
	   	else {
			std::cout << "Invalid input(s)." << std::endl;
			throw std::logic_error("");
		}
	}	

	// Return result	
	return stack.top(); 	
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
