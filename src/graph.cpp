#include "../models/graph.hpp"
#include <iostream>
using namespace std;

graph::graph() { }

graph::graph(vector<vector<int> > vertices) : v (vertices)
{

}

int graph::newVertice()
{
	this->v.push_back(vector<int>{});
	return this->v.size()-1;
}

void graph::newNVertices(int n)
{
	for ( int i = 0; i < n; i++ )
		newVertice();
}

void graph::pushBackEdge(int v_index, int v_target)
{
	this->v[v_index].push_back(v_target);
}

void graph::addEdge(int v1, int v2)
{
	if ( v1 >= this->v.size() || v2 >= this->v.size() )
		return;
	pushBackEdge(v1,v2);
	pushBackEdge(v2,v1);
}

const vector<int>& graph::getVertice(int v_index)
{
	return this->v.at(v_index);
}

int graph::getVerticeDegree(int v_index) const
{
	return this->v.at(v_index).size();
}

void graph::printGraph() const
{
	for ( int i = 0; i < this->v.size(); i++ )
	{
		cout << "v[" << i << "] -> ";
		for ( int j = 0; j < this->v.at(i).size(); j++ )
		{
			cout << this->v.at(i).at(j);
			if ( j+1 < this->v.at(i).size() )
				cout << ", ";
		}
		cout << endl;
	}
}
