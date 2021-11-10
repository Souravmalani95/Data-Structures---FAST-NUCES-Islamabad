/*	Name:Sourav Malani
	Roll#:i19-0434
	Subject: Data Structures
	Section: A
	Assignment #: 2
	No. of test cases passed: 6/11
	Submission date: 10 Nov, 2020
*/
#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//Functions for my help
bool ArePair(char, char);
bool isOperand(const char);
int prcd(char );

template<typename Type>
struct QueueNode {
	Type value;
	QueueNode* next;

};

// Add the required functions 
template<typename Type>
struct Stack {
	Type* array;


};

template<typename Type>
class Stack1
{
	struct node
	{
		Type data;
		node* next;

	}*top;

public:
	Stack1() : top(NULL) {}
	void Push(Type newelement)
	{
		node* newptr;
		newptr = new node;

		newptr->data = newelement;
		newptr->next = top;
		top = newptr;
	}
	void Pop(Type &returnvalue)
	{
		if (IsEmpty())
		{
			cout << "underflow error";
			return;
		}
		node* tempptr;
		tempptr = top;
		returnvalue = top->data;
		top = top->next;

		delete tempptr;
	}
	bool IsEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Type Top() {
		return top->data;
	}
};


struct Queue {//use linked list base implementation 

};

template <typename T>
struct Variables { //A linked list of Variables can be use for finding the variable and associated value 
	T value;
	string Name;

};


template<typename T>
struct ListNode {
	T value;
	ListNode* next;

};

template<typename Type>
class LinkedList {
public:
	ListNode<Type>* head = NULL;
	ListNode<Type>* last = NULL;
	void insert(Type item); /*This Function inserts the item at the end of the list only*/
	//int DeleteNode(Type x); /*Deletes the given node, returns the index of the node, if
	//						   Node Does not exits, returns -1*/
};

template <typename Type>
void LinkedList<Type>::insert(Type List) { /*This Function inserts the item at the end of the list only*/
	Type newNode;
	newNode = List;
	ListNode<Type>* newNode1;
	newNode1 = new ListNode<Type>;
	newNode1->value = newNode;
	newNode1->next = NULL;
	if (head == NULL) {
		head = newNode1;
		last = newNode1;
	}
	else {
		last->next = newNode1;
		last = newNode1;//last = last->next;
	}

} // end insert


class SpecialStack {
public:
	Queue queue1;
	Queue queue2;
};

// Simply just read the file
// Use '\n' to sperate each line of code
string readFile(string a = "code.txt") {
	ifstream inputFile;
	inputFile.open(a);
	string str,tmpStr;
	while (!inputFile.eof()) {
		getline(inputFile, tmpStr);
		str += tmpStr;
		str += '\n';
	}
	return str;
}

//// Remove useless lines so line addressing is done properly
string removeLines(string code) {
	int i = 0;
	while (code[i]!='\0') {
		if (code[i] == '\n') {
			int j = i + 1, k = i,l=0;
			if (code[i + 1] == '\n') {
				l = i + 1;
				goto wh;
			}
			while (code[j] == ' ' ) {
					if(code[j+1] == '\n'){
						l = j + 1;
						wh:
						while (code[l] != '\0') {
							code[k] = code[l];
							k++;
							l++;
						}
						code[k] = '\0';
						break;
					}
					j++;
			}
		}
		i++;
    }
	i = 0;
	string tempStr = "";
	while (code[i] != '\0') {
		tempStr+= code[i++];
	}
	return tempStr;
}



// use this for checking indentations (function, loops, if conditions, etc.)
string checkIndentationErrors(string code) {
	Stack1<char> ST;
	int i = 0;
	char sym,otSym;
	while (code[i] != '\0') { // While code does'nt end.
		sym = code[i];
		if (sym == '(' || sym == '{' || sym == '[') //If the symbol is an opening symbol, push it onto the stack. 
			ST.Push(sym);
		else if (sym == ')' || sym == '}' || sym == ']') {// Closing symbol
			if (ST.IsEmpty())
				return "Indentation error detected";
			else {
				ST.Pop(otSym);
				if(!ArePair(otSym, sym))
                   return "Indentation error detected";
			}
		}
	i++;}//End while
	if(!ST.IsEmpty())
		return "Indentation error detected";
	else 
		return "Indentation error NOT detected";
}

////// Check if the function calls itself indefinitely
string checkInfiniteLoop(string readCode) {

	return " ";
}

//// This prepends a line address to every single line in program
string prependLineAddress(string codeWithoutLines){
	int address = 100, i = 0;
	string tempStr = "",addressStr = "";
	while (codeWithoutLines[i] != '\0') {
		addressStr = "";
		addressStr += 'C';
		addressStr += to_string(address);
		addressStr += "    "; //4 spaces
		tempStr += addressStr;
		while (codeWithoutLines[i] != '\n') {
			tempStr += codeWithoutLines[i++];
		}
		tempStr += '\n';
		address++;
		i++;
	}
	return tempStr;
}


void CreateRunTimeStack(string filename, string outputFile) {
	ofstream output;
	output.open(outputFile);
	output.close();
}

//// Start execution from the main function and use outputFile to print the output
//// Must use CreateRunTimeStack() for execution of the code
void ExecuteCode(string filename, string outputFile) {
	ofstream output;
	output.open(outputFile);
	output.close();
	
}

string infixToPostfix(string expression) {
	Stack1<char> opstk;//	opstk = the empty stack;
	int i = 0;
	char symb,topsymb;
	string postfix ="";
	while (expression[i]) {
		symb = expression[i];
		if (isOperand(symb))
			postfix += symb;
		else if (symb == '(')
			opstk.Push(symb);
		else if (symb == ')') {
			while (opstk.Top() != '(') {
				postfix += opstk.Top();
				opstk.Pop(topsymb);
			}
			opstk.Pop(topsymb);
		}
		else {
			while (!opstk.IsEmpty() && (prcd(expression[i]) <= prcd(opstk.Top()))) {
				postfix += opstk.Top();
				opstk.Pop(topsymb);
			} /* end while */
			opstk.Push(symb);
		}/* end else */
	i++;} /* end while */
	while (!opstk.IsEmpty()) {
		postfix += opstk.Top();
		opstk.Pop(topsymb);
	}
	return postfix;
}


template <typename T>
T makeoperation(T opnd1, T opnd2,char symb) {
	switch (symb)
	{
	case '+': return opnd1 + opnd2;
	case '-': return opnd1 - opnd2;
	case '*': return opnd1 * opnd2;
	case '/': return opnd1 / opnd2;
	case '$': return pow(opnd1 , opnd2);
	}
}
template<typename T>
T Solving_PostfixExpression(string expression, LinkedList<T> values) {
	T value,tempVal;
	int i = 0, opnd2, opnd1;
	char symb;
	Stack1<int> opndstk;
	ListNode<T>* current = values.head;
	i = 0;
	while (current!=NULL) { // Replace alphabest with numbers/values.
		tempVal = current->value;
		switch (expression[i])
		{
		case 'A':  expression[i] = '0'+ tempVal;		
			current = current->next;
			break;
		case 'B':  expression[i] = '0' + tempVal;
			current = current->next;
			break;
		case 'C':  expression[i] = '0' + tempVal;
			current = current->next;
			break;
		case 'D':  expression[i] = '0' + tempVal;
			current = current->next;
			break;
		case 'E':  expression[i] = '0' + tempVal;
			current = current->next;
			break;
		case 'F':  expression[i] = '0' + tempVal;
			current = current->next;
		}
		i++;
	}

	i = 0;
	while (expression[i] != '\0') { // Evaluate the expression with numbers.
		symb = expression[i];
		if (isOperand(symb))
			opndstk.Push(symb - '0');
		else {
			/* symb is an operator */
			opndstk.Pop(opnd2);
			opndstk.Pop(opnd1);
			value = makeoperation(opnd1, opnd2, symb);
			opndstk.Push(value);
		} /* end else */
		i++;
	} /* end while */
	opndstk.Pop(opnd1);
	return (opnd1);
}
//// Code should be templatized
template<typename Type>
class RuntimeNode{
		Type data;
		RuntimeNode *nodeAddress; //same will be stored in ESP and EBP
								  //You may modify the above line
		RuntimeNode *next;
};













//Functions for my own help.
bool ArePair(char opening, char closing)//it tells whether given two brackets form pair.
{
	if (opening == '(' && closing == ')') return true;
	else if (opening == '{' && closing == '}') return true;
	else if (opening == '[' && closing == ']') return true;
	return false;
}

bool isOperand(const char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}
//Function to return precedence of the operators
int prcd(char c) {
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}