#include <iostream>

#include "graph.hpp"

int main()
{
  Graph graph{};

  graph.addNode("A");
  graph.addNode("B");
  graph.addNode("C");
  graph.addNode("D");
  graph.addNode("E");
  graph.addNode("F");
  graph.addNode("G");
  graph.addNode("H");
  graph.addNode("I");
  graph.addNode("J");
  graph.addNode("K");

  graph.addEdge("A", "B", 1);
  graph.addEdge("B", "C", 1);
  graph.addEdge("B", "D", 1);
  graph.addEdge("B", "E", 1);
  graph.addEdge("D", "E", 1);
  graph.addEdge("D", "F", 1);
  graph.addEdge("E", "H", 1);
  graph.addEdge("F", "G", 1);
  graph.addEdge("I", "J", 1);
  graph.addEdge("J", "I", 1);
  graph.addEdge("J", "K", 1);
  graph.addEdge("K", "I", 1);

  std::cout << "Graph size: " << graph.size() << "\n";
  auto aAdj = graph.getNeighbours("A");
  auto bAdj = graph.getNeighbours("B");
  auto cAdj = graph.getNeighbours("C");
  auto dAdj = graph.getNeighbours("D");

  std::cout << "Nodes adj to A: ";
  for(auto node : aAdj)
  {
    std::cout << node.second.lock()->name << ", ";
  }

  std::cout << "\nNodes adj to B: ";
  for(auto node : bAdj)
  {
    std::cout << node.second.lock()->name << ", ";
  }

  std::cout << "\nNodes adj to C: ";
  for(auto node : cAdj)
  {
    std::cout << node.second.lock()->name << ", ";
  }

  std::cout << "\nNodes adj to D: ";
  for(auto node : dAdj)
  {
    std::cout << node.second.lock()->name << ", ";
  }

  std::cout << "\nDFS:\n";
  graph.dfs_visit("A", [](auto& node) { std::cout << node.name << " "; });
  std::cout << "\n";
  graph.dfs_visit("I", [](auto& node) { std::cout << node.name << " "; });

  std::cout << "\nBFS:\n";
  graph.bfs_visit("A", [](auto& node) { std::cout << node.name << " "; });
  std::cout << "\n";
  graph.bfs_visit("I", [](auto& node) { std::cout << node.name << " "; });

  std::cout << "\n";

  return 0;
}