#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here.
//

Graph::Graph(string file)
{
	ifstream DataFile(file);
	char n,c;
	int number;
	char src, dest;
	int weight;
	DataFile >> n >> number >> c >> connections; // first four items extracted
	size = number;

	// cout << "n = " <<  number << endl;
	// cout << "c = " << connections << endl;

	// Create a vector of vector here
	vector<vector<int>> store(size, vector<int> (size, 0));
	graph = store;

	vector<vector<Vectype>> K_store (size, vector<Vectype> (size));
	// This only need to be done for Test4
	for(int i=0; i< size; i++)
	{
		for(int j =0; j<size; j++)
		{
			K_store[i][j].origin = Get_Char(i);
			K_store[i][j].dest = Get_Char(j);
			K_store[i][j].weight = 0;
		}
	}
	Kruskal_graph = K_store;
	//matrices have been initialized with all zeros

	// Now read the rest of data
	while(DataFile >> src >> dest >> weight) // Edge data extracted using a while loop
	{
		// store values in table
		addEdge(src, dest, weight);
	}

}

//
// Adds an edge to the graph. Useful when loading the graph from file.
//
void Graph::addEdge(char start, char end, int weight)
{
	graph[Get_index(start)][Get_index(end)] = weight;
	graph[Get_index(end)][Get_index(start)] = weight; // since undirected
}

// Helper Functions
int Graph::Get_index(char data)
{
	int index = int(data) - 65;
	return index;
}
char Graph::Get_Char(int data)
{
	char letter = 65 + data;
	return letter;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in manual.
//
string Graph::display()
{
	string final = "";
	for(int i= 0; i < size; i++)
	{
		for(int j=0; j<size; j++)
		{
			// cout << graph[i][j] << " ";
			if(graph[i][j] != 0)
			{
				string src = string(1, Get_Char(i));
				string dest = string(1, Get_Char(j));
				string weight = to_string(graph[i][j]);

				string temp = "(" + src + "," +  dest + "," + weight + ") ";
				final = final + temp;
			}
		}
	}
	return final;
}

bool Graph::Reachable(char start, char end)
{
	connected = false;
	// First get indexes
	int src = Get_index(start);
	int dest = Get_index(end);
	// Easier way is to traverse the graph using DFS and return true if connection is found. Else return false
	// For that we need a recursive function
	bool visited[size]{false}; // we initialized a visited array so the same node is not visited twice. This is equal to the number of nodes in the graph
	// vector<bool> visited(size, false);
	Depth_First(src, dest, visited);
	// cout << endl;
	if(connected == false)
	{ return false;}
	else{ return true; }

}
// This will traverse the entire graph and set connected marker to true if connection is found
void Graph::Depth_First(int start, int end, bool *visited)
{
	// for(int i =0; i < size; i++)
	// {
	// 	for(int j=0; j < size; j++)
	// 	{
	// 		cout << graph[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	if(graph[start][end] != 0) // everytime we see whether there is an edge between src and dest. Src changes in every recursive call, dest remains same
	{ connected = true; }

	// cout << Get_Char(start) << " " ;

	visited[start] = true; // set that node's index to visited

	// for(int i=0; i< size; i++)
	// {
	// 	cout << visited[i] << " ";
	// }
	// cout << endl;

	for(int i=0; i<size; i++) // for every edge, visit it depth wise
	{
		if(graph[start][i] != 0 && visited[i] == false) // edge exists and node not alredy traversed, visit it
		{
			Depth_First(i, end, visited); // recursive call
		}
	}

}

//
// OPTION 2
// Returns the weight of the MST using Prims algorithm
// Not done
int Graph::Prims()
{
	// TODO
	return 0;
}

//
// OPTION 1
// Returns the weight of the MST using Kruskal algorithm
//
int Graph::Kruskal()
{
	// For the Kruskal Algortihm, we need to first list all the edges from the adjacency matrix and then sort them in ascending order. We can loop through the adjacency matrix for that.
	// Then once we have the edges, we will go through each edge and see if the src and dest are connected already. We can use Reachable function for this but with some alterations.
	// If they are not connected, then we add an edge between them. Else, we do not add an edge.
	vector<vector<int>> temp = graph;
	vector<Vectype> tracker(connections * 2);


	for(int x=0; x < (connections*2); x ++ )
	{
		int min = 10000; // out value for infinity
		char src;
		char dst;
		for(int i=0; i< size; i++)
		{
			for(int j=0; j<size; j++)
			{
				if(temp[i][j] <= min && temp[i][j] != 0)
				{
					min = temp[i][j];
					src = Get_Char(i);
					dst = Get_Char(j);
				}
			}
		}
		tracker[x].origin = src;
		tracker[x].dest = dst;
		tracker[x].weight = min;
		temp[Get_index(src)][Get_index(dst)] = 0;
}
	// for(int i=0; i< tracker.size(); i++)
	// {
	// cout << tracker[i].origin << tracker[i].dest << tracker[i].weight << endl;
	// }

	// So far we have been able to maintain a list successfully in ascending order which have all the edges.
	// Now iterate thtough this list and find Reachability
	for(int i=0; i<tracker.size(); i++)
	{
		char src = tracker[i].origin;
		char dst = tracker[i].dest;
		int w = tracker[i].weight;
		if(Kruskal_Reachable(src, dst) == false)
		{
			Kruskal_graph[Get_index(src)][Get_index(dst)].weight = w;
			Kruskal_graph[Get_index(dst)][Get_index(src)].weight = w;
		}
	}
	// for(int i =0; i< size; i++)
	// {
	// 	for(int j=0; j<size; j++)
	// 	{
	// 		cout << Kruskal_graph[i][j].weight << " ";
	// 	}
	// 	cout << endl;
	// }

	// We get the correct Minimum spanning tree. Now we only need to add all the weights and divide by 2 (since undirected)
	int sum = 0;
	for(int i =0; i< size; i++)
	{
		for(int j=0; j<size; j++)
		{
			sum = Kruskal_graph[i][j].weight + sum;
		}
	}
	// cout << sum/2 << endl;
	return sum/2;
}

bool Graph::Kruskal_Reachable(char start, char end)
{
	Kruskal_connected = false;
	// First get indexes
	int src = Get_index(start);
	int dest = Get_index(end);
	// Easier way is to traverse the graph using DFS and return true if connection is found. Else return false
	// For that we need a recursive function
	bool visited[size]{false}; // we initialized a visited array so the same node is not visited twice. This is equal to the number of nodes in the graph
	// vector<bool> visited(size, false);
	// cout << endl;
	Kruskal_Depth_First(src, dest, visited);
	if(Kruskal_connected == false)
	{ return false;}
	else{ return true; }
}

void Graph::Kruskal_Depth_First(int start, int end, bool *visited)
{
	if(Kruskal_graph[start][end].weight != 0) // everytime we see whether there is an edge between src and dest. Src changes in every recursive call, dest remains same
	{ Kruskal_connected = true; }

	visited[start] = true; // set that node's index to visited

	for(int i=0; i<size; i++) // for every edge, visit it depth wise
	{
		if(Kruskal_graph[start][i].weight != 0 && visited[i] == false) // edge exists and node not alredy traversed, visit it
		{
			Kruskal_Depth_First(i, end, visited);
		}
	}

}

//
// Returns the weight of shortest path between start and end.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	// We need the shortest cost between start and dest char. If no connection exists, return -1. For that we will use Reachable function
	if(Reachable(start, dest) == false)
	{ return -1; }
	else{
		int src = Get_index(start);
		int destin = Get_index(dest);

		// Rough Sketch
		// We have the adjacency matrix. We need to make a new table that has shortest costs from start to each other node
		// since we have (size)= numbe of nodes, lets make a vector for storing shortest costs
		 vector<int> Shortest (size, 10000); // Since we set initial costs to inf, we use 10000 as our inf for this assignment. It could also be set as inf using maximum int value but any large number will suffice
		// Also set cost of start index to 0. Since self cost is 0
		 Shortest[src] = 0;
		 // This completes initialization of the table

		 // for(int i =0; i<size; i++)
		 // {
			//  cout << Shortest[i] << " ";
		 // }

		 // Now we also need to use another list that stores whether a node is already visited to not.
		  vector<bool> Visited(size, false); // so initially, no vertex will be visited
			// for(int i =0; i<size; i++)
 		 // {
 			//  cout << Visited[i] << " ";
 		 // }

		 // Now, we need to run a loop for all values in the Shortest path table and select the one that has least value is in unvisited
		 for(int i= 0; i< size; i++)
		 {
			 // select the shortest path vertex. In the first iteration, we have src vertex as 0 and all other vertices as 10000.
			 int min = 10000; //taken as a representation of inf again.
			 int index = -1;
			 	for(int j=0; j < size; j++)
				{
						if(Shortest[j] <= min && Visited[j] == false)
						{
							min = Shortest[j]; // set Minimum to Shortest[j] if condition is satified. For the first iteration, src will have shortest distance  = 0
							index = j;
						}
				}
				// Now mark this vertex as the current vartex
				int current_vertex = index;
				// cout << Get_Char(current_vertex) << endl;

				// Now once again, we will run a loop thorugh all the vertices. First thing to check is that does the vertex have an edge with the current current_vertex. Continue if it does
				for (int i =0; i< size; i++)
				{
					if(graph[current_vertex][i] != 0) // Checking if edge exists
					{
						if(Visited[i] == false) // Second thing to check is whether that vertex has not been visited before
						{
							if(Shortest[current_vertex] + graph[current_vertex][i] < Shortest[i] ) // new shortest path found
							{
								Shortest[i] = Shortest[current_vertex] + graph[current_vertex][i];
							}
							else { continue; }
						}
						else
						{ continue; }
					}
					else {continue;}
				}

				// Now that we've completely traversed the current node, add current_vertex to the Visited table
				Visited[current_vertex] = true;

		 }
		 // for(int i=0; i< size; i++)
		 // {
			//  cout << Shortest[i] << " ";
		 // }
		 // cout << endl;
		 // cout << Shortest[destin] << endl;
		 return Shortest[destin];
	}

}

#endif
