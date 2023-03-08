#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(int k) {
	key = k;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

Node::~Node() {}