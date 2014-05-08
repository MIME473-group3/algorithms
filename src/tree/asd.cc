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
 Copyright_ (c) 2005 Instytut Informatyki, Politechnika Warszawska
 ALL RIGHTS RESERVED
 *******************************************************************************/
#ifdef _SUNOS
#include "tree/TreeMap.h" 
#else
#include "TreeMap.h"
#endif

int CCount::count = 0;
TreeMap::Node* TreeMap::last_ = nullptr;

TreeMap::TreeMap() : size_(0), root_(nullptr) {}

TreeMap::TreeMap(const TreeMap& m) : size_(0), root_(nullptr) {

	*this = m;
}

TreeMap::~TreeMap() {
	clear();
}

void TreeMap::copyNode(Node* node) {

	if (!node)
		return;

	insert(node->data_);
	copyNode(node->left_);
	copyNode(node->right_);
}

std::pair<TreeMap::iterator, bool> TreeMap::insert(
		const std::pair<K, V>& entry) {

	auto pair = unsafe_find(entry.first);
	if (pair.second == true)
		return std::make_pair(iterator(pair.first, this), false);
	return std::make_pair(unsafe_insert(entry, pair.first), true);
}

TreeMap::iterator TreeMap::unsafe_insert(const std::pair<K, V>& entry,
		Node* parent) {

	Node* newNode = nullptr;
	if (root_) {
		if (parent == nullptr)
			parent = unsafe_find(entry.first).first;

		newNode = new Node(entry, parent);
		if (entry.first < parent->data_.first)
			parent->left_ = newNode;
		else
			parent->right_ = newNode;
	} else
		newNode = root_ = new Node(entry);

	++size_;
	return iterator(newNode, this);
}

std::pair<TreeMap::Node*, bool> TreeMap::unsafe_find(const K& k) {

	if (!root_)
		return std::make_pair(nullptr, false);
	Node* node_ = root_;
	while (true) {

		if (k == node_->data_.first)
			return std::make_pair(node_, true);

		if (k <= node_->data_.first) {
			if (!node_->left_)
				return std::make_pair(node_, false);
			node_ = node_->left_;
		} else {
			if (!node_->right_)
				return std::make_pair(node_, false);
			node_ = node_->right_;
		}
	}
}

TreeMap::iterator TreeMap::find(const K& k) {

	auto pair = unsafe_find(k);
	if (pair.second == false)
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
	return !root_;
}

TreeMap::size_type TreeMap::size() const {

	return size_;
}

TreeMap::size_type TreeMap::count(const K& k) const {
	return find(k) != end();
}

bool TreeMap::isLeaf(TreeNode* node_) {
	return node_->left_ == nullptr && node_->right_ == nullptr;
}

TreeMap::Node** TreeMap::pointerFromParent(Node* node_) {

	Node* parent = node_->parent_;
	if (parent->right_ == node_)
		return &parent->right_;
	if (parent->left_ == node_)
		return &parent->left_;
	return &parent->parent_;
}

TreeMap::Node* TreeMap::getAnOnlyChild(Node* node_) {

	if (node_->right_ && !node_->left_)
		return node_->right_;
	if (node_->left_ && !node_->right_)
		return node_->left_;
	return nullptr;
}

bool TreeMap::hasTwoChildren(Node* node_) {
	return node_->left_ && node_->right_;
}

TreeMap::iterator TreeMap::erase(TreeMap::iterator i) {

	if (i == end())
		return i;

	Node* node_ = (i++).node_;
	if (hasTwoChildren(node_)) {

		node_->data_ = *i;
		erase(i);

	} else {

		if (isLeaf(node_)) {
			if (node_ == root_)
				root_ = nullptr;
			else
				*pointerFromParent(node_) = nullptr;
		} else {
			Node* ptrToChild = getAnOnlyChild(node_);
			if (node_ == root_)
				root_ = ptrToChild;
			else
				*pointerFromParent(node_) = ptrToChild;
			ptrToChild->parent_ = node_->parent_;
		}
		--size_;
		delete node_;
	}
	return i;
}

TreeMap::size_type TreeMap::erase(const K& k) {

	auto it = find(k);
	if (it == end())
		return 0;
	erase(it);
	return 1;
}

TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l) {

	while (f != l && f != end())
		f = erase(f);
	return f;
}

void TreeMap::clear() {
	erase(begin(), end());
}

bool TreeMap::struct_eq(const TreeMap& that) const {

	//	Both maps are empty
	if (empty() && that.empty())
		return true;

	// Size differs
	if(size() != that.size())
		return false;

	//	One of them is empty
	if (empty() || that.empty())
		return false;

	iterator thisIt = begin();
	iterator thatIt = that.begin();

	while (true) {

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

	// Size differs
	if(size() != that.size())
		return false;

	//	One of them is empty
	if (empty() || that.empty())
		return false;

	iterator thisIt = begin();
	iterator thatIt = that.begin();

	while (true) {

		// if both maps end then they are equal
		if (thisIt == end() && thatIt == that.end())
			return true;

		// but if only one of them ends, they differ
		if (thisIt == end() || thatIt == that.end())
			return false;

		//	Checks whether the same pairs exist in both maps
		if (that.find(thisIt->first) == that.end())
			return false;

		++thisIt;
		++thatIt;
	}
}

TreeMap::Node* TreeMap::smallest_descendant(Node* node) {

	while (node->left_)
		node = node->left_;
	return node;
}

TreeMap::Node* TreeMap::greatest_descendant(Node* node) {

	while (node->right_)
		node = node->right_;
	return node;
}

TreeMap::Node* TreeMap::const_iterator::smaller_ancestor() {

	Node* node = node_;
	while (node->parent_ && node->parent_->left_ == node)
		node = node->parent_;

	return node->parent_;
}

TreeMap::Node* TreeMap::const_iterator::greater_ancestor() {

	Node* node = node_;
	while (node->parent_ && node->parent_->right_ == node)
		node = node->parent_;

	return node->parent_;
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator ++() {

	if (!node_) return *this;

	if (node_->right_)
		node_ = smallest_descendant(node_->right_);
	else {
		last_ = node_;
		node_ = greater_ancestor();
		if (node_)
			last_ = node_;
	}
	return *this;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--() {
	if (node_) {
		if (node_->left_) {
			node_ = greatest_descendant(node_->left_);
		} else {
			node_ = smaller_ancestor();
		}
	} else {
		node_ = last_;
	}
	return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int) {
	///@todo Implement this
	const_iterator temp = *this;
	++*this;
	return temp;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int) {
	const_iterator temp = *this;
	--*this;
	return temp;
}

TreeMap& TreeMap::operator=(const TreeMap& other) {
	copyNode(other.root_);
	return *this;
}

TreeMap::iterator TreeMap::begin() {

	if (!root_)	return end();
	return iterator(smallest_descendant(root_), this);
}

TreeMap::const_iterator TreeMap::begin() const {
	return const_cast<TreeMap*>(this)->begin();
}

TreeMap::iterator TreeMap::end() {
	return iterator(nullptr, this);
}

TreeMap::const_iterator TreeMap::end() const {
	return const_cast<TreeMap*>(this)->end();
}
