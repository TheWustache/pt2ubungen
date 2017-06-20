
#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>


static const auto N = 4;

auto A = std::vector<int>();
auto B = std::vector<int>();
auto C = std::vector<int>();


void print()
{
	#ifdef _WIN32
	std::system("cls");
	#else
	std::system("clear");
	#endif

	// Todo 5.2: Print current state


	std::cout << std::endl << std::endl;
}

void ToH(const int n, const int a, const int b, const int c, int & moves)
{
	// Todo 5.2: Implement ToH and print
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
