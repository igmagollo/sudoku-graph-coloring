#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <tuple>
#include <vector>
#include "graph.hpp"

using namespace std;

class sudoku
{
private:
	graph g;
	int colors[81];
	vector<int> index_constants;

public:
	sudoku();
	sudoku(vector<tuple<int, int> > numbers);
	~sudoku() = default;
	
	/**
	*	return the graph
	*/
	const graph& getGraph() const;

	/**
	*	print the sudoku
	*/
	void printSudoku() const;

	/**
	*	load a pre color sudoku from a file
	*/
	bool loadFromFile(const string& string);
};

#endif