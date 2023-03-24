#pragma once
#include <vector>
#include "MyClasses.h"
int open_node_ldfs(std::vector<Node*>& perifer, int limit);
void ldfs(int* first_state);



int open_node_rbfs(std::vector<Node_rbfs*>& perifer, int best_num);
void rbfs(int* first_state);