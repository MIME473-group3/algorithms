/** 
 @file aisdihashmap.h

 AISDIHashMap and related functions interface.

 @author
 Pawel Cichocki

 @date
 last revision
 - 2006.03.24 Pawel Cichocki: wrote it

 COPYRIGHT:
 Copyright (c) 2006 Instytut Informatyki, Politechnika Warszawska
 ALL RIGHTS RESERVED
 *******************************************************************************/

#include <algorithm>
#include <utility>
#include <iterator>
#include <assert.h>

//static const int DEFAULT_LENGTH = 32;
static const int DEFAULT_LENGTH = 65536;

template<class Key>
inline bool _compFunc(const Key& key1, const Key& key2) {

	return (key1 == key2);
};

inline unsigned hashF(const std::string& m) {

	if (m.length() == 0)
		return 0;
	ushort hash = 0;

	const char* str = m.c_str();
	std::for_each(str, str + m.length(),
			[&hash](const char c) mutable {hash = 31 * hash + static_cast<ushort>(c);});

	return static_cast<unsigned>(hash);
};

template<class K, class V, unsigned hashFunc(const K&) = &hashF, bool compFunc(const K&, const K&) = &_compFunc<K>>
class AISDIHashMap {
	//	===	forward declarations	===================================================================================


	//	===	typedefs	===================================================================================
public:
	typedef K key_type;
	typedef V value_type;
	typedef std::pair<K, V> T;
	typedef unsigned size_type;

	//	===	friendships	===================================================================================

	//	===	classes	=========================================================================================
private:
	class InnerList {

		//	=== classes =================================================================================
	private:
			class NodeCounter {
			public:
				static int count;
				NodeCounter() { ++count; }
				virtual ~NodeCounter() {	assert(count > 0); --count;	}
				friend struct Node;
			public:
				static int getCount() {return count; }
			};

			struct Node : private NodeCounter {
				Node* next_;
				Node* prev_;
				T data_;

				Node(const T& data) : next_(nullptr), prev_(nullptr), data_(data) {};
				Node(const T& data, Node* next, Node* prev)
				: next_(next), prev_(prev), data_(data) {};
			};

		public:
			class const_iterator: public std::iterator<std::forward_iterator_tag, T> {

			protected:
				const_iterator(InnerList* list, Node* node) : list_(list), node_(node) {}
				friend class InnerList;
				friend class AISDIHashMap::const_iterator;
				friend class AISDIHashMap::iterator;
				InnerList* list_;
				Node* node_;

				Node* sentinel() {
					return list_->head_;
				}

			public:
				const_iterator() : node_(nullptr) {}
				const_iterator(const const_iterator& a) : list_(a.list_), node_(a.node_) {}
				inline const T& operator*() const { return node_->data_; }
				inline const T* operator->() const { return &(node_->data_); }
				Node* getNode() { return node_;};

				const_iterator& operator++() {	//pre

					if(node_ != sentinel())
						node_ = node_->next_;

					return *this;
				}

				const_iterator operator++(int) {	// post

					const_iterator tmp = *this;
					++(*this);
					return tmp;
				}

				const_iterator& operator--() { 	//pre

					if(node_->prev_ != sentinel())
						node_ = node_->prev_;

					return *this;
				}

				const_iterator operator--(int) {	// post

					const_iterator tmp = *this;
					--(*this);
					return tmp;
				}

				inline bool operator==(const const_iterator& a) const { return list_ == a.list_ && node_ == a.node_; }
				inline bool operator!=(const const_iterator& a) const {	return list_ != a.list_ || node_ != a.node_; }
			};

			class iterator: public const_iterator {

				iterator(InnerList* list, Node* node) : const_iterator(list, node) {}
				friend class InnerList;
				using const_iterator::node_;
				using const_iterator::sentinel;

			public:
				iterator() {}
				iterator(const iterator& a) : const_iterator(a) {}
				inline T& operator*() const { return node_->data_; }
				inline T* operator->() const { return &(node_->data_); }

				iterator& operator++() {  // preincrementacja
					++(*(const_iterator*) this);
					return (*this);
				}

				iterator operator++(int) {  // postincrementacja
					iterator temp = *this;
					++*this;
					return temp;
				}

				iterator& operator--() {  // predekrementacja
					--(*(const_iterator*) this);
					return (*this);
				}

				iterator operator--(int) {  // postdekrementacja
					iterator temp = *this;
					--*this;
					return temp;
				}
			};

		//	=== constructors =================================================================================
		public:

			InnerList() {

				// first element is a sentinel
				head_ = new Node(std::make_pair(K(), V()));
				head_->next_ = head_;
				head_->prev_ = head_;
			}

			InnerList(const InnerList& m) {

				head_ = new Node(std::make_pair(K(), V()));
				head_->next_ = head_;
				head_->prev_ = head_;

				for (auto it = m.begin(); it != m.end(); ++it)
					this->unsafe_insert(*it);
			}

			~InnerList() {

				clear();
				delete head_;
			}

		//	=== methods =================================================================================
		public:
			std::pair<iterator, bool> insert(const T& entry) {

				iterator it = find(entry.first);
				if (it != end())
					return std::make_pair(it, false);
				else
					return std::make_pair(unsafe_insert(entry), true);
			}

			iterator unsafe_insert(const T& entry) {

				Node* toBeInserted = new Node(entry);
				if(empty())
					head_->prev_ = toBeInserted;

				toBeInserted->next_ = head_->next_;
				toBeInserted->prev_ = head_;

				head_->next_->prev_ = toBeInserted;
				head_->next_ = toBeInserted;


				return begin();
			}

			iterator find(const K& k) {

				return iterator(this, static_cast<const InnerList*>(this)->find(k).node_);
			}

			const_iterator find(const K& k) const {

				for (const_iterator it = this->begin(); it != this->end(); ++it)
					if (compFunc(it->first, k))
						return it;

				return end();
			}

			V& operator[](const K& k) {

				return insert(std::make_pair(k, V())).first->second;
			}

			bool empty() const {

				return head_ == head_->next_;
			}

			size_type size() const {

				auto first = head_->next_;
				int size = 0;
				while (first != head_) {
					first = first->next_;
					++size;
				}
				return size;
			}

			size_type count(const K& k) const {

				if (find(k) != end())
					return 1;

				return 0;
			}

			iterator erase(iterator it) {

				if (it == end())
					return it;

				Node* node = it.node_;
				Node* next = it.node_->next_;
				Node* prev = it == begin() ? head_ : (--it).node_;

				prev->next_ = next;
				next->prev_ = prev;
				delete node;

				return iterator(this, next);
			}

			iterator erase(iterator f, iterator l) {

				if (f == end())
					return f;

				Node* node = f.node_;
				Node* prev = f == begin() ? head_ : (--f).node_;
				Node* next = l.node_;

				prev->next_ = next;
				next->prev_ = prev;
				while (node->next_ != next) {

					Node* tmp = node;
					node = node->next_;
					delete tmp;
				}

				return l;
			}

			size_type erase(const K& key) {

				iterator it = find(key);
				if (it == end())
					return 0;

				erase(it);
				return 1;
			}

			void clear() {

				Node* head = head_->next_;
				while (head != head_) {
					Node* tmp = head;
					head = head->next_;
					delete tmp;
				}
				head_->next_ = head_;
			}

			iterator begin() {

				return iterator(this, head_->next_);
			}

			const_iterator begin() const {

				return const_cast<InnerList*>(this)->begin();
			}

			iterator end() {

				return iterator(this, this->head_);
			}

			const_iterator end() const {

				return const_cast<InnerList*>(this)->end();
			}

		//	=== fields =================================================================================
		private:
			Node* head_;
		};

public:
	class const_iterator: public std::iterator<std::forward_iterator_tag, T> {

		protected:
			AISDIHashMap* map_;
			typename InnerList::iterator listIterator_;
			int idx_;

			friend class AISDIHashMap;


			const_iterator(AISDIHashMap* map, typename InnerList::iterator listIterator, int idx)
				: map_(map), listIterator_(listIterator), idx_(idx_) {};

			InnerList& getList(int idx) {
				return map_->container_[idx];
			}

			bool isListBegin() {

				return listIterator_ == map_->container_[idx_].begin();
			}

			bool isListEnd() {

				return listIterator_ == map_->container_[idx_].end();
			}

			bool isListEmpty() {

				return map_->container_[idx_].empty();
			}

		public:
			const_iterator() {};
			const_iterator(const const_iterator& a) :  map_(a.map_), listIterator_(a.listIterator_), idx_(a.idx_) {};

			inline const T& operator*() const { return listIterator_.node_->data_; }
			inline const T* operator->() const { return &(listIterator_.node_->data_); }

			// pre
			const_iterator& operator++() {

				++listIterator_;
				if(isListEnd() && idx_ < map_->length_ - 1) {
					do { ++idx_; } while(idx_ < map_->length_ && isListEmpty());
					listIterator_ = getList(idx_).begin();
				}
				return *this;
			}

			// post
			const_iterator operator++(int) {

				const_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			//pre
			const_iterator& operator--() {
				if(!isListBegin() && !isListEmpty()) {

					--listIterator_;
				} else if(idx_ > 0) {

					int tmp_idx = idx_;
					do { --tmp_idx; } while(tmp_idx > 0 && getList(tmp_idx).empty());

					if(!getList(tmp_idx).empty()) {

						idx_ = tmp_idx;
						listIterator_ = --(getList(tmp_idx).end());
					}
				}

				return *this;
			}

			// post
			const_iterator operator--(int) {

				const_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			inline bool operator==(const const_iterator& a) const {

				return map_ == a.map_ && idx_ == a.idx_ && listIterator_ == a.listIterator_;
			}

			inline bool operator!=(const const_iterator& a) const {

				return map_ != a.map_ || idx_ != a.idx_ || listIterator_ != a.listIterator_;
			}
		};

	class iterator: public const_iterator {

		iterator(AISDIHashMap* map, typename InnerList::iterator listIterator, int idx)
		: const_iterator(map, listIterator, idx) {

			this->map_ = map; listIterator_ = listIterator; this->idx_ = idx;
		};

		friend class InnerList;
		friend class AISDIHashMap;
		using const_iterator::listIterator_;

	public:
		iterator() {};
		iterator(const iterator& a) : const_iterator(a) {};

		inline T& operator*() const { return listIterator_.node_->data_; }
		inline T* operator->() const { return &(listIterator_.node_->data_); }

		iterator& operator++() {  // preincrementacja
			++(*(const_iterator*) this);
			return (*this);
		}

		iterator operator++(int) {  // postincrementacja
			iterator temp = *this;
			++*this;
			return temp;
		}

		iterator& operator--() {  // predekrementacja
			--(*(const_iterator*) this);
			return (*this);
		}

		iterator operator--(int) {  // postdekrementacja
			iterator temp = *this;
			--*this;
			return temp;
		}
	};

	//	===	constructors	===================================================================================
public:

	AISDIHashMap() : length_(DEFAULT_LENGTH) {

		container_ = new InnerList[length_];
	}

	~AISDIHashMap() {

		delete[] container_;
	}

	explicit AISDIHashMap(const AISDIHashMap<K, V, hashFunc, compFunc>& a)
		: length_(a.length_) {

		container_ = new InnerList[length_];
		for(int i = 0; i < length_; ++i) {
			container_[i] = InnerList(a.container_[i]);
		}
	}

	//	===	methods	==========================================================================================
public:

	inline iterator begin() {

		for (int i = 0; i < length_; ++i)
			if (!container_[i].empty())
					return iterator(this, container_[i].begin(), i);

		return end();
	}

	inline const_iterator begin() const {

		return const_cast<AISDIHashMap*>(this)->begin();
	}

	inline iterator end() {
		if(length_ == 0)
			return iterator();

		return iterator(this, container_[length_ - 1].end(), length_ -1);
	}

	inline const_iterator end() const {

		return const_cast<AISDIHashMap*>(this)->end();
	}

	std::pair<iterator, bool> insert(const T& entry) {

		iterator it = find(entry.first);
		if (it != end())
			return std::make_pair(it, false);
		else
			return std::make_pair(unsafe_insert(entry), true);
	}

	iterator find(const K& k) {

		int index = indexOf(hashF(k));
		InnerList& list = container_[index];
		auto it = list.find(k);
		if(it == list.end())
			return end();
		return iterator(this, it, index);
	}

	const_iterator find(const K& k) const {

		return const_cast<AISDIHashMap*>(this)->find(k);
	}

	V& operator[](const K& k) {

		return insert(std::make_pair(k, V())).first->second;
	}

	bool empty() const {

		return size() == 0;
	}

	size_type size() const {

		size_type size = 0;
		for(int i = 0; i < length_; ++i)
			size += container_[i].size();
		return size;
	}

	size_type count(const K& k) const {

		return static_cast<size_type>(find(k) != end());
	}

	iterator erase(iterator i) {

		auto list = container_[i.idx_];
		if(list.erase(i.listIterator_) == list.end())
			return end();
		return iterator(this, i.listIterator_, i.idx_);
	}

	iterator erase(iterator first, iterator last) {

		if(first.idx_ == last.idx_) {
			auto listIt = container_[first.idx_].erase(first.listIterator_, last.listIterator_);
			return iterator(this, listIt, first.idx_);
		}

		auto firstList = &container_[first.idx_];
		auto lastList = &container_[last.idx_];

		firstList->erase(first.listIterator_, firstList->end());

		while(++firstList != lastList)
			firstList->clear();

		auto listIt = lastList->erase(lastList->begin(), last.listIterator_);

		return iterator(this, listIt, last.idx_);
	}

	size_type erase(const K& k) {

		if(listByKey(k).erase(k) == 0)
			return 0;
		return 1;
	}

	void clear() {

		for(auto list = container_; list != container_ + length_; ++list)
			list->clear();
	}

private:

	int indexOf(unsigned hash) {

		return hash & (length_ - 1);
	}

	InnerList& listByHash(unsigned hash) {

		return container_[indexOf(hash)];
	}

	InnerList& listByKey(const K& k) {

			return container_[indexOf(hashFunc(k))];
		}

	InnerList& listByEntry(const T& entry) {

		return container_[indexOf(hashF(entry.first))];
	}

	iterator unsafe_insert(const T& entry) {

		int idx = indexOf(hashFunc(entry.first));
		auto it = container_[idx].unsafe_insert(entry);

		return iterator(this, it, idx);
	}

	//	===	fields	=========================================================================================
private:

	InnerList* container_;
	const int length_;
};
