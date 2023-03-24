#pragma once
#include <vector>
enum actions {
	empty_right = 0,
	empty_left = 1,
	empty_up = 2,
	empty_down = 3
};
class Node {
	Node* parent_node;
protected:
	int** state;
	int row_of_zero;
	int column_of_zero;
	int action;
	int depth;
public:
	int state_code;
	Node(int* st, Node* parent, int act, int d);
	~Node();
	int** get_state() { return state; }
	virtual Node* get_parent_node() { return parent_node; }
	int get_action() { return action; }
	int get_depth() { return depth; }
	virtual void create_new_nodes(std::vector<Node*>& perifer);
	bool finish();
	virtual void show_parent_state();
	void write_file_parent_state();
private:
	void new_node(int* new_st, int action, std::vector<Node*>& perifer);
};



class Node_rbfs : public Node {
	Node_rbfs* parent_node;
	int own_funcs;
	int total_funcs;
	int result;
public:
	Node_rbfs(int* st, Node_rbfs* parent, int act, int d);
	Node_rbfs* get_parent_node() { return parent_node; }
	int get_own_funcs() { return own_funcs; }
	int get_total_funcs() { return total_funcs; }
	int get_result() { return result; }
	int create_new_nodes(std::vector<Node_rbfs*>& perifer);
	void set_result(int res) { result = res; }
	void show_parent_state();
private:
	int count_own_funcs();
	int count_total_funcs();
	void new_node(int* new_st, int action, int& amount, std::vector<Node_rbfs*>& perifer);
};