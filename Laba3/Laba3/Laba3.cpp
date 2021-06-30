/*
* ������������ ������ �3
* ������������ ��������� �������.
* �������� ����������� � ����������� ������������� ��������.
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>


const int MEMORY = 700;


struct Queue {
	char ch;
	Queue* next;
};

Queue* first, * last; // ��������� �� ������ � ����� �������

// ������� ������� � ����������
Queue* creatEmptyQueue() {
	Queue* queue = new Queue;
	queue->next = NULL;
	std::cout << "Queue created!" << std::endl;
	return queue;
}

// �������� �������� ��������
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

char getRandomChar() {
	char ch = 65 + rand() % 26;
	return ch;
}

// ���� first ��������� �� null �� ������� �����
bool isEmpty() {
	if (first->next == NULL) {
//		std::cout << "Queue is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// ������� �� ��������� ������
bool isFull() {
	MEMORYSTATUS ms;
	GlobalMemoryStatus(&ms);
	int a;
	a = (int)ms.dwAvailPhys / 1024 / 1024;

	if (a > MEMORY)
		return true;
	else {
		std::cout << "Queue is full!\n" << std::endl;
		return false;
	}
}

//������� ����� ������� � �������� ��� � ����� �������. ��������� ������� ������ ��������� �� null
void createItem(char item) {
	Queue* newLast = new Queue;
	newLast->ch = item;
	newLast->next = NULL;
	last->next = newLast;
	last = newLast;
}

// ������� ������� � ������ �������
// � first �������� ������ ���������� ��������� �� ��������� �������.
// ������� ��� ���������� �� ����
void deleteItem() {
	Queue* newFirst = first->next;
	first->next = newFirst->next;

	// ���� �� ������� ��������� �������, �� �������� �������� *last
	if (first->next == NULL) {
		last = first;
	}

	delete newFirst;
}

// ������� ������� � ������� ��������, �� ���������
void outputQueue() {
	if (isEmpty()) {
		std::cout << "Queue: " << std::endl;

		Queue* f = first;

		while (f->next != NULL) {
			Queue* newFirst = f->next;
			std::cout << newFirst->ch << std::endl;
			f = newFirst;
		}
	}
	else {
		std::cout << "Queue is empty! " << std::endl;
	}
}

void model() {
	char ch = 'w'; // ������ ��� ������ �� �����
	int a, q;
	char item;
	while (ch != 'a') { 
		a = rand() % 100 + 1; // ��������� ����� �� 1 �� 100
		q = rand() % 3 + 1; 

		//�������� ����������
		if (a % 2 == 0) {
			std::cout << "-----------------------------------" << std::endl;
			std::cout << "Add operation." << std::endl;
			std::cout << "Number of added elements: " << q << std::endl;
			for (int i = 0; i < q; ++i) {
				if (isFull()) {
					item = getRandomChar();
					createItem(item);
				}
			}
			outputQueue();
		}
		//�������� ��������
		else {
			std::cout << "-----------------------------------" << std::endl;
			std::cout << "Delete operation." << std::endl;
			std::cout << "Number of deleted elements: " << q << std::endl;
		
			for (int i = 0; i < q; ++i) {
				if (isEmpty()) {
					deleteItem();
				}
			}
			outputQueue();
		}
		if (_kbhit()) {
			ch = _getch();
		}
		Sleep(2000);
	}
}

int main() {
	int command = 1;  // ����, ����������� �����������
	
	// ������� ��� ��������� �� ���� � ��� �� ������� (���������)
	first = last = creatEmptyQueue();

	// �� ������� �� ���������, ���� ������������ �� ������� �����
	while (command) {
		char item;

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nStart the queue model           - 1" << std::endl;

		bool b = true;

		// ����, ����� ��� �������� ������������ �������, ��������� ���� ������
		while (b) {
			b = false;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {
			case 1:
				model();
				break;

			default:
				std::cout << "Wrong command!" << std::endl;
				b = true;
			}
		}

		while (true) {
			std::cout << "Continue the programm? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}
	return 0;
}