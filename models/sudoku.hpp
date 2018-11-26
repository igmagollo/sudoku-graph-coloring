#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <tuple>
#include <vector>
#include <set>
#include "graph.hpp"

using namespace std;

class sudoku
{
private:
	graph g;
	int colors[81];
	set<int> index_constants;

	void createConnections();

public:
	sudoku();
	sudoku(vector<tuple<int, int> > numbers);
	~sudoku() = default;
	
	/**
	*	return the graph
	*/
	const graph& getGraph() const;

	/**
	*	retorna a cor na posição i
	*/
	int getColorAt(int i) const;

	/**
	*	algoritmo Welsh & Powell para coloração de grafos aplicado em sudoku
	*/
	bool Welsh_Powell();

	/**
	*	print the sudoku
	*/
	void printSudoku() const;

	/**
	*	print the pre-color
	*/
	void printPreColorIndex() const;

	/**
	*	returns the number of initial values
	*/
	int getPreColorSize() const;

	/**
	*	load a pre color sudoku from a file
	*/
	bool loadFromFile(const string& string);

	/**
	*	Compara as cores de dois sudokus para verificar igualdade (não verifica equivalencia)
	*/
	bool compara(const sudoku& outro) const;
};

#endif