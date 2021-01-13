#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include<bits/stdc++.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
#include <list>
#include <sstream>
// You may include more libraries.

using namespace std;

class Edge
{
	// You may add more variables and functions in this class
public:
	char origin;
	char dest;
	int weight;
};

struct Vectype{
	char origin;
	char dest;
	int weight;
};

class Graph
{

	//
	// You are required to implement the data structures for the graph. Two representations
	// you will be familiar with are adjaceny list and adjacency matrix.
	// You can choose to go with any representation you wish.
	//

public:
	//
	// To get you started, we have written the definitions for both adjacency list
	// and matrix. You can uncomment whichever one you like. You are also free to change
	// the data structure to your liking. HOWEVER:
	// MAKE SURE YOU DO NOT CHANGE NAME FROM 'graph' OTHERWISE THE TESTS WILL FAIL.
	//
	// Matrix:
	// Making a vector of struct for adjacency matrix is an overkill. The indexes already serve as src and dest so why add them again. Only add int weights. Helper function can simply convert matrix indexes to origin and dest chars
	vector<vector<int>> graph;
	vector< vector<Vectype> > Kruskal_graph; // for the Kruskal algorithm
	//
	// List:
	//vector<list<Edge *>> graph;
	//
	int size = 0; // serves as number of nodes in the graph
	int connections = 0; // number of edges in graph
	bool connected = false; // connected check
	bool Kruskal_connected = false; // Kruskal_connected check
	Graph(string filename);

	void addEdge(char start, char end, int weight);
	string display(); // displays the graph
	bool Reachable(char start, char dest);
	int Prims();
	int Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree weight
	int Dijkstra(char start, char dest);
	//
	// Add any helper function definitions here...
	int Get_index(char data); // City to Index Helper
	char Get_Char(int data); // Index to City Helper
	void Depth_First(int start, int end, bool *visited);

	bool Kruskal_Reachable(char start, char end); // For the Kruscal Algorithm
	void Kruskal_Depth_First(int start, int end, bool *visited);
	//
	// We encourage you to make a helper function that can easily translate a city name to its
	// index.
	// ...
	//
};

#endif
