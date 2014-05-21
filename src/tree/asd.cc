/** 
@file asd.cc

Plik do modyfikacji w w ramach cwiczenia 4 z AISDI.
Zawiera niekompletne implementacje metod klasy TreeMap.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY TreeMap.
    
@author
Pawel Cichocki, Michal Nowacki

@date  
last revision
- 2005.12.01 Pawel Cichocki: TreeNodeDetail class
- 2005.12.01 Michal Nowacki: lab #4
- 2005.11.17 Michal Nowacki: lab #3, copy operator and constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#ifdef _SUNOS
#include "/materialy/AISDI/tree/TreeMap.h" 
#else
#include "TreeMap.h"
#endif

int CCount::count = 0;
/// A helper class.
class TreeMapDetail //Helper
{
protected:
   friend class TreeMap;

   static void copyTree(TreeMap& a, const TreeMap& m){
	   copyTree(a,m.root->parent);
   }
   static void copyTree(TreeMap& a, const TreeNode* node){

		if (node == NULL){
			return;
		}

		a.insert(node->data);
		copyTree(a, node->left);
		copyTree(a, node->right);
   }
};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

TreeMap::TreeMap()
{
   // wartownik;
   root = new TreeNode(std::make_pair(Key(),Val()));
   root->parent = root;
};

/// Content of existing TreeMap object is copied into the new object. 
TreeMap::TreeMap( const TreeMap& m )
{

	root = new TreeNode(std::make_pair(Key(),Val()));
	root->parent = root;
	TreeMapDetail::copyTree(*this,m);

};

TreeMap::~TreeMap()
{
   clear();
   delete root;
};

// Inserts an element into the map.
// @returns A pair whose bool component is true if an insertion was
//          made and false if the map already contained an element
//          associated with that key, and whose iterator component coresponds to
//          the address where a new element was inserted or where the element
//          was already located.
std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<Key, Val>& entry)
{

	if (root->parent == root) {
		root->parent = new Node(entry,root,root);
		return std::make_pair(iterator(root->parent), bool(true));
	}

	Key k = entry.first;
	iterator i = find(k);

	if (i != end())
		return std::make_pair(i, false);

	Node* aktual = root->parent;
	Node* prev = aktual;

	while (aktual != root) {
		prev = aktual;
		if (aktual->data.first > k)
			aktual = aktual->left;
		else
			aktual = aktual->right;
	}

	if (prev->data.first > k) {
		prev->left = new Node(entry, prev, root, root);
		return std::make_pair(iterator(prev->left), bool(true));
	} else {
		prev->right = new Node(entry, prev, root, root);
		return std::make_pair(iterator(prev->right), bool(true));
	}
}

// Inserts an element into the map.
// This method assumes there is no value asociated with
// such a key in the map.

TreeMap::iterator TreeMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
	iterator i = find(entry.first);
	if (i == end()) {
		return this->insert(entry).first;
	} else
		i->second = entry.second;
	return i;
}

// Returns an iterator addressing the location of the entry in the map
// that has a key equivalent to the specified one or the location succeeding the
// last element in the map if there is no match for the key.
TreeMap::iterator TreeMap::find(const Key& k)
{
	if (empty())
		return end();

	Node* aktual = root->parent;

	while (aktual != root && aktual->data.first != k)
		if (aktual->data.first > k)
			aktual = aktual->left;
		else
			aktual = aktual->right;

	if (aktual == root)
		return end();
	else
		return iterator(aktual);
}

TreeMap::const_iterator TreeMap::find(const Key& k) const
{
	return const_cast<TreeMap*>(this)->find(k);
}

// Inserts an element into a map with a specified key value
// if one with such a key value does not exist.
// @returns Reference to the value component of the element defined by the key.
TreeMap::Val& TreeMap::operator[](const Key& k)
{
	iterator i = find(k);
	if (i == end()) {
		auto it = this->unsafe_insert(std::make_pair(k, Val()));
		return it->second;
	}
	return i->second;
}

// Tests if a map is empty.
bool TreeMap::empty( ) const
{
   return root->parent==root;
}

// Returns the number of elements in the map.
TreeMap::size_type TreeMap::size( ) const
{
	if (empty())
		return 0;
	int count = 0;
	for (auto it = begin(); it != end(); ++it)
		++count;
	return count;
}

// Returns the number of elements in a map whose key matches a parameter-specified key.
TreeMap::size_type TreeMap::count(const Key& _Key) const
{
	if (this->find(_Key) != end())
		return 1;  // this is not a multimap
	else
		return 0;
}

// Removes an element from the map.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator i)
{
	if (i == end())
		return end();

	auto it = i;
	++it;
	// jeśli nie ma potomkow
	if ( i.node->left == root && i.node->right == root){
		if (i.node == root->parent) {
			root->parent = root;
		}
		else {
			if (i.node->parent->left == i.node){
				i.node->parent->left = root;
			}
			if (i.node->parent->right == i.node){
				i.node->parent->right = root;
			}
		}
		delete i.node;
		return it;
	}

	// jesli ma lewego potomka
	if (i.node->right == root){
		// jezeli node jest root->parent
		if (i.node == root->parent) {
			root->parent = i.node->left;
			root->parent->parent = NULL;
		}
		else {
			if (i.node->parent->left == i.node){
				i.node->parent->left = i.node->left;
				i.node->left->parent = i.node->parent;
			}
			if (i.node->parent->right == i.node){
				i.node->parent->right = i.node->left;
				i.node->left->parent = i.node->parent;
			}
		}
		delete i.node;
		return it;
	}

	// jesli ma prawego potomka
	if ( i.node->left == root ){
		// jezeli node jest root->parent
		if (i.node == root->parent) {
			root->parent = i.node->right;
			root->parent->parent = NULL;
		}
		else {
			if (i.node->parent->left == i.node){
				i.node->parent->left = i.node->right;
				i.node->right->parent = i.node->parent;
			}
			if (i.node->parent->right == i.node){
				i.node->parent->right = i.node->right;
				i.node->right->parent = i.node->parent;
			}
		}
		delete i.node;
		return it;
	}

	// ma obu potomkow
	i.node->data = it.node->data;
	erase(it);
	return i;

}

// Removes a range of elements from the map.
// The range is defined by the key values of the first and last iterators
// first is the first element removed and last is the element just beyond the last elemnt removed.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l)
{
	if (f == end())
		return f;
	if (l == end())
		while (f != l)
			f = this->erase(f);
	else {
		P data = l.node->data;
		while (f.node->data != data)
			f = this->erase(f);
	}
	return f;
}

// Removes an element from the map.
// @returns The number of elements that have been removed from the map.
//          Since this is not a multimap itshould be 1 or 0.
TreeMap::size_type TreeMap::erase(const Key& key)
{
	auto result = find(key);
	if (result == end())
		return 0;

	erase(result);
	return 1;
}

// Erases all the elements of a map.
void TreeMap::clear( )
{
	erase(begin(), end());
	root->parent = root;
}

bool TreeMap::struct_eq(const TreeMap& another) const
{
	if (empty() && another.empty()) return true;

	if (size() != another.size()) return false;

	if (empty() || another.empty()) return false;

	iterator it1 = begin();
	iterator it2 = another.begin();


	while (true) {
		if (it1 == end() && it2 == another.end()) return true;

		if (it1.node->data!=it2.node->data)
			return false;

		++it1;++it2;
	}
}

bool TreeMap::info_eq(const TreeMap& another) const
{
	if (empty() && another.empty()) return true;

	if (size() != another.size()) return false;

	if (empty() || another.empty()) return false;

	iterator it1 = begin();
	iterator it2 = another.begin();


	while (true) {
		if (it1 == end() && it2 == another.end()) return true;

		if (another.find(it1->first) == another.end())
			return false;
		++it1;++it2;
	}
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator ++()
{
	// node == root i puste drzewo
	if (node->parent == node)
		return *this;

	// node!=root, szukamy end == root
	Node* end = node;

	// jestem w root->parent
	if (end->parent == NULL){
		if (end->left->left == NULL)
			end = end->left;
		else
			if(end->right->right == NULL)
				end = end->right;
			else {
				while(end->left->parent == end)
					end = end->left;
				end = end->left;
			}
	}

	else{
		if (end->left == NULL)
			return *this;
		while(end->left->parent == end)
			end = end->left;
		end = end->left;
	}


	// jeśli jest prawy potomek
	if (node->right != end){
		Node* tmp = node->right;
		while (tmp->left != end)
			tmp = tmp->left;
		node = tmp;
		return *this;
	}

	// jesli nie ma prawego i jestesmy w root->parent
	// zwracamy end
	if (node->parent == NULL){
		node = end;
		return *this;
	}

	// jesli jestem lewym dzieckiem
	if (node->parent->left == node){
		node = node->parent;
		return *this;
	}

	// dopoki jestem prawym dzieckiem
	while (node->parent!=NULL && node->parent->right == node)
		node = node->parent;

	// weszlismy na root->parent
	// zwracam end
	if (node->parent == NULL){
		node = end;
		return *this;
	}

	node = node->parent;
	return *this;
}
// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int)
{
	const_iterator it(*this);
	++(*this);
	return it;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--()
{
	// node == root i puste drzewo
	if (node->parent == node)
		return *this;

	// node!=root, szukamy end == root
	Node* end = node;

	// jestem w root->parent
	if (end->parent == NULL){
		if (end->left->left == NULL)
			end = end->left;
		else
			if(end->right->right == NULL)
				end = end->right;
			else {
				while(end->left->parent == end)
					end = end->left;
				end = end->left;
			}
	}

	else{
		if (end->left == NULL){
			Node *tmp = end->parent;
			while (tmp->right!=end)
				tmp = tmp->right;
			node = tmp;
			return *this;
		}
		else{
			while(end->left->parent == end)
				end = end->left;
			end = end->left;
		}
	}

	// jeśli jest lewy potomek
	if (node->left != end){
		Node* tmp = node->left;
		while (tmp->right != end)
			tmp = tmp->right;
		node = tmp;
		return *this;
	}

	// jesli nie ma lewego i jestesmy w root->parent
	if (node->parent == NULL)
		return *this;

	// jesli jestem prawym dzieckiem
	if (node->parent->right == node){
		node = node->parent;
		return *this;
	}

	// jesli jestem lewym dzieckiem

	while (node->parent!=NULL && node->parent->left == node)
		node = node->parent;

	// weszlismy na root->parent
	if (node->parent == NULL)
		return *this;

	node = node->parent;
	return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int)
{
	auto it(*this);
	--(*this);
	return it;
}


/// Assignment operator copy the source elements into this object.
TreeMap& TreeMap::operator=(const TreeMap& other)
{
	TreeMapDetail::copyTree(*this,other);
	return *this;
}
      
/// Returns an iterator addressing the first element in the map
TreeMap::iterator TreeMap::begin()
{ 
	if (empty()) return end();

	Node* node = root->parent;
	while (node->left!=root)
		node = node->left;
    return iterator(node);
}

TreeMap::const_iterator TreeMap::begin() const
{ 
	return const_cast<TreeMap*>(this)->begin();
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::iterator TreeMap::end()
{ 
   return iterator(root);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::const_iterator TreeMap::end() const
{ 
	return const_cast<TreeMap*>(this)->end();
}

//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void print(const std::pair<int, std::string>& p)
{
   std::cout<<p.first<<", "<<p.second<<std::endl;
}

