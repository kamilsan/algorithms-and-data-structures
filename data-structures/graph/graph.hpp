#pragma once

#include <vector>
#include <string>
#include <exception>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>

class Graph
{
public:
  struct Node
  {
    Node(const std::string& name): name(name) {}

    std::string name;
    std::vector<std::pair<float, std::weak_ptr<Node>>> adjacentNodes;
  };

  Graph() = default;

  void addNode(const std::string& name);
  void addEdge(const std::string& from, const std::string& to, float weight);

  std::vector<std::pair<float, std::weak_ptr<Node>>>
  getNeighbours(const std::string& name) const;
  void dfs_visit(const std::string& name, std::function<void(const Node&)> func) const;
  void bfs_visit(const std::string& name, std::function<void(const Node&)> func) const;
  size_t size() const;

private:
  std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;

  void dfsVisitImpl(std::shared_ptr<Node> node, std::function<void(const Node&)> func, 
    std::unordered_set<std::shared_ptr<Node>>& visited) const;
};

void Graph::addNode(const std::string& name)
{
  auto it = nodes_.find(name);
  if(it != nodes_.end())
    throw std::runtime_error("Node already exists!");

  auto newNode = std::make_shared<Node>(name);
  nodes_.insert(std::make_pair(name, std::move(newNode)));
}

void Graph::addEdge(const std::string& from, const std::string& to, float weight)
{
  auto itFrom = nodes_.find(from);
  auto itTo = nodes_.find(to);
  if(itFrom == nodes_.end() || itTo == nodes_.end())
    throw std::runtime_error("Node does not exists!");

  itFrom->second->adjacentNodes.push_back(std::make_pair(weight, itTo->second));
}

std::vector<std::pair<float, std::weak_ptr<Graph::Node>>>
Graph::getNeighbours(const std::string& name) const
{
  auto it = nodes_.find(name);
  if(it == nodes_.end())
    throw std::runtime_error("Node does not exist!");
  return it->second->adjacentNodes;
}

void Graph::dfs_visit(const std::string& name, std::function<void(const Node&)> func) const
{
  std::unordered_set<std::shared_ptr<Node>> visited;
  auto it = nodes_.find(name);
  if(it == nodes_.end())
    throw std::runtime_error("Node does not exist!");
  dfsVisitImpl(it->second, func, visited);
}

void Graph::dfsVisitImpl(std::shared_ptr<Node> node, std::function<void(const Node&)> func, 
  std::unordered_set<std::shared_ptr<Node>>& visited) const
{
  if(visited.find(node) != visited.end())
    return;

  func(*node);
  visited.insert(node);
  for(auto adj : node->adjacentNodes)
  {
    dfsVisitImpl(adj.second.lock(), func, visited);
  }
}

void Graph::bfs_visit(const std::string& name, std::function<void(const Node&)> func) const
{
  auto it = nodes_.find(name);
  if(it == nodes_.end())
    throw std::runtime_error("Node does not exist!");
  
  std::unordered_set<std::shared_ptr<Node>> discovered;
  std::queue<std::shared_ptr<Node>> q;

  q.push(it->second);
  discovered.insert(it->second);
  while(!q.empty())
  {
    auto node = q.front();
    q.pop();
    func(*node);

    for(auto adj : node->adjacentNodes)
    {
      auto ptr = adj.second.lock();
      if(discovered.find(ptr) == discovered.end())
      {
        q.push(ptr);
        discovered.insert(ptr);
      }
    }
  }
}

size_t Graph::size() const
{
  return nodes_.size();
}
