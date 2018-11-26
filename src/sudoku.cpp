#include "../models/sudoku.hpp"
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h> 

using namespace std;

static int getRowQuadrant(int i)
{
	return (i % 9) / 3;
}

static int getColumnQuadrant(int i)
{
	return (i / 9) / 3;
}


sudoku::sudoku()
{
	// inicialization of colors
	for ( int i = 0; i < 81; i++ )
	{
		this->colors[i] = 0;
	}

	// cria	conexões
	this->createConnections();
}

sudoku::sudoku(vector<tuple<int, int> > numbers)
{
	// inicialization of colors
	for ( int i = 0; i < 81; i++ )
	{
		this->colors[i] = 0;
	}

	// pre-coloring
	for ( int i = 0; i < numbers.size(); i++ )
	{
		this->colors[get<0>(numbers.at(i))] = get<1>(numbers.at(i));
		this->index_constants.insert(get<0>(numbers.at(i)));
	}

	// cria	conexões
	this->createConnections();
}

void sudoku::createConnections()
{
	// Create graph connections
	this->g.newNVertices(81);
	for ( int i = 0; i < 81; i++ )
	{
		static int j;

		// Connections quadrant
		static int quadrant_row;
		static int quadrant_column;
		quadrant_row = getRowQuadrant(i);
		quadrant_column = getColumnQuadrant(i);
		j = i + 1;
		while ( getColumnQuadrant(j) == quadrant_column )
		{
			if ( getRowQuadrant(j) == quadrant_row )
			{
				this->g.addEdge(i,j);
				j++;
			}
			else
			{
				j += 6;
			}
		}

		// Connections row
		j = i+1;
		// evita repetições de edges
		while ( getRowQuadrant(j) == quadrant_row ) j++;
		while ( j % 9 > i % 9 )
		{
			this->g.addEdge(i,j);
			j++;
		}

		// Connections column
		j = i + 9;
		// evita repetições de edges
		while ( getColumnQuadrant(j) == quadrant_column ) j += 9;		
		while ( j < 81 )
		{
			this->g.addEdge(i,j);
			j += 9;
		}
	}
}

const graph& sudoku::getGraph() const
{
	return this->g;
}

int sudoku::getColorAt(int i) const
{
	return this->colors[i];
}

bool sudoku::Welsh_Powell()
{
	vector<set<int> > posible_colors(81, set<int>());
	vector<int> uncolored;

	// pre algoritmo. Aplicando pre coloração
	for ( int i = 0; i < 81; i++ )
	{
		if ( this->index_constants.find(i) == this->index_constants.end() )
		{
			// marca como não colorido
			uncolored.push_back(i);

			// inicia possibilidades de cores como 81 ( numero de vértices )
			for ( int j = 1; j < 10; j++ )
				posible_colors.at(i).insert(j);
		}
	}

	// para cada vertice pre colorido
	for ( set<int>::iterator i = this->index_constants.begin(); i != this->index_constants.end(); i++ )
	{
		// pegue os seus vizinhos
		set<int> vizinhos = this->getGraph().getVertice(*i);

		// para cada vizinho deste vertice pre colorido
		for ( set<int>::iterator j = vizinhos.begin(); j != vizinhos.end(); j++ )
		{
			set<int>::iterator eraser = posible_colors.at(*j).find(this->colors[*i]);
			if ( eraser != posible_colors.at(*j).end() )
			{
				// apague a possibilidade de cor
				posible_colors.at(*j).erase(eraser);	
			}
		}
	}

	
	/**
	*	Após aplicar este pre algoritmo tratando a pre coloração, temos vértices com graus diferentes
	*	e nem todas as possibilidades de cores.
	*	Que comece o algoritmo!
	*/

	// Ordenar os vértices em ordem crescente considerando a quantidade de opções de cores
	sort(uncolored.begin(), uncolored.end(), 
		[posible_colors](const int& a, const int& b) -> bool
		{
			return posible_colors.at(a).size() < posible_colors.at(b).size();
		});


	for ( int i = 1; i < uncolored.size() + 1; i++ )
	{
		if ( posible_colors.at(uncolored.at(i-1)).size() == 0 )
			return false;
		this->colors[uncolored.at(i-1)] = *(posible_colors.at(uncolored.at(i-1)).begin());
		
		set<int> vizinhos = this->getGraph().getVertice(uncolored.at(i-1));

		for ( set<int>::iterator j = vizinhos.begin(); j != vizinhos.end(); j++ )
		{
			set<int>::iterator eraser = posible_colors.at(*j).find(this->colors[uncolored.at(i-1)]);
			if ( eraser != posible_colors.at(*j).end() )
			{
				// apague a possibilidade de cor
				posible_colors.at(*j).erase(eraser);	
			}
		}
	}

	return true;
}

void sudoku::printSudoku() const
{
	cout << "  ----------------------- " << endl;
	for ( int i = 0; i < 81; i++ )
	{
		if ( i % 9 == 0 && i != 0)
		{
			cout << " |" << endl;
			if ( (i / 9) % 3 == 0 )
				cout << "  ----------------------- " << endl;
		}
		if ( i % 3 == 0 )
			cout << " |";
		if ( this->colors[i] == 0 )
			cout << "  ";
		else
			cout << " " << colors[i];
	}
	cout << " |" << endl;
	cout << "  ----------------------- " << endl;
}

void sudoku::printPreColorIndex() const
{
	set<int>::iterator i;
	int count = 0;
	cout << "[";
	for ( i = this->index_constants.begin(); i != this->index_constants.end(); i++ )
	{
		if ( i != this->index_constants.begin() )
			cout << ", ";
		if ( count % 10 == 0 && count )
			cout << endl << " ";
		cout << setw(2) << *i;
		count++;
	}
	cout << "]" << endl;
}

int sudoku::getPreColorSize() const
{
	return this->index_constants.size();
}

bool sudoku::loadFromFile(const string& name)
{
	ifstream file;
	string input_lines;
	int index, color, count = 0;
	vector<tuple<int, int> > numbers;

	file.open(name);
	if ( !file.is_open() )
		return false;

	while ( !file.eof() && count < 81 )
	{
		getline(file, input_lines);
		sscanf(input_lines.c_str(), "%d %d", &index, &color);
		numbers.push_back(make_tuple(index,color));
		count++;
	}

	// pre-coloring
	for ( int i = 0; i < numbers.size(); i++ )
	{
		this->colors[get<0>(numbers.at(i))] = get<1>(numbers.at(i));
		this->index_constants.insert(get<0>(numbers.at(i)));
	}

	return true;
}

bool sudoku::compara(const sudoku& outro) const
{
	for ( int i = 0; i < 81; i++ )
		if ( this->getColorAt(i) != outro.getColorAt(i) )
			return false;
	return true;
}
