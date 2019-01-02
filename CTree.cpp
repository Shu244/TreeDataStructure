/*
 * Author: Shuhao Lai
 * JHED: slai16
 */
#include "CTree.h"


//Defines << operator for CTree objects.
std::ostream& operator<<(std::ostream& os, CTree& rt)
{
	os << rt.toString();
	return os;
}
//Constructor for CTree class.
CTree::CTree(char ch)
{
	data = ch;
	kids = nullptr;
	sibs = nullptr;
	prev = nullptr;
}
// clear siblings to right and children and this node
CTree::~CTree()
{
	if (sibs != nullptr)
		clear_section(sibs);
	if (kids != nullptr)
		clear_section(kids);
}
//^ operator to do the same thing as addChild
CTree& CTree::operator^(CTree& rt)
{
	addChild(&rt);
	return *this;
}
// siblings and children must be unique, return true if added, false otherwise
bool CTree::addChild(char ch)
{
	CTree * child = new CTree(ch);
	bool added = addChild(child);
	if(added)
		return true;
	else
		delete child;
	return false;
}
// add tree root for better building, root should have null prev and sibs
// returns false on any type of failure, including invalid root
bool CTree::addChild(CTree *root)
{
	if(root == this) //Cannot add itself.
			return false;
	if (root->prev != nullptr && root->sibs != nullptr)
	{
		//delete root;
		return false;
	}
	CTree * current = kids;
	if (current == nullptr)
	{
		kids = root;
		root->prev = this;
		return true;
	}
	do
	{
		if (root->data < current->data)//Checks to see if data can be inserted in current position.
		{
			root->sibs = current;
			root->prev = current->prev;
			if (current->prev->kids == current) //Checks to see if previous node is a parent.
				current->prev->kids = root;
			else
				current->prev->sibs = root;
			current->prev = root;
			return true;
		}
		else if (root->data == current->data)//Checks to see if the data is unique.
		{
			//delete root;
			return false;
		}
		else if (!current->sibs)//Checks to see if data should be added as the last sibling.
		{
			current->sibs = root;
			root->prev = current;
			return true;
		}
	} while ((current = current->sibs));
	return false; //Never reaches this
}

// Returns all characters from the tree separated by newlines, including at the end
std::string CTree::toString()
{
	std::string all;
	toString_helper(this, all);
	return all;
}

// these should only be called from addChild, and have the same restrictions
// the root of a tree should never have any siblings
// returns false on any type of failure, including invalid root
bool CTree::addSibling(char ch)
{
	if (prev == nullptr)
		return false;
	return prev->addChild(ch);
}
bool CTree::addSibling(CTree *root)
{
	if (prev == nullptr || root == this)
	{
		//delete root;
		return false;
	}
	return prev->addChild(root);
}
//Helps the toString function recurse through tree.
void CTree::toString_helper(CTree * node, std::string & all)
{
	std::string temp(1, node->data);
	all += (temp + "\n");
	if (node->kids != nullptr)
		toString_helper(node->kids, all);
	if (node->sibs != nullptr)
		toString_helper(node->sibs, all);
}
//Helps the destructor recurse through tree.
void CTree::clear_section(CTree * node)
{
	if (node->sibs != nullptr)
		clear_section(node->sibs);
	if (node->kids != nullptr)
		clear_section(node->kids);

	CTree * previous = node->prev;
	bool parent = false;
	if (previous->kids == node)
		parent = true;
	if (parent)
		previous->kids = nullptr;
	else
		previous->sibs = nullptr;

	delete node;
}
