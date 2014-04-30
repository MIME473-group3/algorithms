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

/// A helper class.
class TreeMapDetail //Helper
{
protected:
	friend class TreeMap;

	/// Stupid example of a method that modifies a protected field in
	/// the TreeMap class. Feel free to remove this method or add new
	/// ones here.
	static void erase(TreeMap* tm, const TreeMap::K& k) {
		tm->root_ = nullptr; // we just modified a protected field in tree map
	}
};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

TreeMap::TreeMap()
	: root_(new Node(std::make_pair(K(), V()), nullptr, nullptr, nullptr)), size_(0) {}

TreeMap::TreeMap(const TreeMap& m) {}

TreeMap::~TreeMap() {
	clear();
	delete root_;
}

std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<K, V>& entry) {

	if(root_->parent_ == nullptr) {
		root_->parent_ = new Node(entry, root_, nullptr, nullptr);
		++size_;
		return std::make_pair(iterator(root_->parent_, this), true);
	}

	auto pair = unsafe_find(entry.first);
	if(pair.second == true)
		return std::make_pair(iterator(pair.first, this), false);

	return std::make_pair(unsafe_insert(entry, pair.first), true);
}

TreeMap::iterator TreeMap::unsafe_insert(const std::pair<K, V>& entry, Node* parent) {

	if(parent == nullptr)
		parent = unsafe_find(entry.first).first;

	Node* newNode = new Node(entry, parent, nullptr, nullptr);
	if(entry.first < parent->data_.first)
		parent->left_ = newNode;
	else
		parent->right_ = newNode;

	++size_;
	return iterator(newNode, this);
}

std::pair<TreeMap::Node*, bool> TreeMap::unsafe_find(const K& k) {

	Node* node = root_->parent_;
	while(true) {
		
		if(k == node->data_.first)
			return std::make_pair(node, true);

		if(k < node->data_.first) {
			if(node->left_ == nullptr)
				return std::make_pair(node, false);
			node = node->left_;
		} else {
			if(node->right_ == nullptr)
				return std::make_pair(node, false);
			node = node->right_;
		}
	}
}

TreeMap::iterator TreeMap::find(const K& k) {

	auto pair = unsafe_find(k);
	if(pair.second == false)
		return end();

	return iterator(pair.first, this);
}

TreeMap::const_iterator TreeMap::find(const K& k) const {
	return const_cast<TreeMap*>(this)->find(k);
}

TreeMap::V& TreeMap::operator[](const K& k) {
	return insert(std::make_pair(k, V())).first->second;
}

bool TreeMap::empty() const {
	return size_ == 0;
}

TreeMap::size_type TreeMap::size() const {

	return size_;
}

TreeMap::size_type TreeMap::count(const K& _Key) const {
	return 1;
}

TreeMap::iterator TreeMap::erase(TreeMap::iterator i) {
	assert(0);
	return end();
}

TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l) {
	///@todo Implement this
	assert(0);
	return end();
}

TreeMap::size_type TreeMap::erase(const K& key) {
	///@todo Implement this
	assert(0);
	return 0;
}

void TreeMap::clear() {
	TreeMapDetail::erase(this, 0);
}

bool TreeMap::struct_eq(const TreeMap& another) const {
	assert(0);
	return false;
}

bool TreeMap::info_eq(const TreeMap& another) const {
	assert(0);
	return false;
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator ++() {
	if(node_ == tree_->root_)
		return *this;

	if(node_->right_)
		node_ = node_->right_;
	else {
		Node* tmp_node = greater_ancestor();
		node_ = tmp_node ? tmp_node : tree_->root_;
	}

	return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int) {
	const_iterator tmp = *this;
	++(*this);
	return tmp;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--() {

	if(node_ == tree_->root_)
		node_ = tree_->begin().node_;
	else if(node_->left_)
		node_ = node_->left_;
	else {
		Node* tmp_node = smaller_ancestor();
		node_ = tmp_node ? tmp_node : node_ ;
	}

	return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int) {
	const_iterator tmp = *this;
	--(*this);
	return tmp;
}

TreeMap& TreeMap::operator=(const TreeMap& other) {
	return *this;
}

TreeMap::iterator TreeMap::begin() {

	if(empty()) return end();
	return iterator(smallest_descendant(root_->parent_), this);
}

TreeMap::const_iterator TreeMap::begin() const {
	return const_cast<TreeMap*>(this)->begin();
}

TreeMap::iterator TreeMap::end() {
	return iterator(root_, this);
}

TreeMap::const_iterator TreeMap::end() const {
	return const_cast<TreeMap*>(this)->end();
}

TreeMap::Node* TreeMap::smallest_descendant(Node* node) {

	while(node->left_)
		node = node->left_;

	return node;
}

TreeMap::Node* TreeMap::greatest_descendant(Node* node) {

	while(node->right_);
		node = node->right_;
	return node;
}

TreeMap::Node* TreeMap::const_iterator::smaller_ancestor() {

	if(node_ == node_->parent_->right_)
		return node_->parent_;

	Node* node = node_->parent_;
	while(node != node->parent_->right_ && node != tree_->root_)
		node = node->parent_;

	if(node == tree_->root_ || node->left_ == nullptr)
		return nullptr;

	//todo cos tu nie gra
	return TreeMap::smallest_descendant(node->left_);
}

TreeMap::Node* TreeMap::const_iterator::greater_ancestor() {

	if(node_ == node_->parent_->left_)
		return node_->parent_;

	Node* node = node_->parent_;
	while(node != node->parent_->left_ && node != tree_->root_)
		node = node->parent_;

	if(node == tree_->root_ || node->right_ == nullptr)
		return nullptr;

	//todo cos tu nie gra
	return TreeMap::smallest_descendant(node->right_);
}
