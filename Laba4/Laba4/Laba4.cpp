/*
* ������������ ������ �4
* ����������� ���������� �������������� ��������� ������ �� ������ �������.
*/

#include <iostream>
#include <string>

const int ERROR = -1; // ������������ ��������, ���� �������� ������� �� ������ � ������
const int SIZE = 5; //������ �������
int count = 0;      // ���������� ��������� �������

struct List {
	int item;
};

List* list[SIZE];  // ������-������

// �������� ������� ������
bool isEmpty() {
	if (count == 0) {
		std::cout << "List is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// �������� ������� ������
bool isFull() {
	if (count == SIZE) {
		std::cout << "List is full!\n" << std::endl;
		return false;
	}
	else
		return true;
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

// ������� ������ ��� ������������� �������
int findPlace(int element) {
	int index;
	for (int i = 0; i < count; ++i) {
		if (list[i]->item > element) { return i; }
	}
	// ���� � ������ ��� �������� ������� ���������, �� ������ ��� � �����
	// ���������� ������� ���������� � ����, � count � 1
	// ������� �������� count ��������� �� ������ ������ ������
	return count;
}

// ����� � �������� �������� �������� ������, ����� �������� ���������� ��������� ����� �������
int findItem() {
	int element;
	while (true) {
		element = checkInput();

		for (int i = 0; i < count; ++i) {
			if (list[i]->item == element) { return i; }
		}

		std::cout << "This item was not found!" << std::endl;
		return ERROR;
	}
}

// ��������� ������ ��� ������ �������� � ��� ���������� � ������
void createItem(int element, int index) {
	List* newItem = new List;
	newItem->item = element;
	list[index] = newItem;
}

// ���������� ������ ��������
void addItem() {
	if (isFull()) {
		int element, index;
		std::cout << "Enter the item: " << std::endl;
		element = checkInput();

		//���� ��������� ������ �������
		if (count == 0) {
			createItem(element, 0);
		}
		else {
			index = findPlace(element);

			// ���������� �������� ������, ����� ���������� ����� ��� �����
			if (list[index] != NULL) {
				for (int i = count - 1; i >= index; --i) {
					list[i + 1] = list[i];
				}
			}

			createItem(element, index);
		}

		++count;
	}
}

// �������� ���������� ��������
void deleteItem() {
	if (isEmpty()) {
		int index;
		std::cout << "What to delete: " << std::endl;
		while (true) {
			index = findItem();
			if (index == ERROR) {
				std::cout << "Write again: " << std::endl;
				continue;
			}
			break;
		}
		List* oldItem = list[index];
		list[index] = NULL;
		// ���������� �������� �����, ����� ������ �������
		if (list[index + 1] != NULL) {
			for (int i = index; i < count; ++i) {
				list[i] = list[i + 1];
			}
		}

		delete oldItem;
		--count;
	}
}

//����� ����������� ������
void outputList() {
	if (isEmpty()) {
		std::cout << "List:" << std::endl;
		for (int i = 0; i < count; ++i) {
			std::cout << list[i]->item << std::endl;
		}
	}
}

int main()
{
	int command = 1;  // ����, ����������� �����������
	int index;
	// �� ������� �� ���������, ���� ������������ �� ������� �����
	while (command) {

		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\nCheck list for emptiness       - 1" << std::endl;
		std::cout << "Check list for fullness        - 2" << std::endl;
		std::cout << "Adding an item to the list     - 3" << std::endl;
		std::cout << "Deleting an item from the list - 4" << std::endl;
		std::cout << "Find the item                  - 5" << std::endl;
		std::cout << "Output list on the console     - 6" << std::endl;

		bool b2 = true;
		// ����, ����� ��� �������� ������������ �������, ��������� ���� ������
		while (b2) {
			b2 = false;

			std::cout << "Enter the command: " << std::endl;

			command = checkInput();

			switch (command) {
			case 1:
				if (isEmpty())
					std::cout << "List is not empty!\n" << std::endl;
				break;

			case 2:
				if (isFull())
					std::cout << "List is not full!\n" << std::endl;
				break;

			case 3:
				addItem();
				break;

			case 4:
				deleteItem();
				break;

			case 5:
				std::cout << "Write the value of the element: " << std::endl;
				index = findItem();
				if (index != ERROR) {
					std::cout << "Item found. Its index is " << index <<std::endl;
				}
				break;
			case 6:
				outputList();
				break;

			default:
				std::cout << "Wrong command!" << std::endl;
				b2 = true;
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