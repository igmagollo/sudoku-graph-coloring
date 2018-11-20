#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
using namespace std;

class graph
{
private:
	vector<vector<int> > v;

	/**
	*	push back a target vertice in a vertice
	*/
	void pushBackEdge(int v_index, int v_target);

public:
	graph();
	graph(vector<vector<int> > vertices);
	~graph() = default;

	/**
	*	add a new vertice and returns your number
	*/
	int newVertice();

	/**
	*	add n vertices
	*/
	void newNVertices(int n);

	/**
	*	add an edge
	*/
	void addEdge(int v1, int v2);

	/**
	*	get a vertice
	*/
	const vector<int>& getVertice(int v_index);

	/**
	*	get the degree of the vertice at the index specified
	*/
	int getVerticeDegree(int v_index) const;

	/**
	*	print the graph
	*/
	void printGraph() const;
};

#endif