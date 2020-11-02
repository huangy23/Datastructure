/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//add here
//from lecture note
Node *Rope::copy_tree(Node *n_current, Node *n_past)
{
	if (n_current == NULL)
	{
		return NULL;
	}
	Node *n_new = new Node();
	n_new->left = copy_tree(n_current->left, n_new);
	n_new->right = copy_tree(n_current->right, n_new);
	n_new->value = n_current->value;
	n_new->weight = n_current->weight;
	n_new->parent = n_past;
	return n_new;
}

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
//from lecture note
rope_iterator &rope_iterator::operator++()
{
	if (ptr_->right != NULL)
	{ // find the leftmost child of the right node
		ptr_ = ptr_->right;
		while (ptr_->left != NULL)
		{
			ptr_ = ptr_->left;
		}
	}
	else
	{ // go upwards along right branches... stop after the first left
		while (ptr_->parent != NULL && ptr_->parent->right == ptr_)
		{
			ptr_ = ptr_->parent;
		}
		ptr_ = ptr_->parent;
	}
	return *this;
	//assert(0 && "rope_iterator operator++ not implemented!");
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const
{
	/*
	if (!root_) return iterator(NULL);
        TreeNode<T> *p = root_;
        while (p->left) p = p->left;
        return iterator(p);
	*/
	if (!root)
	{
		return rope_iterator(nullptr);
	}

	Node *temp = root;
	while (temp->left)
	{
		temp = temp->left;
	}

	return rope_iterator(temp);
	//assert(0 && "rope_iterator begin() not implemented!");
}

Rope::Rope()
{
	size_ = 0;
	root = nullptr;
	//assert(0 && "Rope default constructor not implemented!");
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node *p)
{
	root = p;
	size_ = 0;

	while (p)
	{
		size_ = size_ + p->weight;
		p = p->right;
	}

	//assert(0 && "Rope constructor from Node not implemented!");
}

Rope::~Rope()
{
	this->destroy_tree(root);
	root = nullptr;
	//assert(0 && "Rope destructor not implemented!");
}

Rope::Rope(const Rope &r)
{
	size_ = r.size_;
	root = this->copy_tree(r.root, NULL);
	//assert(0 && "Rope copy constructor not implemented!");
}

//from lecture note
Rope &Rope::operator=(const Rope &r)
{
	if (&r != this)
	{
		this->destroy_tree(root);
		root = this->copy_tree(r.root, NULL);
		size_ = r.size_;
	}
	return *this;
	//assert(0 && "Rope assignment not implemented!");
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char &c) const
{
	if ((i < size_) && (i >= 0))
	{
		Node *temp = root;
		while (!is_leaf(temp))
		{
			if (i < temp->weight)
			{
				temp = temp->left;
			}
			else
			{
				i = i - temp->weight;
				temp = temp->right;
			}
		}
		c = temp->value[i];
		return true;
	}
	return false;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope &r)
{
	Node *new_r = new Node;
	new_r->weight = size_;
	root->parent = new_r;
	new_r->left = root;
	Node *right_child = copy_tree(r.root, nullptr);
	right_child->parent = new_r;
	new_r->right = right_child;
	root = new_r;
	size_ = new_r->weight + r.size_;

	//assert(0 && "Rope concat() not implemented!");
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string &s) const
{
	//clear s
	s.clear();

	//situation return false
	if (!((j >= i) && (size_ > j) && (i >= 0)))
	{
		return false;
	}

	char tmp_charactor;
	//one character if i == j
	if (i == j)
	{
		if (this->index(i, tmp_charactor))
		{
			s += tmp_charactor;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//loop and add charactor from i -> j
		for (signed int a = i; a < j + 1; a++)
		{
			if (this->index(a, tmp_charactor))
			{
				s += tmp_charactor;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	//assert(0 && "Rope report() not implemented!");
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope &Rope::split(int i, Rope &rhs)
{
	std::string one;
	std::string sp1;
	std::string sp2;

	rope_iterator itr = this->begin();
	while (itr != this->end())
	{
		if (!itr.ptr_->value.empty())
		{
			one += itr.ptr_->value;
		}
		itr++;
	}

	for (signed int k = 0; k < i; k++)
	{
		sp1 += one[k];
	}
	for (unsigned int k = i; k < one.size(); k++)
	{
		sp2 += one[k];
	}
	this->destroy_tree(root);
	rhs.destroy_tree(rhs.root);
	Node *temp1 = new Node();
	temp1->value = sp1;
	temp1->weight = sp1.size();
	//this->destroy_tree(root);
	root = temp1;
	size_ = sp1.size();
	Node *temp2 = new Node;
	temp2->weight = sp2.size();
	temp2->value = sp2;
	//rhs.destroy_tree(rhs.root);
	rhs.root = temp2;
	rhs.size_ = sp2.size();

	//assert(0 && "Rope split() not implemented!");
	return rhs;
}
