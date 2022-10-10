#include <iostream>
#include "graph.hpp"
#include <fstream>
#include <limits>
#include <iomanip>
#include <nlohmann/json.hpp>

#define MAX_CAP 0x3FFFFFFF

using json = nlohmann::json;

int main(int argc, char *argv[]) {
	std::ifstream f(argv[1]);
	json data = json::parse(f);

	int node_num = data["node_num"].get<int>();
	auto source_nodes = data["source_nodes"].get<std::vector<int>>();
	auto sink_nodes = data["sink_nodes"].get<std::vector<int>>();

	int source = node_num;
	int sink = source + 1;

  Graph<int> g(node_num+2);
	for (auto &[u, u_adj] : data["nodes"].items()) {
		for (auto &[v, cap] : u_adj.items()) {
			g.AddLink(std::stoi(u), std::stoi(v), cap);
		}
	}
	for (auto &s : source_nodes) {
		g.AddLink(source, s, MAX_CAP);
	}
	for (auto &t : sink_nodes) {
		g.AddLink(t, sink, MAX_CAP);
	}
	int max_flow = g.MaxFlow(source, sink);
  std::cout << "Max Flow: " << max_flow << std::endl;
	auto adj = g.GetLinks();

	json res = {{"node_num", node_num}, {"source_nodes", source_nodes}, {"sink_nodes", sink_nodes}, {"max_flow", max_flow}};
	for (int i=0; i < node_num; i++) {
		std::string u = std::to_string(i);
		for (auto &link: adj[i]) {
			if (link.v < node_num) {
				res["nodes"][u][std::to_string(link.v)] = link.flow;
			}
		}
	}
	std::ofstream out(argv[2]);
	out << std::setw(4) << res << std::endl;
    return 0;
}