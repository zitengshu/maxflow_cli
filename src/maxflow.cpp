#include <iostream>
#include "graph.hpp"

int main() {
    Graph<int> g(6);
    g.AddLink(0, 1, 16); 
	g.AddLink(0, 2, 13); 
	g.AddLink(1, 2, 10); 
	g.AddLink(1, 3, 12); 
	g.AddLink(2, 4, 14); 
	g.AddLink(3, 2, 9); 
	g.AddLink(3, 5, 20); 
	g.AddLink(4, 3, 7); 
	g.AddLink(4, 5, 4); 

    std::cout << "Max Flow: " << g.MaxFlow(0, 5) << std::endl;
	auto adj = g.GetLinks();

	for (int i=0; i < adj.size(); i++) {
		for (auto &link: adj[i]) {
			std::cout << i << "->" << link.v << ": " << link.flow << std::endl;
		}
	}
    return 0;
}