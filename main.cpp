#include <iostream>
#include <vector>
#include "MyClasses.h"
#include "externs.h"
#include "Funcs.h"
#include <chrono>
std::vector<Node*> nodes;
long long states_ldfs = 0;
long long bad_leaf_solution = 0;
std::vector<Node_rbfs*> nodes_rbfs;
std::vector<Node_rbfs*> closed;
long long states_rbfs = 0;
using namespace std::chrono_literals;
int limit = 22;

int main() {
	/*int first_state[9]={1, 2, 5, 6, 3, 4, 0, 7, 8};*/
	int first_state[9] = { 8,1,4,0,7,2,3,6,5 };
	/*int first_state[9] = {4, 2, 5, 0, 1, 8, 6, 3, 7};*/
	/*int first_state[9] = { 7,2,0,1,3,4,8,6,5 };*/
	/*int first_state[9] = { 3,8,4,5,2,0,7,6,1 };*/
	/*int first_state[9] = { 0,2,1,3,4,5,6,7,8 };*/    //no solution

	ldfs(first_state);
	rbfs(first_state);
	return 0;
}