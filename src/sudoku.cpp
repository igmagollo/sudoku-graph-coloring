#include "../models/sudoku.hpp"
#include <cstdio>
#include <fstream>

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
		this->index_constants.push_back(get<0>(numbers.at(i)));
	}

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
		this->index_constants.push_back(get<0>(numbers.at(i)));
	}

	return true;
}
