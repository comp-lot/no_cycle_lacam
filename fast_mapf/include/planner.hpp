#pragma once

#include "dist_table.hpp"
#include "graph.hpp"
#include "instance.hpp"
#include "utils.hpp"

struct Constraint {
  std::vector<int> who;
  Vertices where;
  const int depth;
  Constraint() : who(std::vector<int>()), where(Vertices()), depth(0) {}
  Constraint(Constraint* parent, int i, Vertex* v)
      : who(parent->who), where(parent->where), depth(parent->depth + 1)
  {
    who.push_back(i);
    where.push_back(v);
  }
  ~Constraint() {}
};

struct Node {
  const Config C;
  const float cost;
  const std::string id;
  Node* parent;
  const int depth;

  // for low-level search
  const std::vector<int> order;
  std::queue<Constraint*> search_tree;

  Node(Config _C, const DistTable& dist_table, std::string _id, Node* _parent);
  ~Node();
};
using Nodes = std::vector<Node*>;

struct Agent {
  int id;
  Vertex* v_now;   // current location
  Vertex* v_next;  // next location
  Agent(int _id) : id(_id), v_now(nullptr), v_next(nullptr) {}
};
using Agents = std::vector<Agent*>;

float get_cost(Config& C, const DistTable& dist_table);
std::vector<int> get_order(Config& C, const DistTable& dist_table);
std::string get_id(Config& C);
Solution solve(const Instance& ins);
bool funcPIBT(Agent* ai, Agent* aj, Agents& occupied_now, Agents& occupied_next,
              const DistTable& dist_table);
