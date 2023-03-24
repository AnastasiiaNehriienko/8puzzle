#include "MyClasses.h"
#include <iostream>
#include <vector>
#include "externs.h"
#include <fstream>
Node::Node(int* st, Node* parent, int act, int d) {
	row_of_zero = -1; column_of_zero = -1;
	state = new int* [3];
	state_code = 0;
	for (int i = 0; i < 3; ++i)
		state[i] = new int[3];
	int st_num = 0;
	int coef = 100000000;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			state[i][j] = st[st_num];
			state_code += st[st_num] * coef;
			if (st[st_num] == 0) {
				row_of_zero = i;
				column_of_zero = j;
			}
			st_num++;
			coef /= 10;
		}
	}
	parent_node = parent;
	action = act;
	depth = d;
}
Node::~Node() {
	for (int i = 0; i < 3; ++i)
		delete[] state[i];
	delete[] state;
}
void Node::create_new_nodes(std::vector<Node*>& perifer) {
	int new_matrix[3][3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			new_matrix[i][j] = state[i][j];
		}
	}
	int new_st[9];
	int new_st_num = 0;
	if (row_of_zero < 2) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero + 1][column_of_zero];
		new_matrix[row_of_zero + 1][column_of_zero] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_down, perifer);
		new_matrix[row_of_zero + 1][column_of_zero] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	if (row_of_zero > 0) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero - 1][column_of_zero];
		new_matrix[row_of_zero - 1][column_of_zero] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_up, perifer);
		new_matrix[row_of_zero - 1][column_of_zero] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	if (column_of_zero < 2) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero][column_of_zero + 1];
		new_matrix[row_of_zero][column_of_zero + 1] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_right, perifer);
		new_matrix[row_of_zero][column_of_zero + 1] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	if (column_of_zero > 0) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero][column_of_zero - 1];
		new_matrix[row_of_zero][column_of_zero - 1] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_left, perifer);
		new_matrix[row_of_zero][column_of_zero - 1] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}

}
void Node::new_node(int* new_st, int action, std::vector<Node*>& perifer) {
	Node* n = new Node(new_st, this, empty_down, depth + 1);
	bool exists = false;
	int i = 0;
	while (!exists && i < nodes.size()) {
		if (n->state_code == nodes[i]->state_code) {
			exists = true;
		}
		i++;
	}
	if (!exists) {
		nodes.push_back(n);
		states_ldfs++;
		perifer.push_back(n);
	}
	else {
		delete n;
	}
}
bool Node::finish() {
	int finish_num = 12345678;
	int res = 0;
	if (state_code == finish_num)
		res = 1;
	return res;
}
void Node::show_parent_state() {
	if (parent_node) {
		parent_node->show_parent_state();
	}
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < 3; ++k) {
			std::cout << state[j][k] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Node::write_file_parent_state() {
	if (parent_node) {
		parent_node->write_file_parent_state();
	}
	std::ofstream file("Nodes_of_res.txt", std::ios::app);
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < 3; ++k) {
			file << state[j][k] << " ";
		}
		file << std::endl;
	}
	file << std::endl;
	file.close();
}




Node_rbfs::Node_rbfs(int* st, Node_rbfs* parent, int act, int d) : Node(st, NULL, act, d) {
	parent_node = parent;
	own_funcs = count_own_funcs();
	total_funcs = count_total_funcs();
	result = total_funcs;
}
int Node_rbfs::count_own_funcs() {
	int h = 0;
	int rows[9];
	int columns[9];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			rows[state[i][j]] = i;
			columns[state[i][j]] = j;
		}
	}
	h = rows[1] + rows[2] + abs(rows[3] - 1) + abs(rows[4] - 1) + abs(rows[5] - 1) + 6 - rows[6] - rows[7] - rows[8] + columns[3] + columns[6] + abs(columns[1] - 1)
		+ abs(columns[4] - 1) + abs(columns[7] - 1) + 6 - columns[2] - columns[5] - columns[8];

	return h;
}
int Node_rbfs::count_total_funcs() {
	if (parent_node != NULL)
		return own_funcs + depth;
	else return own_funcs;
}
int Node_rbfs::create_new_nodes(std::vector<Node_rbfs*>& perifer) {
	int amount = 0;
	int new_matrix[3][3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			new_matrix[i][j] = state[i][j];
		}
	}
	int new_st[9];
	int new_st_num = 0;
	if (row_of_zero < 2) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero + 1][column_of_zero];
		new_matrix[row_of_zero + 1][column_of_zero] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_down, amount, perifer);
		new_matrix[row_of_zero + 1][column_of_zero] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	if (row_of_zero > 0) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero - 1][column_of_zero];
		new_matrix[row_of_zero - 1][column_of_zero] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_up, amount, perifer);
		new_matrix[row_of_zero - 1][column_of_zero] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	if (column_of_zero < 2) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero][column_of_zero + 1];
		new_matrix[row_of_zero][column_of_zero + 1] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_right, amount, perifer);
		new_matrix[row_of_zero][column_of_zero + 1] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	if (column_of_zero > 0) {
		int tmp = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = new_matrix[row_of_zero][column_of_zero - 1];
		new_matrix[row_of_zero][column_of_zero - 1] = tmp;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				new_st[new_st_num] = new_matrix[i][j];
				new_st_num++;
			}
		}
		new_st_num = 0;
		new_node(new_st, empty_left, amount, perifer);
		new_matrix[row_of_zero][column_of_zero - 1] = new_matrix[row_of_zero][column_of_zero];
		new_matrix[row_of_zero][column_of_zero] = tmp;
	}
	return amount;
}

void Node_rbfs::new_node(int* new_st, int action, int& amount, std::vector<Node_rbfs*>& perifer) {
	Node_rbfs* n = new Node_rbfs(new_st, this, empty_down, depth + 1);
	bool exists = false;
	int i = 0;
	while (!exists && i < (int)closed.size()) {
		if (n->state_code == closed[i]->state_code) {
			exists = true;
		}
		i++;
	}
	if (!exists) {
		i = 0;
		while (!exists && i < nodes_rbfs.size()) {
			if (n->state_code == nodes_rbfs[i]->state_code) {
				exists = true;
			}
			i++;
		}
		if (!exists) {
			nodes_rbfs.push_back(n);
			states_rbfs++;
			perifer.push_back(n);
			amount++;
		}
		else {
			delete n;
		}
	}
	else {
		delete n;
	}
}
void Node_rbfs::show_parent_state() {
	if (parent_node) {
		parent_node->show_parent_state();
	}
	for (int j = 0; j < 3; ++j) {
		for (int k = 0; k < 3; ++k) {
			std::cout << state[j][k] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}