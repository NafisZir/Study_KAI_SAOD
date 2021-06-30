/*
* ������������ ������ �1
* ������������ ���������� �����
* ���� �������������� ���� ��� �������� ��������� ��������� �� �������� �����.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

const int MEMORY = 700; // ���������� ��������� ������ � ��. ���� �������� �������, �� ��������� ���������� ����� ���������

struct Stack {
	int i;
	Stack *next;
};

//������� ���������, ����� ������������ ���� ������ �����
int checkInput() {
	int n;
	bool b = true;
	std::string s;

	while (b) {
		b = false;
		try {
			std::cin >> s;
			n = std::stoi(s);
		}
		catch (std::invalid_argument) {
			std::cout << "Only numbers are allowed!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
		catch (std::out_of_range) {
			std::cout << "Too great a value!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
		catch (...) {
			//���� ����� ��������� �����-�� ����������, ������� �� ���������� ����, �� �������, ��� �������� ����������� ������
			std::cout << "Unknown error!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
	}

	return n;
}

//��������� ������������� �������� �����
Stack *creatEmptyStack() {
	Stack *stack = NULL;
	std::cout << "Stack created!" << std::endl;
	return stack;
}

//��������� ������������� ���������� �����
Stack* creatEmptyStackDop() {
	Stack* stack = NULL;
	std::cout << "And subsidiary stack too!\n" << std::endl;
	return stack;
}

//���� ���� �� ������, �� ���������� true
bool isEmpty(Stack* head) {
	if (head == NULL) {
		std::cout << "Stack is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

//�������� ������������� ������. ���� ��������� ������ ������ �������������� ��������, �� ���������� false
bool isFullness(Stack* head) {
	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);
	int a;
	a = (int)ms.dwAvailPhys / 1024 / 1024;

	if (a > MEMORY) 
		return true;
	else {
		std::cout << "Stack is full!\n" << std::endl;
		return false;
	}
}

//���������� ������ �������� � ������� ����
Stack *createItem(Stack *head, int item) {
	if (isFullness(head)) {
		Stack* newHead = new Stack;
		newHead->i = item;
		newHead->next = head;
		return newHead;
	}
}

//���������� ������������� �������� �� ���������� �����
void addItemFromOther(Stack* arrHead[]) {
	if (isEmpty(arrHead[1])) {
		Stack* newHead = arrHead[1]->next;
		arrHead[1]->next = arrHead[0];
		arrHead[0] = arrHead[1];
		arrHead[1] = newHead;
	}
}

//���������� ���������� ��������� � ������� ����
Stack* addSeveralItems(Stack* head) {
	int a;
	int item;

	std::cout << "Enter the quantity of items: " << std::endl;
	a = checkInput();

	for (int i = 0; i < a; ++i) {
		item = rand();
		head = createItem(head, item);
	}
	std::cout << "items added successfully!\n" << std::endl;
	return head;
}

//���������� ������������� �������� �� ��������� ����
void addItemDop(Stack* arrHead[]) {
	arrHead[0]->next = arrHead[1];
	arrHead[1] = arrHead[0];
	std::cout << "Item moved!\n" << std::endl;
}

//�������� �������� �� �����
void deleteItem(Stack *arrHead[]) {
	int a;
	while (true) {
		std::cout << "Really delete item (1) or move it (2)?" << std::endl;
		a = checkInput();
		if (a == 1 || a == 2) break;
		std::cout << "Wrong command!" << std::endl;
	}

	if (isEmpty(arrHead[0])) {
		Stack* newHead = arrHead[0]->next;
		if (a == 1) {
			delete arrHead[0];
			std::cout << "Item deleted!\n" << std::endl;
		}
		if (a == 2) addItemDop(arrHead);
		arrHead[0] = newHead;
	}
}

//����� ����� � �������
void outputStack(Stack* head) {
	if(isEmpty(head)){
		std::cout << "Stack: " << std::endl;
		
		while (head != NULL) {
			std::cout << head->i << std::endl;
			head = head->next;
		}
	}
}

int main()
{
	bool b = true;
	int item, a;
	Stack* arrHead[2]; //������ ��������: 0 - ��������� �� ������ �������� �����, 1 - ��������� �� ������ ���������� �����

	Stack* stackHead = creatEmptyStack();       //������������� �����
	arrHead[0] = stackHead;
	Stack* dopStackHead = creatEmptyStackDop(); //������������� ���������� �����
	arrHead[1] = dopStackHead;

    int command = 1;
	while (command) {
		
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck stack for emptiness       - 1" << std::endl;
		std::cout << "Adding several items            - 2" << std::endl;
		std::cout << "Adding an item to the stack     - 3" << std::endl;
		std::cout << "Deleting an item from the stack - 4" << std::endl;
		std::cout << "Output stack on the console     - 5" << std::endl;
		std::cout << "Enter the command: " << std::endl;

		command = checkInput();
		
		switch (command) {
		
		case 1:
			if(isEmpty(arrHead[0]))
				std::cout << "Stack is not empty!\n" << std::endl;
			break;
		
		case 2:
			arrHead[0] = addSeveralItems(arrHead[0]);
			break;
		
		case 3:
			// ������� ����� ��� ����������� �� ���������� �����
			while (true) {
				std::cout << "Create a new item (1) or to take from other (2)?" << std::endl;
				a = checkInput();
				if (a == 1 || a == 2) break;
				std::cout << "Wrong command!" << std::endl;
			}

			if (a == 1) {
				std::cout << "Enter the item: " << std::endl;
				item = checkInput();
				arrHead[0] = createItem(arrHead[0], item);
				std::cout << "Item added!\n" << std::endl;
			}
			else
				addItemFromOther(arrHead);
			break;
		
		case 4:
			deleteItem(arrHead);
			break;
		
		case 5:
			// ������ ��������? �� ��������� ��� ���������� �����
			while (true) {
				std::cout << "Show main stack (1) or other (2)?" << std::endl;
				a = checkInput();
				if (a == 1 || a == 2) break;
				std::cout << "Wrong command!" << std::endl;
			}

			if(a == 1) outputStack(arrHead[0]);
			else outputStack(arrHead[1]);
			break;

		// ���� ������� ������������ �������
		default:
			std::cout << "Wrong command!" << std::endl;
		}

		//�������� ����, ����� ������������ ���� ������ ������ �����
		while (true) {
			std::cout << "Continue the programm? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}

	return 0;
}
