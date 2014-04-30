/** 
 @file TreeMap.h

 Zawiera deklaracje klasy TreeMap.
 Jest to mapa (Slownik) zrobiona na drzewie binarnym.
 Implementacja tej klasy jest przedmiotem cwiczenia 4
 na laboratoriach z AISDI.

 @author
 Pawel Cichocki, Michal Nowacki

 @date
 last revision
 - 2005.12.01 Pawel Cichocki: More TreeNode constructors
 - 2005.12.01 Pawel Cichocki: TreeNodeDetail class
 - 2005.12.01 Michal Nowacki: Lab #4
 - 2005.11.17 Michal Nowacki: prev pointer
 - 2005.11.04 Pawel Cichocki: cosmetic code improvements
 - 2005.11.04 Pawel Cichocki: a public method for obtaining the count from CCount
 - 2005.11.03 Pawel Cichocki: const_iterator done properly now
 - 2005.10.27 Pawel Cichocki: cosmetic changes
 - 2005.10.27 Michal Nowacki: removed templates, and moved the implementation to another file
 - 2005.10.25 Pawel Cichocki: wrote it

 COPYRIGHT:
 Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
 ALL RIGHTS RESERVED
 *******************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <iterator>
#include <string>

class CCount {
private:
	static int count;
	CCount() {
		count++;
	}

	~CCount() {
		assert(count > 0);
		count--;
	}

	friend struct TreeNode;

public:

	static int getCount() {
		return count;
	}
};

struct TreeNode: CCount {
	typedef std::pair<int, std::string> T;
	TreeNode* parent_;  ///< Parent node
	TreeNode* left_;    ///< The left child in the tree
	TreeNode* right_;   ///< The right child in the tree
	T data_;            ///< User's data
	short b_;            ///< balance
	TreeNode(const T& d) :
			parent_(nullptr), left_(nullptr), right_(nullptr), data_(d), b_(0) {
	}

	TreeNode(const T& d, TreeNode* l, TreeNode* r) :
			parent_(nullptr), left_(l), right_(r), data_(d), b_(0) {
	}

	TreeNode(const T& d, TreeNode* p) :
			parent_(p), left_(nullptr), right_(nullptr), data_(d), b_(0) {
	}

	TreeNode(const T& d, TreeNode* p, TreeNode* l, TreeNode* r) :
			parent_(p), left_(l), right_(r), data_(d), b_(0) {
	}

	TreeNode(const T& d, short bal, TreeNode* p) :
			parent_(p), left_(nullptr), right_(nullptr), data_(d), b_(bal) {
	}
};

class TreeMapDetail;

class TreeMap {
	friend class TreeMapDetail;
public:
	typedef int K;
	typedef std::string V;

protected:
	typedef TreeNode Node;
	Node* root_;
	TreeMapDetail* detail_;

public:
	typedef size_t size_type;
	typedef std::pair<K, V> T;

	TreeMap();
	TreeMap(const TreeMap&);
	~TreeMap();

	class const_iterator: public std::iterator<std::bidirectional_iterator_tag, std::pair<K, V> > {


	protected:
		Node* node_;
		friend class TreeMap;
		TreeMap* tree_;
		Node* smaller_ancestor();
		Node* greater_ancestor();
		const_iterator(Node* x, TreeMap* tree) : node_(x), tree_(tree) {}

	public:
		const_iterator() {}
		const_iterator(const const_iterator& a) : node_(a.node_) {}

		inline const T& operator*() const {
			return node_->data_;
		}

		inline const T* operator->() const {
			return &(node_->data_);
		}

		// preincrement
		const_iterator& operator++();
		// postincrement
		const_iterator operator++(int);
		// predecrement
		const_iterator& operator--();
		// postdecrement
		const_iterator operator--(int);

		inline bool operator==(const const_iterator& a) const {
			return node_ == a.node_;
		}

		inline bool operator!=(const const_iterator& a) const {
			return node_ != a.node_;
		}
	};

	class iterator: public const_iterator {
		iterator(Node* x, TreeMap* tree) : const_iterator(x, tree) {
			this->node_ = x;
		}
		friend class TreeMap;
		using const_iterator::smaller_ancestor;
		using const_iterator::greater_ancestor;

	public:
		iterator() {}
		iterator(const const_iterator& a) :	const_iterator(a) {}
		iterator(const iterator& a) : const_iterator(a.node_, a.tree_) {}

		inline T& operator*() const {
			return node_->data_;
		}

		inline T* operator->() const {
			return &(node_->data_);
		}

		iterator& operator++() {  // preincrement
			++(*(const_iterator*) this);
			return (*this);
		}

		iterator operator++(int) {  // postincrement
			iterator temp = *this;
			++*this;
			return temp;
		}

		iterator& operator--() {  // predecrement
			--(*(const_iterator*) this);
			return (*this);
		}

		iterator operator--(int) {  // postdecrement
			iterator temp = *this;
			--*this;
			return temp;
		}
	};

	friend class iterator;
	friend class const_iterator;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	std::pair<iterator, bool> insert(const std::pair<K, V>& entry);
	iterator unsafe_insert(const std::pair<K, V>& entry, Node* parent = nullptr);
	iterator find(const K& k);
	const_iterator find(const K& k) const;
	V& operator[](const K& k);
	bool empty() const;
	size_type size() const;
	size_type count(const K& k) const;
	iterator erase(iterator i);
	iterator erase(iterator first, iterator last);
	size_type erase(const K& key);
	void clear();
	bool struct_eq(const TreeMap& another) const;
	bool info_eq(const TreeMap& another) const;

	/// Returns true if this map contains exactly the same key-value pairs as the another map.
	inline bool operator==(const TreeMap& a) const {
		return info_eq(a);
	}

	/// Assignment operator copy the source elements into this object.
	TreeMap& operator=(const TreeMap&);

private:
	std::pair<Node*, bool> unsafe_find(const K& k);
	static Node* smallest_descendant(Node* node);
	static Node* greatest_descendant(Node* node);
	int size_;
};

