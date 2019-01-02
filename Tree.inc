/*
 * Author: Shuhao Lai
 * JHED: slai16
 */
//Tree.inc
//#include "Tree.h"

//Defines << operator for Tree objects.
template<typename T>
std::ostream& operator<<(std::ostream& os, Tree<T>& rt)
{
	os << rt.toString();
	return os;
}
//Constructor for Tree class
template<typename T>
Tree<T>::Tree(T info)
{
	data = info;
	kids = nullptr;
	sibs = nullptr;
	prev = nullptr;
}
// clear siblings to right and children and this node
template<typename T>
Tree<T>::~Tree()
{
	if (!(sibs == nullptr))
		clear_section (sibs);
	if (!(kids == nullptr))
		clear_section (kids);
}

//^ operator to do the same thing as addChild
template<typename T>
Tree<T>& Tree<T>::operator^(Tree<T>& rt)
{
	addChild(&rt);
	return *this;
}

// siblings and children must be unique, return true if added, false otherwise
template<typename T>
bool Tree<T>::addChild(T info)
{
	Tree < T > * child = new Tree(info);
	bool added = addChild(child);
	if(added)
		return true;
	else
		delete child;
	return false;
}
// add tree root for better building, root should have null prev and sibs
// returns false on any type of failure, including invalid root
template<typename T>
bool Tree<T>::addChild(Tree<T> *root)
{
	if(root == this) //Cannot add itself. 
		return false;
	if (!(root->prev == nullptr) && !(root->sibs == nullptr))
	{
		//delete root;
		return false;
	}
	
	Tree < T > *current = kids;
	if (current == nullptr)
	{
		kids = root;
		root->prev = this;
		return true;
	}
	
	do
	{
		if (root->data < current->data) //Checks to see if data can be inserted in current position.
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
		else if (root->data == current->data) //Checks to see if the data is unique.
		{
			//delete root;
			return false;
		}
		else if (!current->sibs) //Checks to see if data should be added as the last sibling.
		{
			current->sibs = root;
			root->prev = current;
			return true;
		}
	} while ((current = current->sibs));
	return false; //Never reaches this
}
// Returns all characters from the tree separated by newlines, including at the end
template<typename T>
std::string Tree<T>::toString()
{
	std::string all;
	toString_helper(this, all);
	return all;
}
// these should only be called from addChild, and have the same restrictions
// the root of a tree should never have any siblings
// returns false on any type of failure, including invalid root
template<typename T>
bool Tree<T>::addSibling(T info)
{
	if (prev == nullptr)
		return false;
	return prev->addChild(info);
}
template<typename T>
bool Tree<T>::addSibling(Tree<T> *root)
{
	if (prev == nullptr || root == this)
	{
		//delete root;
		return false;
	}
	return prev->addChild(root);
}
//Helps the toString function recurse through tree.
template<typename T>
void Tree<T>::toString_helper(Tree<T> * node, std::string & all)
{
	std::stringstream ss;
	ss << node->data;
	std::string dataStr(ss.str());
	all += (dataStr + "\n");
	if (!(node->kids == nullptr))
		toString_helper(node->kids, all);
	if (!(node->sibs == nullptr))
		toString_helper(node->sibs, all);
}
//Helps the destructor recurse through tree.
template<typename T>
void Tree<T>::clear_section(Tree<T> * node)
{
	if (!(node->sibs == nullptr))
		clear_section(node->sibs);
	if (!(node->kids == nullptr))
		clear_section(node->kids);

	//std::cout << node->data << std::endl;
	Tree < T > *previous = node->prev;
	bool parent = false;
	if (previous->kids == node)
		parent = true;
	if (parent)
		previous->kids = nullptr;
	else
		previous->sibs = nullptr;

	delete node;

}
