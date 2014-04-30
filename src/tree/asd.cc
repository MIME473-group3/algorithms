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
		tm->root = NULL; // we just modified a protected field in tree map
	}
};

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

TreeMap::TreeMap() {
	root = NULL;
}

TreeMap::TreeMap(const TreeMap& m) {
}

TreeMap::~TreeMap() {
	clear();
}

std::pair<TreeMap::iterator, bool> TreeMap::insert(
		const std::pair<K, V>& entry) {
	///@todo Finnish this
	iterator i;
	for (i = begin(); i != end(); ++i) {
		if (i->first == entry.first)
			return std::make_pair(i, (bool) false);
	}
	return std::make_pair(i, (bool) false);
}

TreeMap::iterator TreeMap::unsafe_insert(const std::pair<K, V>& entry) {
	///@todo  Finnish this
	assert(0);
	return iterator(root);
}

TreeMap::iterator TreeMap::find(const K& k) {
	assert(0);
	return end();
}

TreeMap::const_iterator TreeMap::find(const K& k) const {
	assert(0);
	return end();
}

TreeMap::V& TreeMap::operator[](const K& k) {
	///@todo Implement this
	assert(0);
	iterator i;
	return i->second;
}

bool TreeMap::empty() const {
	return root == NULL;
}

TreeMap::size_type TreeMap::size() const {
	///@todo Implement this
	assert(0);
	return 0;
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
	assert(0);
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
	return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int) {
	return *this;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--() {
	///@todo Implement this
	return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int) {
	return *this;
}

TreeMap& TreeMap::operator=(const TreeMap& other) {
	return *this;
}

TreeMap::iterator TreeMap::begin() {
	return iterator(NULL);
}

TreeMap::const_iterator TreeMap::begin() const {
	return iterator(NULL);
}

TreeMap::iterator TreeMap::end() {
	return iterator(NULL);
}

TreeMap::const_iterator TreeMap::end() const {
	return iterator(NULL);
}
