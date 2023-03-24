#include <iostream>
#include "MyClasses.h"
#include "Funcs.h"
#include "externs.h"
#include <chrono>
int open_node_ldfs(std::vector<Node*>& perifer, int limit) {
	Node* this_node;
	while (!perifer.empty()) {
		this_node = perifer.back();
		while (nodes.back() != this_node) {
			delete nodes.back();
			nodes.pop_back();
		}
		if (this_node->finish())
			return 1;
		else {
			perifer.pop_back();
			if (this_node->get_depth() < limit) {
				this_node->create_new_nodes(perifer);
			}
			else {
				bad_leaf_solution++;
				delete this_node;
				nodes.pop_back();
			}

		}
	}
	return 0;
}
void ldfs(int* first_state) {
	std::vector<Node*> perifer;
	auto start = std::chrono::high_resolution_clock::now();
	Node* n = new Node(first_state, NULL, -1, 0);
	nodes.push_back(n);
	states_ldfs++;
	perifer.push_back(n);
	std::cout << "___LDFS___\n";
	int res = open_node_ldfs(perifer, limit);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Duration in milisec: " << (double)duration.count() / 1000;
	if (res) {
		std::cout << "\nSuccess!\n";

		std::cout << "Iterations to achieve the goal: " << perifer.back()->get_depth() << "; Bad solutions (leaves of the tree without solution): " << bad_leaf_solution << "; Total amount of seen states: " <<
			states_ldfs << "; States in memory: " << nodes.size() << std::endl;
		/*perifer.back()->show_parent_state();*/
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				std::cout << nodes[0]->get_state()[j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				std::cout << nodes.back()->get_state()[j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		/*perifer.back()->write_file_parent_state();*/

	}
	else {
		std::cout << "\nNot found((\n";
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				std::cout << nodes[0]->get_state()[j][k] << " ";
			}
			std::cout << std::endl;
		}
	}
	for (int i = nodes.size(); i > 0; --i) {
		delete nodes[i - 1];
	}
	states_ldfs = 0;
	bad_leaf_solution = 0;
	nodes.clear();
}









int open_node_rbfs(std::vector<Node_rbfs*>& perifer, int best_num) {
	Node_rbfs* this_node;
	int this_node_num;
	int last_node_num;
	int best_on_level;
	while (!perifer.empty()) {
		best_on_level = perifer.size() - 1;
		this_node_num = best_num;
		this_node = perifer[best_num];
		if (this_node->finish())
			return 1;
		perifer.erase(perifer.begin() + this_node_num);
		int children_nodes = this_node->create_new_nodes(perifer);
		if (children_nodes == 0) {
			closed.push_back(this_node);
			int this_depth = this_node->get_depth();
			while (!perifer.empty() && perifer.back()->get_depth() >= this_depth) {
				perifer.pop_back();
			}
			while (!nodes_rbfs.empty() && nodes_rbfs.back()->get_depth() >= this_depth) {
				if (nodes_rbfs.back() != this_node)
					delete nodes_rbfs.back();
				nodes_rbfs.pop_back();
			}
			perifer.push_back(this_node->get_parent_node());
			best_num = perifer.size() - 1;
			if (perifer.back()->get_parent_node() == NULL)
				perifer.pop_back();
		}
		else {
			for (int i = best_on_level + 1; i < perifer.size(); ++i) {
				if (perifer[i]->get_result() <= perifer[best_on_level]->get_result())
					best_on_level = i;
			}
			int best_on_level_result = perifer[best_on_level]->get_result();
			int new_best = perifer.size() - 1;
			for (int i = new_best - 1; i > -1; --i) {
				if (perifer[i]->get_result() < perifer[new_best]->get_result())
					new_best = i;
			}
			best_num = new_best;
			if (best_on_level != new_best) {
				int max_level = perifer[new_best]->get_depth();
				Node_rbfs* tmp_node = this_node;
				while (tmp_node->get_depth() > max_level) {
					if (tmp_node->get_parent_node() != NULL)
						tmp_node = tmp_node->get_parent_node();
				}
				while (!perifer.empty() && perifer.back()->get_depth() > max_level) {
					perifer.pop_back();
				}
				while (nodes_rbfs.back()->get_depth() > max_level) {
					delete nodes_rbfs.back();
					nodes_rbfs.pop_back();
				}if (tmp_node->get_parent_node() != NULL) {
					tmp_node->set_result(best_on_level_result);
					perifer.push_back(tmp_node);
				}
			}
		}
	}
	return 0;
}
void rbfs(int* first_state) {
	std::vector<Node_rbfs*> perifer;
	int best_num = 0;
	auto start = std::chrono::high_resolution_clock::now();
	Node_rbfs* n = new Node_rbfs(first_state, NULL, -1, 0);
	nodes_rbfs.push_back(n);
	states_rbfs++;
	perifer.push_back(n);
	std::cout << "___RBFS___\n";
	int res = open_node_rbfs(perifer, best_num);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Duration in milisec: " << (double)duration.count() / 1000;
	if (res) {
		std::cout << "\nSuccess!\n";
		std::cout << "Iterations to achieve the goal: " << perifer.back()->get_depth() << /*"; Bad solutions (leaves of the tree without solution): " << bad_leaf_solution <<*/
			"; Total amount of seen states: " <<
			states_rbfs << "; States in memory: " << nodes_rbfs.size() << std::endl;
		/*perifer.back()->show_parent_state();*/
		/*perifer.back()->write_file_parent_state();*/
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				std::cout << nodes_rbfs[0]->get_state()[j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				std::cout << perifer.back()->get_state()[j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "\nNot found((\n";
	}
	for (int i = nodes_rbfs.size(); i > 0; --i) {
		delete nodes_rbfs[i - 1];
	}
	/*for (int i = closed.size(); i > 0; --i) {
		delete closed[i - 1];
	}*/
}