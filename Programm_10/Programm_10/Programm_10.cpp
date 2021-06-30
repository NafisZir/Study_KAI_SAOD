/*
* Лабораторная рабоа №10
* Добавить в предыдущую программу (лаба 9) нерекурсивный вариант процедуры обхода дерева в симметричном порядке
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

// Число вершин
int N;

struct Tree {
	int item;
	Tree* right;
	Tree* left;
};
Tree* root;

struct Stack {
	int level;
	Stack* next;
	Tree* treeP;
};
Stack* head;

//Первичная инициализация главного стека
void initStack() {
	Stack* stack = new Stack;
	stack->level = -1;
	stack->next = NULL;
	stack->treeP = NULL;
	head = stack;
}

//Если стек не пустой, то возвращает true
bool isEmpty() {
	if (head->next == NULL) {
		std::cout << "Stack is empty!\n" << std::endl;
		return false;
	}
	else
		return true;
}

// проверка вводимых значений
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
			//Если будет выброшено какое-то исключение, которое не обработано выше, то говорим, что возникла неизвестная ошибка
			std::cout << "Unknown error!\n";
			std::cout << "Write again: " << std::endl;
			b = true;
		}
		if (n < 0) {
			std::cout << "Write numbers greater than 0!\n " << std::endl;
			std::cout << "Write again: " << std::endl;
			b = true;
		}
	}

	return n;
}

// Возвращает сгенерированное число
int getValue() {
	int val;
	val = rand() % 100;
	return val;
}

// Строит идеальное двоичное дерево
Tree* buildTree(int N) {
	Tree* rootT; // Корень поддерева

	if (N == 0) {
		return NULL;
	}
	else {
		int nL = N / 2;
		int nR = N - nL - 1;
		rootT = new Tree;
		rootT->item = getValue();
		rootT->left = buildTree(nL);
		rootT->right = buildTree(nR);

		return rootT;
	}
}

//Добавление нового элемента в главный стек
void addPointer(Tree* p, int lvl) {
	Stack* newHead = new Stack;
	newHead->level = lvl;
	newHead->treeP = p;
	newHead->next = head;
	head = newHead;
}

//Удаление элемента из стека
void deletePointer() {
	if (isEmpty()) {
		Stack* newHead = head->next;
		delete head;
		head = newHead;
	}
}

// Вывод в прямом порядке
void forward(Tree* current, int lvl) {
	if (current != NULL) {
		std::string str = "     ";
		for (int i = 0; i < lvl; ++i) {
			str += "     ";
		}
		std::cout << str << current->item << std::endl;

		forward(current->left, lvl + 1);
		forward(current->right, lvl + 1);
	}
}

// Вывод в симметричном порядке
void symmetric(Tree* current, int lvl) {
	if (current != NULL) {
		symmetric(current->left, lvl + 1);

		std::string str = "     ";
		for (int i = 0; i < lvl; ++i) {
			str += "     ";
		}
		std::cout << str << current->item << std::endl;

		symmetric(current->right, lvl + 1);
	}
}

// Симметричный вывод без рекурсии
void symmetricWithStack() {
	if (root != NULL) {
		// Выполняем вывод пока в стеке есть указатели. Внешний цикл
		while (head->next != NULL) {
			Tree* current = head->treeP;
			// цикл, добавляющий левые поддеревы
			while (current->left != NULL) {
				addPointer(current->left, head->level + 1);
				current = current->left;
			}

			// Выводим существуюущие вершины, пока не найдется вершина с правым поддеревом
			// или пока стек не станет пустым
			while (head->next != NULL) {
				current = head->treeP;
				int l = head->level;
				std::string str = "     ";
				for (int i = 0; i < l; ++i) {
					str += "     ";
				}
				std::cout << str << current->item << std::endl;
				deletePointer();
				// Если нашли правое поддерево, то добавляем его в стек
				// и переходим к циклу добавления левых вершин
				if (current->right != NULL) {
					addPointer(current->right, ++l);
					break;
				}
			}
		}
	}
}

// Вывод в обратно-симметричном порядке
void backSymmetric(Tree* current, int lvl) {
	if (current != NULL) {
		backSymmetric(current->right, lvl + 1);

		std::string str = "     ";
		for (int i = 0; i < lvl; ++i) {
			str += "     ";
		}
		std::cout << str << current->item << std::endl;

		backSymmetric(current->left, lvl + 1);
	}
}

int main() {
	int command = 1;

	// не выходим из программы, пока пользователь не захочет этого
	while (command) {
		initStack();
		std::cout << "----------------------------" << std::endl;
		std::cout << "Enter quantity of vertex: " << std::endl;
		N = checkInput();
		root = buildTree(N);
		addPointer(root, 0);

		std::cout << "Forward: " << std::endl;
		forward(root, 0);
		std::cout << "Symmetric recursia: " << std::endl;
		symmetric(root, 0);
		std::cout << "Symmetric with stack: " << std::endl;
		symmetricWithStack();
		std::cout << "Back-Symmetric: " << std::endl;
		backSymmetric(root, 0);

		while (true) {
			std::cout << "Continue the programm? 1/0" << std::endl;
			command = checkInput();
			if (command == 0 || command == 1) break;
			std::cout << "Wrong command!" << std::endl;
		}
	}
	return 0;
}