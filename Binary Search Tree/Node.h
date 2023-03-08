#pragma once
class Node {
	public:
		int key;
		Node* left;
		Node* right;
		Node* parent;
		Node(int key);
		~Node();
};