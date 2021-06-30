/*
* ������������ ������ �9
* ���������� � ����� �������� ���������������� �������� ��������
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

// ����� ������
int N;

struct Tree {
	int item;
	Tree* right;
	Tree* left;
};

Tree* root;

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
		if (n < 0) {
			std::cout << "Write numbers greater than 0!\n " << std::endl;
			std::cout << "Write again: " << std::endl;
			b = true;
		}
	}

	return n;
}

// ���������� ��������������� �����
int getValue() {
	int val;
	val = rand() % 100;
	return val;
}

// ������ ��������� �������� ������
Tree* buildTree(int N) {
	Tree* rootT; // ������ ���������

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

// ����� � ������ �������
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

// ����� � ������������ �������
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

// ����� � �������-������������ �������
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

	// �� ������� �� ���������, ���� ������������ �� ������� �����
	while (command) {
		std::cout << "----------------------------" << std::endl;
		std::cout << "Enter quantity of vertex: " << std::endl;
		N = checkInput();
		root = buildTree(N);

		std::cout << "Forward: " << std::endl;
		forward(root, 0);
		std::cout << "Symmetric: " << std::endl;
		symmetric(root, 0);
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