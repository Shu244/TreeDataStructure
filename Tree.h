/*
 * Author: Shuhao Lai
 * JHED: slai16
 */
#ifndef _TREE_H
#define _TREE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

// tree of characters, can be used to implement a trie
template<typename T>
class Tree
{
	friend class TreeTest;

	T data;     // the value stored in the tree node

	Tree<T> * kids; // children - pointer to first child of list, maintain order & uniqueness

	Tree<T> * sibs; // siblings - pointer to rest of children list, maintain order & uniqueness
					// this should always be null if the object is the root of a tree

	Tree<T> * prev; // pointer to parent if this is a first child, or left sibling otherwise
					// this should always be null if the object is the root of a tree

public:
	//Defines << operator for Tree objects.
	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, Tree<U>& rt);
	//Constructor for Tree class.
	Tree(T info);

	// clear siblings to right and children and this node
	~Tree();

	//^ operator to do the same thing as addChild
	Tree<T>& operator^(Tree<T>& rt);

	// siblings and children must be unique, return true if added, false otherwise
	bool addChild(T info);

	// add tree root for better building, root should have null prev and sibs
	// returns false on any type of failure, including invalid root
	bool addChild(Tree<T> *root);
	// Returns all characters from the tree separated by newlines, including at the end
	std::string toString();

private:
	// these should only be called from addChild, and have the same restrictions
	// the root of a tree should never have any siblings
	// returns false on any type of failure, including invalid root
	bool addSibling(T info);
	bool addSibling(Tree<T> *root);
	//Helps the toString function recurse through tree.
	void toString_helper(Tree<T> * node, std::string & all);
	//Helps the destructor recurse through tree.
	void clear_section(Tree<T> * node);

};

#include "Tree.inc"

#endif
