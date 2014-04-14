/**
 @file asd.cc

 Plik do modyfikacji w ramach cwiczenia z AISDI.
 Zawiera niekompletne implementacje metod klasy ListMap,
 oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
 zaimplementowana w jescze bardziej szczatkowy sposob.
 Jest tez prosta funkcja testujaca (void test()), ktora
 jest wolana w funkcji main. Mozna w niej zaimplementowac
 wlasne testy.
 NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

 @author
 Pawel Cichocki, Michal Nowacki

 @date
 last revision
 - 2006.01.06 Michal Nowacki: wersja polska
 - 2005.11.17 Michal Nowacki: constructor
 - 2005.11.04 Pawel Cichocki: copied comments from the header
 - 2005.11.03 Pawel Cichocki: const_iterator done properly now
 - 2005.10.27 Pawel Cichocki: cosmetic changes
 - 2005.10.26 Michal Nowacki: removed some method bodies
 - 2005.10.25 Pawel Cichocki: wrote it

 COPYRIGHT:
 Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
 ALL RIGHTS RESERVED
 *******************************************************************************/

#include <algorithm>
#include <string>
#include <cstdlib>
#include <iostream>

#ifdef _SUNOS
#include "/materialy/AISDI/liniowe/ListMap.h"
#else
#include "ListMap.h"
#endif

#define LOG(x) std::cout << __LINE__ << ": " << x << std::endl;

#define FUNC LOG(__PRETTY_FUNCTION__);

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap() {

	// first element is a sentinel
	first = new Node(std::make_pair(0, ""));
	first->next = first;
	first->prev = first;
}

ListMap::ListMap(const ListMap& m) {

	first = new Node(std::make_pair(0, ""));
	first->next = first;
	first->prev = first;

	ListMap m2;
	for(auto it = m.begin(); it != m.end(); ++it)
		m2.unsafe_insert(*it);

	for(auto it = m2.begin(); it != m2.end(); ++it)
			unsafe_insert(*it);
//	this->first = m.first;
}

ListMap::~ListMap() {

	clear();
	delete first;
}

std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry) {

	iterator it = find(entry.first);
	if(it != end())
		return std::make_pair(it, false);
	else
		return std::make_pair(unsafe_insert(entry), true);
}


ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry) {

	Node* toBeInserted = new Node(entry);
	toBeInserted->next = first->next;

	//sentinel
	toBeInserted->prev = first;
	first->next = toBeInserted;

	return begin();
}

ListMap::iterator ListMap::find(const Key& k) {

	return iterator(static_cast<const ListMap*>(this)->find(k).node);
}

ListMap::const_iterator ListMap::find(const Key& k) const {

	for(const_iterator it = begin(); it != end(); ++it)
			if(it->first == k)
				return it;

		return end();
}

ListMap::Val& ListMap::operator[](const Key& k) {

	return insert(std::make_pair(k, "")).first->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty() const {

	return size() == 0;
}

ListMap::size_type ListMap::size() const {

	const_iterator it = begin(), e = end();
	int size = 0;
	while(it++ != e)
		++size;

	return size;
}

ListMap::size_type ListMap::count(const Key& _Key) const {

	if(find(_Key) != end())
		return 1;

	return 0;
}

ListMap::iterator ListMap::erase(ListMap::iterator it) {

	if(it == end())
		return it;

	Node* node = it.node;
	Node* next = it.node->next;
	Node* prev = nullptr;
	if(node == first->next)
		prev = first;
	else
		prev = (--it).node;

	prev->next = next;
	delete node;

	return iterator(next);
}

ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l) {

	if(f == end())
		return f;

	Node* node = f.node;
	Node* prev;
	if(f == begin())
		prev = first;
	else
		(--f).node;

	Node* next = l.node;

	prev->next = next;
	while(node->next != next) {

		Node* tmp = node;
		node = node->next;
		delete tmp;
	}

	return l;
}

ListMap::size_type ListMap::erase(const Key& key) {

	iterator it = find(key);
	if(it == end())
		return 0;

	erase(it);
	return 1;
}

void ListMap::clear() {

	Node* head = first->next;
	while(head != first) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
	first->next = first;
}

//	===	equality	================================================================================================

bool ListMap::struct_eq(const ListMap& that) const {

	ListNode *thisNode = first;
	ListNode *thatNode = that.first;

	//	Both maps are empty
	if (thisNode->next == thisNode && thatNode->next == thatNode)
		return true;

	//	One of them is empty
	if (thisNode->next == thisNode || thatNode->next == thatNode)
		return false;

	while(true)	{
		thisNode = thisNode->next;
		thatNode = thatNode->next;

		//	Checks whether keys are equal
		if (thisNode->data.first != thatNode->data.first)
			return false;

		// if both maps end then they are equal
		if (thisNode->next == first && thatNode->next == that.first)
			return true;

		// but if only one of them ends, they differ
		if (thisNode->next == first || thatNode->next == first)
			return false;
	}
}

bool ListMap::info_eq(const ListMap& that) const {

	ListNode *thisNode = first;
	ListNode *thatNode = that.first;

	//	Both maps are empty
	if (thisNode->next == thisNode && thatNode->next == thatNode)
		return true;

	//	One of them is empty
	if (thisNode->next == thisNode || thatNode->next == thatNode)
		return false;

	while(true)	{
		thisNode = thisNode->next;
		thatNode = thatNode->next;

//		//	Checks whether keys are equal
//		if (thisNode->data != thatNode->data)
//			return false;

		//	Checkks whether a pair exists in the second map
		auto it = that.find(thisNode->data.first);
		if(thisNode->data.second != it->second)
			return false;

		// if both maps end then they are equal
		if (thisNode->next == first && thatNode->next == that.first)
			return true;

		// but if only one of them ends, they differ
		if (thisNode->next == first || thatNode->next == first)
			return false;
	}
}

//	===	begin & end	================================================================================================

ListMap::iterator ListMap::begin() {

	return iterator(first->next);
}

ListMap::const_iterator ListMap::begin() const {

	return const_cast<ListMap*>(this)->begin();
}

ListMap::iterator ListMap::end() {

	return iterator(first->prev);
}

ListMap::const_iterator ListMap::end() const {

	return const_cast<ListMap*>(this)->end();
}

//	===	iterator	=================================================================================================

// pre
ListMap::const_iterator& ListMap::const_iterator::operator++() {

	if(node != node->prev)
		node = node->next;

	return *this;
}

// post
ListMap::const_iterator ListMap::const_iterator::operator++(int) {

	const_iterator tmp = *this;
	++(*this);
	return tmp;
}

//pre
ListMap::const_iterator& ListMap::const_iterator::operator--() {


	Node* head = node->prev->next;

	if(head == node)
		return *this;

	while(head->next != node)
		head = head->next;
	node = head;
	return *this;
}

// post
ListMap::const_iterator ListMap::const_iterator::operator--(int) {

	const_iterator tmp = *this;
	--(*this);
	return tmp;
}

//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

void test() {

}

