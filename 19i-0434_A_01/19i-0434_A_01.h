//19i-0434_A_01.h ----------------------------------------------------------------------------------------------------------------------------------------------------------- 1
//Sourav Malani
//BS-CS
//Apriori algorithm implementation with LinkedList
//All 7 Test Cases Working. (11 October 2021)

#pragma once
#include <fstream>
//using namespace std;
char* Erase(char*&, int);
void strcpy1(char* original, char cpy[]);
bool equal1(const char a[], const char b[]);


template <class Type>
class LinkedList;   //Main linkList class

//  Global Variables
double SUPPORT_T = 0, FREQ = 0;
LinkedList<char*>* FREQ_2;


template <class Type>
struct node {
	Type data;
	node* next;
};

template <class Type>
class LinkedList {
public:
	node<Type>* head = NULL;
	node<Type>* last = NULL;
	void insert(Type List); /*This Function inserts the item at the end of the list only*/
	int DeleteNode(Type x); /*Deletes the given node, returns the index of the node, if
							   Node Does not exits, returns -1*/
	static bool validFreq(Type key, double SupportT1, double Freq1, int* itemFreq);    /*Returns true is frequancy is valid, otherwise returns fale.*/
	void FreqSort();  /*Sorts the items by their Frequency*/
	void FreqSort2();
	void sortedInsert(node<Type>* newnode, node<Type>*& sorted); /*Inserts the given node in ascending
																	  order in the node<Type> *sorted*/

	void sortedInsert2(node<Type>* newnode, node<Type>*& sorted); /*Inserts the given node in ascending*/

	void reverse();  /*Reverse the list*/
	void removeDuplicates();	/* Removes duplicates from a
								   unsorted linked list */
};

template <class Type>
void LinkedList<Type>::insert(Type List) { /*This Function inserts the item at the end of the list only*/
	Type newNode;
	newNode = List;
	node<Type>* newNode1;
	newNode1 = new node<Type>;
	newNode1->data = newNode;
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

template <class Type>
int LinkedList<Type>::DeleteNode(Type x) { /*Deletes the given node, returns the index of the node, if
						   Node does not exits, returns -1*/
	node<Type>* prevNode = NULL;
	node<Type>* currNode = head;

	int currIndex = 1;
	while (currNode && currNode->data != x) {
		prevNode = currNode;
		currNode = currNode->next;
		currIndex++;
	}
	if (currNode) {
		if (prevNode) {
			prevNode->next = currNode->next;
			if (last->next == NULL)
				last = prevNode;
			delete currNode;
		}
		else {
			head = currNode->next;
			delete currNode;
		}
		return currIndex;
	}
	return -1;
} // end DeleteNode


template <class Type>
bool LinkedList<Type>::validFreq(Type key, double SupportT1, double Freq1, int* itemFreq) {
	double valid = SupportT1 * Freq1;
	int count = 0;
	char* temp = TransactionLL.head->data.head->data;
	if (key == NULL) {
		return -1;
	}
	node<LinkedList<char*>>* current;
	node<char*>* current1;
	char tmp[10] = { '\0' };
	char tmp2[10] = { '\0' };
	bool eq = false;
	strcpy1(key, tmp2);

	current = TransactionLL.head;
	while (current != NULL) {
		current1 = current->data.head;
		while (current1 != NULL) {
			strcpy1(current1->data, tmp);
			eq = equal1(tmp, tmp2);
			if (eq)
				count++;
			current1 = current1->next;
		}
		current = current->next;
	}
	*itemFreq = count;
	if (count >= valid)
		return true;
	return false;
}//end ValifFreq

template<class Type>
void LinkedList<Type>::FreqSort() {
	node<Type>* sorted = NULL;
	node<Type>* current = head;
	while (current != NULL) {
		node<Type>* next = current->next;
		sortedInsert(current, sorted);
		current = next;
	}
	head = sorted;
}
template<class Type>
void LinkedList<Type>::sortedInsert(node<Type>* newnode, node<Type>*& sorted) {
	int tmp = 0;
	char* tmpstr;
	int num = 0, i = 0, num2 = 0;
	if (sorted != NULL) {
		tmpstr = sorted->data;
		while (tmpstr[i] != '(') {
			i++;
		}
		num = int(tmpstr[i + 1]) - 48;
	}
	i = 0;
	tmpstr = newnode->data;
	while (tmpstr[i] != '(') {
		i++;
	}
	num2 = int(tmpstr[i + 1]) - 48;

	if (sorted == NULL || num > num2) {//num = sorted->data | num2 = newnode->data
		newnode->next = sorted;
		sorted = newnode;
	}
	else {
		node<Type>* current = sorted;
		if (current->next != NULL) {
			tmpstr = current->next->data;
			while (tmpstr[i] != '(') {
				i++;
			}
			num = int(tmpstr[i + 1]) - 48;
		}
		i = 0;
		tmpstr = newnode->data;
		while (tmpstr[i] != '(') {
			i++;
		}
		num2 = int(tmpstr[i + 1]) - 48;

		while (current->next != NULL
			&& num < num2) { // num = current->next->data | num2 = newnode->data
			current = current->next;
		}
		newnode->next = current->next;
		current->next = newnode;
	}
}

template<class Type>
void LinkedList<Type>::FreqSort2() {
	node<Type>* sorted = NULL;
	node<Type>* current = head;
	while (current != NULL) {
		node<Type>* next = current->next;
		sortedInsert2(current, sorted);
		current = next;
	}
	head = sorted;
}
template<class Type>
void LinkedList<Type>::sortedInsert2(node<Type>* newnode, node<Type>*& sorted) {
	int tmp = 0;
	Type tmpstr;
	int num = 0, i = 0, num2 = 0;
	if (sorted != NULL) {
		num = sorted->data.pairCount;
		num2 = newnode->data.pairCount;
	}
	if (sorted == NULL || num < num2) {//num = sorted->data | num2 = newnode->data
		newnode->next = sorted;
		sorted = newnode;
	}
	else {
		node<Type>* current = sorted;
		if (current->next != NULL) {
			num = current->next->data.pairCount;
			num2 = newnode->data.pairCount;
		}
		while (current->next != NULL
			&& num > num2) { // num = current->next->data | num2 = newnode->data
			current = current->next;
		}
		newnode->next = current->next;
		current->next = newnode;
	}
}

template <class Type>
void LinkedList<Type>::reverse() { /*Reverses the list*/
	node<Type>* current = head;
	node<Type>* prev = NULL, * next = NULL;
	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}
template <class Type>
void LinkedList<Type>::removeDuplicates() /*Names describes it*/
{
	node<Type>* ptr1, * ptr2, * dup, * next_next;
	ptr1 = head;
	Type tmp;
	char tmp1[10] = { '\0' }, tmp2[10] = { '\0' };

	while (ptr1 != NULL && ptr1->next != NULL) {
		ptr2 = ptr1;

		while (ptr2->next != NULL) {
			tmp = ptr1->data;
			strcpy1(ptr1->data, tmp1);
			tmp = ptr2->next->data;
			strcpy1(tmp, tmp2);
			if (equal1(tmp1, tmp2)) {
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				delete (dup);
			}
			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

LinkedList<LinkedList<char*>>  TransactionLL; //Linked List is global.

void readInputFile(char* inputFilePath) {
	LinkedList<char*>* List1;
	LinkedList<char*>* List2;
	char ch;
	std::ifstream ip(inputFilePath); // ip can only read data from file "inputFilePath"
	TransactionLL = *new LinkedList<LinkedList<char*>>;
	if (!ip.is_open()) {
		std::cout << inputFilePath << " File not found" << std::endl;
		assert(ip.is_open()); // abort program if file not found
	}
	else {
		char* tmp2, tmp3, Support_T[5] = { '\0' }, Freqs[1] = { '\0' };
		int i = 0;
		while (ip.get(tmp3)) {
			if (tmp3 == '\n')
				break;
			Support_T[i++] = tmp3;
		}
		SUPPORT_T = std::stod(Support_T);
		while (ip.get(tmp3)) {
			if (tmp3 == '\n')
				break;
			Freqs[0] = tmp3;
		}
		FREQ = std::stod(Freqs);
		i = 0;
		List1 = new LinkedList<char*>;

		tmp2 = new char[10];
		while (ip.get(tmp3)) {
			if (tmp3 == ',') {
				List1->insert(tmp2);
				tmp2 = new char[10];
				i = 0;
				continue;
			}
			if (tmp3 == '\n') {
				List1->insert(tmp2);
				tmp2 = new char[10];
				i = 0;
				TransactionLL.insert(*List1);
				List1 = new LinkedList<char*>;
				continue;
			}
			*(tmp2 + i++) = tmp3;
			*(tmp2 + (i + 1)) = '\0';
		}
		List1->insert(tmp2);
		tmp2 = new char[10];
		i = 0;
		TransactionLL.insert(*List1);
		delete[] tmp2;

		ip.close(); //Close the file
	}
}

void removePunctuationMarks() {
	assert(TransactionLL.head != NULL); //transactionll is empty, abort program
	node<LinkedList<char*>>* current;
	node<char*>* current1;
	char* tmp, tmp2;
	current = TransactionLL.head;
	while (current != NULL) {
		current1 = current->data.head;
		while (current1 != NULL) {
			tmp = current1->data;
			tmp2 = *(tmp);
			int dec = 0;
			for (int i = 0; tmp2 != '\0'; i++) {
				tmp2 = *(tmp + i);
				bool flag = (((tmp2 < 'a' || tmp2 > 'z')) && ((tmp2 < 'A' || tmp2 > 'Z'))) && tmp2 != ' ' && tmp2 != '\0';
				if (flag) {
					if ((tmp2) != '\n')
						if (i == strlen(tmp)) {
							Erase(tmp, i - dec);
							dec++;
							break;
						}
						else {
							tmp = Erase(tmp, i);
							tmp2 = *(tmp + i);
							dec++;
						}
				}
				if (tmp2 == '\0')
					break;
			}
			current1->data = tmp;
			current1 = current1->next;
		}
		current = current->next;
	}
}
void writingTransactionLLToFile(char* outputFilePath) {
	std::fstream ip(outputFilePath, std::ios::out); // outputFilePath can be read and wrote,
										   // if there is no file on the name of outputhFilePath
										   // then it creates one.	
	node<LinkedList<char*>>* current;
	node<char*>* current1;

	current = TransactionLL.head;
	while (current != NULL) {
		current1 = current->data.head;
		while (current1 != NULL) {
			ip << current1->data;
			if (current1->next != NULL)
				ip << ',';
			current1 = current1->next;
		}
		if (current->next)
			ip << '\n';
		current = current->next;
	}
}

void convertUpperToLowerCase() {
	assert(TransactionLL.head != NULL); //TransactionLL is empty, abort program
	node<LinkedList<char*>>* current;
	node<char*>* current1;
	char* tmp, tmp2;

	current = TransactionLL.head;
	while (current != NULL) {
		current1 = current->data.head;
		while (current1 != NULL) {
			tmp = current1->data;
			tmp2 = *tmp;
			//int dec = 0;
			for (int i = 0; strlen(tmp); i++) {
				tmp2 = *(tmp + i);
				if (tmp2 >= 'A' && tmp2 <= 'Z') { // if uppercase
					*(tmp + i) = *(tmp + i) + 32;
				}
				if (tmp2 == '\0')
					break;
			}
			current1 = current1->next;
		}
		current = current->next;
	}

}


void generateFirstItemSet(char* frequency_output_file) {
	std::fstream ip2("tempFile.txt", std::ios::out);  // "tempFile.txt" can be read and wrote,
											// if there is no file on the name of outputhFilePath
											// then it creates one.	

	if (!ip2.is_open()) {
		std::cout << frequency_output_file << " File not found" << std::endl;
		assert(ip2.is_open()); // abort program if file not found
	}
	else {
		node<LinkedList<char*>>* current;
		node<char*>* current1, * current2;
		char* tmp, tmp2, * tmp3;
		bool valid = false;
		int itemFreq = 0;


		current = TransactionLL.head;
		while (current != NULL) {
			current1 = current->data.head;
			current2 = current->data.head;
			while (current1 != NULL) {
				tmp = current1->data;
				valid = LinkedList<char*>::validFreq(tmp, SUPPORT_T, FREQ, &itemFreq);
				if (!valid) {
					current2 = current1->next;
					current->data.DeleteNode(tmp);
					current1 = current2;
				}
				if (valid) {
					ip2 << tmp << '(' << itemFreq << ')';
					int len = strlen(tmp);
					if (tmp[len] == '\0')
						ip2 << '\n';
				}
				if (current1 == NULL)
					continue;
				current1 = current1->next;
			}
			current = current->next;
		}
		ip2.close();

		std::ifstream ip2("tempFile.txt", std::ios::out); // tempFile.txt can only be read.
		if (!ip2.is_open()) {
			std::cout << "tempFile.txt" << " File not found(2)" << std::endl;
			assert(ip2.is_open()); // abort program if file not found
		}
		else {
			char* tmp2, tmp3, Support_T[5] = { '\0' }, Freqs[1] = { '\0' };
			int i = 0;
			FREQ_2 = new LinkedList<char*>;

			tmp2 = new char[10];
			while (ip2.get(tmp3)) {
				if (tmp3 == '\n') {
					FREQ_2->insert(tmp2);
					tmp2 = new char[10];
					i = 0;
					continue;
				}
				else {
					*(tmp2 + i++) = tmp3;
					*(tmp2 + (i + 1)) = '\0';
				}
			}
			ip2.close(); //Close the file
			delete[] tmp2;
			FREQ_2->removeDuplicates();
			FREQ_2->FreqSort();
			FREQ_2->reverse();



			std::fstream ip(frequency_output_file, std::ios::out); // frequency_output_file can be read and wrote,
																	 // if there is no file on the name of outputhFilePath
																	 // then it creates one.	

			if (!ip.is_open()) {
				std::cout << frequency_output_file << " File not found" << std::endl;
				assert(ip.is_open()); // abort program if file not found
			}
			else {
				node<char*>* current = FREQ_2->head;
				while (current) {
					ip << current->data;
					if (current->next != NULL)
						ip << '\n';
					current = current->next;
				}
			}
			ip.close();

		}
	}
	//FREQ_2->print();
	//LinkedList<char*>::print2(TransactionLL.head);
}

void removeCharacters(char*& tmp) {
	int i = 0;
	while (tmp[i] != '\0') {
		if (tmp[i] == '(' || tmp[i] == ')' || (tmp[i] >= '1' && tmp[i] <= '9')) {
			Erase(tmp, i);
			i--;
		}
		i++;
	}
}

template<class Type>
class itemset2nd
{
public:
	Type item1;
	Type item2;
	bool item1P, item2P;
	int pairCount;
	itemset2nd()
	{
		item1 = "";
		item2 = "";
		item1P = false;
		item2P = false;
		pairCount = 0;
	}
};
template<class Type>
class itemset3rd
{
public:
	Type item1;
	Type item2;
	Type item3;
	bool item1P, item2P, item3P;
	int pairCount;
	itemset3rd()
	{
		item1 = item2 = item3 = "";
		item1P = item2P = item3P = false;
		pairCount = 0;
	}
};

void generateSecondItemSet(char* frequency_output_file) {
	node<char*>* current1, * current2; //pointers to traverse the FREQ_2
	char* tmp, * tmp2;
	LinkedList<itemset2nd<char*>>* itemset2;
	itemset2nd<char*>* itemset2_1;
	//current2 = current1->next;

	itemset2_1 = new itemset2nd<char*>;
	itemset2 = new LinkedList<itemset2nd<char*>>;

	current1 = FREQ_2->head;
	while (current1 != NULL) {
		current2 = current1->next;
		while (current2 != NULL) {
			tmp = current1->data;
			tmp2 = current2->data;
			removeCharacters(tmp);
			removeCharacters(tmp2);
			itemset2_1->item1 = tmp;
			itemset2_1->item2 = tmp2;
			//itemset2_1->print();
			itemset2->insert(*itemset2_1);
			itemset2_1 = new itemset2nd<char*>;
			current2 = current2->next;
		}
		current1 = current1->next;
	}
	//------------------------------------------------
	node<LinkedList<char*>>* current;
	//node<char*>* current1, * current2;
	//char* tmp, tmp2, * tmp3;
	bool valid = false;
	int itemFreq = 0;


	// Remove Items which has less frequency than the minimum required frequency.
	current = TransactionLL.head;
	while (current != NULL) {
		current1 = current->data.head;
		current2 = current->data.head;
		while (current1 != NULL) {
			tmp = current1->data;
			valid = LinkedList<char*>::validFreq(tmp, SUPPORT_T, FREQ, &itemFreq);
			if (!valid) {
				current2 = current1->next;
				current->data.DeleteNode(tmp);
				current1 = current2;
			}
			if (current1 == NULL)
				continue;
			current1 = current1->next;
		}
		current = current->next;
	}
	//---------------------------------------------------------------------------------------
	std::ofstream ip(frequency_output_file); // Create file for writing itemset3 to the file.

	node<itemset2nd<char*>>* current3, * current4;
	current3 = itemset2->head;
	while (current3 != NULL) {
		current = TransactionLL.head;   /*Traversing TransactionLL and finding out
										if FREQ_2's pair exists in the TransactionLL
										if it does, increasing pair count of FREQ_2's pair */
		while (current != NULL) {
			current1 = current->data.head;
			while (current1 != NULL) {
				//if(equal1(current3->data.item1, current1->data))
				if (equal1(current3->data.item1, current1->data)) {
					current3->data.item1P = true;
				}
				if (equal1(current3->data.item2, current1->data)) {
					current3->data.item2P = true;
				}
				current1 = current1->next;
			}
			if (current3->data.item1P && current3->data.item2P) {
				current3->data.pairCount++;
				current3->data.item1P = false;
				current3->data.item2P = false;
			}
			else {
				current3->data.item1P = false;
				current3->data.item2P = false;
			}
			current = current->next;
		}
		current3 = current3->next;
	}
	itemset2->FreqSort2();
	//itemset2->removeDuplicates2();
	current3 = itemset2->head;
	while (current3 != NULL) {
		if (current3->data.pairCount >= SUPPORT_T * FREQ) {
			ip<< current3->data.item1 << ',' << current3->data.item2 << '(' << current3->data.pairCount << ')';
			if (current3->next /*&& current3->next->data.pairCount >= SUPPORT_T * FREQ*/)
				ip << '\n';
		}
		current3 = current3->next;
	}
	ip.close();
}

void generateThirdItemSet(char* frequency_output_file) {
	node<char*>* current1, * current2, * current3; //pointers to traverse the FREQ_2
	char* tmp, * tmp1, * tmp2, * tmp3;
	LinkedList<itemset3rd<char*>>* itemset3;
	itemset3rd<char*>* itemset3_1;

	itemset3_1 = new itemset3rd<char*>;
	itemset3 = new LinkedList<itemset3rd<char*>>;


	current1 = FREQ_2->head;
	while (current1 != NULL) {
		current2 = current1->next;
		while (current2 != NULL) {
			current3 = current2->next;
			while (current3 != NULL) {
				tmp1 = current1->data;
				tmp2 = current2->data;
				tmp3 = current3->data;
				removeCharacters(tmp1);
				removeCharacters(tmp2);
				removeCharacters(tmp3);
				itemset3_1->item1 = tmp1;
				itemset3_1->item2 = tmp2;
				itemset3_1->item3 = tmp3;
				//itemset3_1->print();
				itemset3->insert(*itemset3_1);
				itemset3_1 = new itemset3rd<char*>;
				current3 = current3->next;
			}
			current2 = current2->next;
		}
		current1 = current1->next;
	}

	////------------------------------------------------
	node<LinkedList<char*>>* current;
	bool valid = false;
	int itemFreq = 0;


	// Remove Items which has less frequency than the minimum required frequency.
	current = TransactionLL.head;
	while (current != NULL) {
		current1 = current->data.head;
		current2 = current->data.head;
		while (current1 != NULL) {
			tmp = current1->data;
			valid = LinkedList<char*>::validFreq(tmp, SUPPORT_T, FREQ, &itemFreq);
			if (!valid) {
				current2 = current1->next;
				current->data.DeleteNode(tmp);
				current1 = current2;
			}
			if (current1 == NULL)
				continue;
			current1 = current1->next;
		}
		current = current->next;
	}
	////---------------------------------------------------------------------------------------
	std::ofstream ip(frequency_output_file); // Create file for writing itemset3 to the file.

	node<itemset3rd<char*>>* current4, * current5;
	current4 = itemset3->head;
	while (current4 != NULL) {
		current = TransactionLL.head;   /*Traversing TransactionLL and finding out
										if FREQ_2's pair exists in the TransactionLL
										if it does, increasing pair count of FREQ_2's pair */
		while (current != NULL) {
			current1 = current->data.head;
			while (current1 != NULL) {
				if (equal1(current4->data.item1, current1->data)) {
					current4->data.item1P = true;
				}
				if (equal1(current4->data.item2, current1->data)) {
					current4->data.item2P = true;
				}
				if (equal1(current4->data.item3, current1->data)) {
					current4->data.item3P = true;
				}
				current1 = current1->next;
			}
			if (current4->data.item1P && current4->data.item2P && current4->data.item3P) {
				current4->data.pairCount++;
				current4->data.item1P = false;
				current4->data.item2P = false;
				current4->data.item3P = false;
			}
			else {
				current4->data.item1P = false;
				current4->data.item2P = false;
				current4->data.item3P = false;

			}
			current = current->next;
		}
		current4 = current4->next;
	}
	itemset3->FreqSort2();
	current4 = itemset3->head;
	while (current4 != NULL) {
		if (current4->data.pairCount >= SUPPORT_T * FREQ) {
			ip << current4->data.item1 << ',' << current4->data.item2 << ',' << current4->data.item3 << '(' << current4->data.pairCount << ')';
		}
		if (current4->next)
			ip << '\n';
		current4 = current4->next;
	}
	ip.close();
}


























/*These functions are used somewhere in the functionality*/

char* Erase(char*& c, int start) {
	/*Erases characters from an character array.
	  on start index*/
	int i = 0, length = strlen(c);
	char* tmp = new char[length];
	int j = 0;
	for (int i = 0; i < length; i++) {
		if (i != start)
			tmp[j++] = c[i];
	}
	tmp[length - 1] = '\0';
	c = tmp;
	return c;
}

void strcpy1(char* original, char cpy[]) {
	for (int i = 0; i < strlen(original); i++) {
		cpy[i] = original[i];
	}
	cpy[strlen(original)] = '\0';
}


bool equal1(const char a[], const char b[]) {
	if (strlen(a) != strlen(b))
		return false;
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}
