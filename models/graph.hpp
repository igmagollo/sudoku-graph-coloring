#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <set>
using namespace std;

class graph
{
private:
	vector<set<int> > v;

	/**
	*	push back a target vertice in a vertice
	*/
	void pushBackEdge(int v_index, int v_target);

public:
	graph() = default;
	graph(vector<set<int> > vertices);
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
	*	returns true if v2 is in v1's neighbors
	*/
	bool edgeExists(const set<int>& v1, int v2) const;

	/**
	*	add an edge
	*/
	void addEdge(int v1, int v2);

	/**
	*	get a vertice
	*/
	const set<int>& getVertice(int v_index) const;

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