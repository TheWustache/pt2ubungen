
#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>

static const auto N = 10;

auto A = std::vector<int>();
auto B = std::vector<int>();
auto C = std::vector<int>();

std::vector<int>* stacks[] = {&A, &B, &C};

void printTimes(const char c, const int n) {
	for (int i = 0; i < n; i++) {
		std::cout << c;
	}
}
void printEmptyLine() {
	for (int rows = 0; rows < 3; rows++) {
		printTimes(' ', N+2);
		std::cout << char(219);
		printTimes(' ', N+2);
		std::cout << ' ';
	}
	std::cout << std::endl;
}
void printColumnRow(const int row) {
	char printchar;
	int slideSize;
	for (int column = 0; column < 3; column++) {
		//2n + 1 wide columns, 2n high
		//determine size of slice to print(or just space)
		if (N - stacks[column]->size() <= row) {
			printchar = char(219);
			slideSize = stacks[column]->at(N - 1 - row);
		}
		else {
			printchar = ' ';
		slideSize = 0;
		}
		//print slices
		printTimes(' ', 2 + (N - slideSize));
		printTimes(printchar, slideSize);
		std::cout << char(219); //middle
		printTimes(printchar, slideSize);
		printTimes(' ', 2 + (N - slideSize));
		std::cout << ' ';
	}
	std::cout << std::endl;
}

void printBottom() {
	printTimes(char(219), 7 * 2 + 3 + N*6);
	std::cout << std::endl;
	printTimes(char(219), 2+N);
	std::cout << 'A';
	printTimes(char(219), 2*(N+2)+1);
	std::cout << 'B';
	printTimes(char(219), 2 * (N + 2) + 1);
	std::cout << 'C';
	printTimes(char(219), N+2);
}
void print()
{
	#ifdef _WIN32
	std::system("cls");
	#else
	std::system("clear");
	#endif
	// Todo 5.2: Print current state
	for (int row = 0; row < N; row++) {
		printColumnRow(row);
		printEmptyLine();
	}
	printBottom();
	std::cout << std::endl << std::endl;
}


//move from a to c with help of b
void ToH(const int n, const int a, const int b, const int c, int & moves)
{
	//5.2: Implement ToH and print
	if (n == 1) {
		moves++;
		stacks[c]->push_back(stacks[a]->back());
		stacks[a]->pop_back();
		print();
		getchar();
	}
	else {
		ToH(n - 1, a, c, b,moves);
		ToH(1, a, b, c,moves);
		ToH(n - 1, b, a, c, moves);
	}
	
}

int main(int argc, char ** argv)
{
	int moves = 0;

	for (int i = N; i > 0; --i)
		A.push_back(i);
	print();
	getchar();
	ToH(N, 0, 1, 2, moves);
	std::cout << "minimal number of moves: " << moves << std::endl;

	getchar();
	return 0;
}
