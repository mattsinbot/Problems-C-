#include <iostream> // to use cout
#include <vector>   // to use vector
#include <queue>    // to use queue
#include <utility>  // to use pair

using namespace std;

// Add edge to the graph
void add_edge(vector<pair<int,int>> adj_weighted[], int src, pair<int,int> dest_cost){
	adj_weighted[src].push_back(dest_cost);
}

// Check if a vertex already exists in a given path
bool not_visited(vector<pair<int,int>> path, pair<int,int> weighted_edge){
	for (size_t i = 0; i < path.size(); i++){
		if (path[i].first == weighted_edge.first){
			return false;
		}
	}
	return true;
}

// Print a valid path from start to destination
void print_valid_path(vector<pair<int,int>> valid_path){
	int path_cost = 0;
	path_cost += valid_path[0].second;

	cout << valid_path[0].first;
	for (size_t i = 1; i < valid_path.size(); i++){
		cout << "->";
		cout << valid_path[i].first;
		path_cost += valid_path[i].second;
	}
	cout << "\tpath cost: " << path_cost << endl;
}

// Find all paths
void find_all_paths(vector<pair<int,int>> adj[], int src, int dest, int num_vertex){
	queue<vector<pair<int,int> >> to_explore;

	vector<pair<int,int>> path;

	pair<int,int> src_edge;
	src_edge = make_pair(src, 0);
	path.push_back(src_edge);

	to_explore.push(path);

	while(!to_explore.empty()){
//		cout << "size of to_explore: " << to_explore.size() << endl;
		vector<pair<int,int>> current_path = to_explore.front();
		to_explore.pop();

		// check if the last element of the current_path is the
		// desired destination, then continue.
		int path_last_element = current_path[current_path.size() - 1].first;
		if (path_last_element == dest){
			print_valid_path(current_path);
			continue;
		}

		// Extend the path from the path_last_element
		for (size_t i=0; i < adj[path_last_element].size(); i++){
			if (not_visited(current_path, adj[path_last_element][i])){
				vector<pair<int,int>> extended_path(current_path);
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
	vector<pair<int,int>> adj_weighted[num_vertex];

	// Define the edges in the graph
	pair <int,int> edge1, edge2, edge3, edge4, edge5, edge6;

	edge1 = make_pair(0, 5); edge2 = make_pair(2, 3);
	edge3 = make_pair(1, 4); edge4 = make_pair(1, 6);
	edge5 = make_pair(3, 2); edge6 = make_pair(3, 2);

	add_edge(adj_weighted, 2, edge1);
	add_edge(adj_weighted, 0, edge2);
	add_edge(adj_weighted, 2, edge3);
	add_edge(adj_weighted, 0, edge4);
	add_edge(adj_weighted, 0, edge5);
	add_edge(adj_weighted, 1, edge6);

	cout << "find all paths, from node " << src << " to " << dest << endl;

	// Find all the paths in the graph
	find_all_paths(adj_weighted, src, dest, num_vertex);

	return 0;
}
