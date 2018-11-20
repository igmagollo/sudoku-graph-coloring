#include "models/graph.hpp"
#include "models/sudoku.hpp"
#include <vector>
#include <tuple>

using namespace std;

int main()
{
	sudoku s;
	s.loadFromFile("sudoku.txt");
	s.printSudoku();

	return 0;
}