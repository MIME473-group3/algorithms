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
#ifdef _SUNOS
#include "/materialy/AISDI/tree/TreeMap.h" 
#else
#include "TreeMap.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

int CCount::count = 0;

#include <iostream>

TreeMap::TreeMap()
	: root_(new Node(std::make_pair(K(), V()), nullptr, nullptr, nullptr)), size_(0) {}

TreeMap::TreeMap(const TreeMap& m)
	: root_(new Node(std::make_pair(K(), V()), nullptr, nullptr, nullptr)), size_(0) {

	copyNode(m.root_->parent_);
}

void TreeMap::copyNode(Node* node) {

	if(!node) return;

	insert(node->data_);
	copyNode(node->left_);
	copyNode(node->right_);
}

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
	if(node == nullptr)
		return std::make_pair(root_, false);

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

TreeMap::size_type TreeMap::count(const K& k) const {
	return find(k) != end();
}

bool isLeaf(TreeNode* node) {
	return node->left_ == nullptr && node->right_ == nullptr;
}

TreeMap::Node** TreeMap::pointerFromParent(Node* node) {

	Node* parent = node->parent_;
	if(parent->right_ == node) return &parent->right_;
	if(parent->left_ == node) return &parent->left_;
	return &parent->parent_;
}

TreeMap::Node* TreeMap::getAnOnlyChild(Node* node) {

	if(node->right_ && !node->left_) return node->right_;
	if(node->left_ && !node->right_) return node->left_;
	return nullptr;
}

bool TreeMap::hasTwoChildren(Node* node) {
	return node->left_ && node->right_;
}

TreeMap::iterator TreeMap::erase(TreeMap::iterator i) {

	Node* node = (i++).node_;
	if(hasTwoChildren(node)) {

		node->data_ = *i;
		erase(i);

	} else {

		if(isLeaf(node)) *pointerFromParent(node) = nullptr;
		else {
			Node* ptrToChild = getAnOnlyChild(node);
			*pointerFromParent(node) = ptrToChild;
			ptrToChild->parent_ = node->parent_;
		}
		--size_;
		delete node;
	}
	return i;
}

TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l) {

	while(f != l)
		f = erase(f);
	return l;
}

TreeMap::size_type TreeMap::erase(const K& k) {

	auto it = find(k);
	if(it == end()) return 0;
	erase(it);
	return 1;
}

void TreeMap::clear() {
	erase(begin(), end());
}

bool TreeMap::struct_eq(const TreeMap& that) const {

	//	Both maps are empty
	if (empty() && that.empty())
		return true;

	//	One of them is empty
	if (empty() || that.empty())
		return false;

	iterator thisIt = begin();
	iterator thatIt = that.begin();

	while(true)	{

		// if both maps end then they are equal
		if (thisIt == end() && thatIt == that.end())
			return true;

		// but if only one of them ends, they differ
		if (thisIt == end() || thatIt == that.end())
			return false;

		//	Checks whether pairs are equal and equally ordered
		if (*thisIt != *thatIt)
			return false;

		++thisIt;
		++thatIt;
	}
}

bool TreeMap::info_eq(const TreeMap& that) const {

	//	Both maps are empty
	if (empty() && that.empty())
		return true;

	//	One of them is empty
	if (empty() || that.empty())
		return false;

	iterator thisIt = begin();
	iterator thatIt = that.begin();

	while(true)	{

		// if both maps end then they are equal
		if (thisIt == end() && thatIt == that.end())
			return true;

		// but if only one of them ends, they differ
		if (thisIt == end() || thatIt == that.end())
			return false;

		//	Checks whether the same pairs exist in both maps
		auto it = that.find(thisIt->first);
		if(thisIt->second != it->second)
			return false;

		++thisIt;
		++thatIt;
	}
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator++() {

	if(node_ == tree_->root_)
		return *this;

	if(node_->right_) {
		node_ = smallest_descendant(node_->right_);
	} else {
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

	if(node_ == tree_->root_ && !tree_->empty())
		node_ = TreeMap::greatest_descendant(tree_->root_->parent_);
	else if(node_->left_)
		node_ = greatest_descendant(node_->left_);
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

	while(node->right_)
		node = node->right_;
	return node;
}

TreeMap::Node* TreeMap::const_iterator::smaller_ancestor() {

	if(isEnd() || isRoot())
		return nullptr;

	Node* node = node_;
	while(node->parent_->left_ == node)
		node = node->parent_;

	return node && node->parent_ ? node->parent_ : nullptr;
}

TreeMap::Node* TreeMap::const_iterator::greater_ancestor() {

	if(isEnd() || isRoot())
		return nullptr;

	Node* node = node_;
	while(node->parent_->right_ == node)
		node = node->parent_;

	return node && node->parent_ ? node->parent_ : nullptr;
}

bool TreeMap::isRootNode(Node* node) {

	return root_->parent_ && (root_->parent_ == node);
}

bool TreeMap::isEndNode(Node* node) {

	return root_ == node;
}

bool TreeMap::const_iterator::isRoot() {

	return tree_->isRootNode(node_);
}

bool TreeMap::const_iterator::isEnd() {

	return tree_->isEndNode(node_);
}

bool TreeMap::const_iterator::isRightChild() {

	return node_->parent_ && (node_ == node_->parent_->right_);
}
bool TreeMap::const_iterator::isLeftChild() {

	return node_->parent_ && (node_ == node_->parent_->left_);
}
