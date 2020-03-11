#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Add edge to the graph
void add_edge(vector<int> adj[], int src, int dest){
	adj[src].push_back(dest);
}

// Check if a vertex already exists in a given path
bool not_visited(vector<int> path, int vertex){
	for (size_t i = 0; i < path.size(); i++){
		if (path[i] == vertex){
			return false;
		}
	}
	return true;
}

// Print a valid path from start to destination
void print_valid_path(vector<int> valid_path){
	cout << valid_path[0];
	for (size_t i = 1; i < valid_path.size(); i++){
		cout << "->";
		cout << valid_path[i];
	}
	cout << endl;
}

// Find all paths
void find_all_paths(vector<int> adj[], int src, int dest, int num_vertex){
	queue<vector<int>> to_explore;

	vector<int> path;
	path.push_back(src);

	to_explore.push(path);

	while(!to_explore.empty()){
		vector<int> current_path = to_explore.front();
		to_explore.pop();

		// check if the last element of the current_path is the
		// desired destination, then continue.
		int path_last_element = current_path[current_path.size() - 1];
		if (path_last_element == dest){
			print_valid_path(current_path);
			continue;
		}

		// Extend the path from the path_last_element
		for (size_t i=0; i < adj[path_last_element].size(); i++){
			if (not_visited(current_path, adj[path_last_element][i])){
				vector<int> extended_path(current_path);
				extended_path.push_back(adj[path_last_element][i]);
				to_explore.push(extended_path);
			}
		}
	}
	cout << "All paths were computed" << endl;
}

int main(int argc, char* argv[]){
	// Define source and destination nodes
	int src = 2, dest = 3;

	// Define number of vertices in the graph
	int num_vertex = 4;
	vector<int> adj[num_vertex];

	// Define the edges in the graph
	add_edge(adj, 2, 0);
	add_edge(adj, 0, 2);
	add_edge(adj, 2, 1);
	add_edge(adj, 0, 1);
	add_edge(adj, 0, 3);
	add_edge(adj, 1, 3);

	cout << "find all paths, from node " << src << " to " << dest << endl;

	// Find all the paths in the graph
	find_all_paths(adj, src, dest, num_vertex);

	return 0;
}
