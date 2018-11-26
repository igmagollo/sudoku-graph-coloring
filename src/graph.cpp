#include "../models/graph.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

graph::graph(vector<set<int> > vertices) : v (vertices)
{

}

int graph::newVertice()
{
	this->v.push_back(set<int>());
	return this->v.size()-1;
}

void graph::newNVertices(int n)
{
	for ( int i = 0; i < n; i++ )
		newVertice();
}

void graph::pushBackEdge(int v_index, int v_target)
{
	this->v[v_index].insert(v_target);
}

bool graph::edgeExists(const set<int>& v1, int v2) const
{
	if ( v1.find(v2) != v1.end() )
		return true;
	return false;
}

void graph::addEdge(int v1, int v2)
{
	if ( v1 >= this->v.size() || v2 >= this->v.size() )
		return;

	if ( !this->edgeExists( this->getVertice(v1), v2 ) )
		pushBackEdge(v1,v2);
	if ( !this->edgeExists( this->getVertice(v2), v1 ) )
		pushBackEdge(v2,v1);
}

const set<int>& graph::getVertice(int v_index) const
{
	return this->v.at(v_index);
}

int graph::getVerticeDegree(int v_index) const
{
	return this->v.at(v_index).size();
}

void graph::printGraph() const
{
	set<int>::iterator j;
	for ( int i = 0; i < this->v.size(); i++ )
	{
		cout << "v[" << setw(2) << i << "] -> ";
		for ( j = v.at(i).begin(); j != this->v.at(i).end(); j++ )
		{
			if ( j != v.at(i).begin() )
				cout << ", ";
			cout << setw(2) << *j;
		}
		cout << endl;
	}
}
