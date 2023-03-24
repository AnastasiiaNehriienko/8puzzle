#pragma once
#include <vector>
#include "MyClasses.h"
extern std::vector<Node*> nodes;
extern long long states_ldfs;
extern long long bad_leaf_solution;
extern int limit;


extern std::vector<Node_rbfs*> nodes_rbfs;
extern std::vector<Node_rbfs*> closed;
extern long long states_rbfs;