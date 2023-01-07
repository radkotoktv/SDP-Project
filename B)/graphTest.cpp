#include <iostream>
#include <vector>

struct Edge {
  int to;
  int weight;
};

void printGraph(std::vector<Edge>* graph, int vertices){
	for(std::size_t i = 0; i < vertices; ++i){
		std::cout << "Vertex " << i << " has edges to: ";
		for(const Edge& e: graph[i]){
			std::cout << e.to << " (weight " << e.weight << ") ";
		}
		std::cout << std::endl;
	}
}

int main() {
	std::vector<Edge> adj_list[10];

	adj_list[0].push_back({1, 1});
	adj_list[1].push_back({2, 1});
	adj_list[2].push_back({0, 1});
	adj_list[5].push_back({1, 10});
	adj_list[1].push_back({4, 3});
	printGraph(adj_list, 10);
}
