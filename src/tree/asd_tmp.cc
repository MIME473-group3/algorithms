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
#include "tree/TreeMap.h" 
#else
#include "TreeMap.h"
#endif

/// A helper class.
// {{{
class TreeMapDetail //Helper
{
protected:
    friend class TreeMap;

    /// Stupid example of a method that modifies a protected field in 
    /// the TreeMap class. Feel free to remove this method or add new
    /// ones here.
    static void erase(TreeMap* tm, const TreeMap::K& k)
    {
//std::cout<<"sth is going wrong"<<std::endl;
        tm->root_=NULL; // we just modified a protected field in tree map
    }
    static void testTree(TreeMap* tm)
    {
        TreeNode * n = tm->root_;
        while (n)
        {
            if (n->left_)
                n = n->left_;
            else if (n->right_)
                n = n->right_;
            else
            {
                TreeNode * n2 = n->parent_;
                if (n2)
                {
                    if (n2->left_ != n && n2->right_ != n)
                        std::cout << "Fail! in " << n->data_.first;
                }
                n = n2;
            }
        }
/*
        for (TreeMap::iterator it = tm->begin(); it != tm->end(); ++it)
        {
            std::cout << "test: " << it.node_ << std::endl;
            if (it.node_->parent_)
            {
                std::cout << "parent_: " << it.node_->parent_->left_ << ", " << it.node_->parent_->right_ << std::endl;
            }
        }
*/
    }
};
// }}}

void print(const std::pair<int, std::string>& p);

//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

/* ORDER
 * preorder -1
 * inorder 0
 * postorder 1 // not implemented yet
 */
#define ORDER 0
TreeNode * last = NULL;

TreeMap::TreeMap()
{
    root_ = NULL;
};

/// Content of existing TreeMap object is copied into the new object. 
TreeMap::TreeMap( const TreeMap& m )
{
    ///@todo Implement this
    root_ = NULL;
    *this = m;
};

TreeMap::~TreeMap()
{
    clear();
};

// Inserts an element into the map.
// @returns A pair whose bool component is true if an insertion was
//             made and false if the map already contained an element
//             associated with that key, and whose iterator component coresponds to
//             the address where a new element was inserted or where the element
//             was already located.
std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<K, V>& entry)
{
    ///@todo Finnish this
    //iterator i;
    //for(i=begin(); i!=end(); ++i)
    //{
    //    if(i->first==entry.first)
    //      return std::make_pair(i, (bool)false);
    //}
    //      return std::make_pair(i, (bool)false);
    iterator it = find(entry.first);
    if (it == end())
    {
        return std::make_pair(unsafe_insert(entry), true);
    }
    else
    {
        return std::make_pair(it, false);
    }
}

// Inserts an element into the map.
// This method assumes there is no value asociated with
// such a key in the map.
TreeMap::iterator TreeMap::unsafe_insert(const std::pair<K, V>& entry)
{
    ///@todo Finnish this
    //assert(0);
    //return iterator(root_);
    if (!root_) {
        root_ = new Node(entry);

        ++size_;
        return iterator(root_);
    }
    Node * n = root_;
    while (true)
    {
        if (entry.first < n->data_.first)
        {
            if (n->left_)
                n = n->left_;
            else
            {
                n->left_ = new Node(entry, n);
                n = n->left_;
                break;
            }
        }
        else
        {
            if (n->right_)
                n = n->right_;
            else
            {
                n->right_ = new Node(entry, n);
                n = n->right_;
                break;
            }
        }
    }
    ++size_;
    return iterator(n);
}

// Returns an iterator addressing the location of the entry in the map
// that has a key equivalent to the specified one or the location succeeding the
// last element in the map if there is no match for the key.
TreeMap::iterator TreeMap::find(const K& k)
{
    ///@todo Implement this
    //assert(0);
    //return end();
    if (!root_) return end();
    Node * n = root_;
    while (n && n->data_.first != k)
    {
        if (k < n->data_.first)
            n = n->left_;
        else
            n = n->right_;
    }
    return iterator(n);
}

TreeMap::const_iterator TreeMap::find(const K& k) const
{
    ///@todo Implement this
    //assert(0);
    //return end();
    if (!root_) return end();
    Node * n = root_;
    while (n && n->data_.first != k)
    {
        if (k < n->data_.first)
            n = n->left_;
        else
            n = n->right_;
    }
    return const_iterator(n);
}

// Inserts an element into a map with a specified key value
// if one with such a key value does not exist.
// @returns Reference to the value component of the element defined by the key.
TreeMap::V& TreeMap::operator[](const K& k)
{
    ///@todo Implement this
    //assert(0);
    //iterator i;
    //return i->second;
    return insert(P(k, "tmp")).first->second;
}

// Tests if a map is empty.
bool TreeMap::empty( ) const
{
    return root_==NULL;
}

// Returns the number of elements in the map.
TreeMap::size_type TreeMap::size( ) const
{
    ///@todo Implement this
    //assert(0);
    int size = 0;
    iterator it = begin();
    while (it != end())
    {
        ++size;
        ++it;
    }
    return size;
}

// Returns the number of elements in a map whose key matches a parameter-specified key.
TreeMap::size_type TreeMap::count(const K& _Key) const
{
    ///@todo Implement this
    if (find(_Key) != end())
        return 1;  // this is not a multimap
    return 0;
}

// Removes an element from the map.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator i)
{
    ///@todo Implement this
    //assert(0);
    //return end();
    if (i == end())
        return i;
    iterator it(i);
    ++it;
    if (erase(i->first))
        return it;
    return i;
}

// Removes a range of elements from the map.
// The range is defined by the key values of the first and last iterators
// first is the first element removed and last is the element just beyond the last elemnt removed.
// @returns The iterator that designates the first element remaining beyond any elements removed.
TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l)
{
    ///@todo Implement this
    //assert(0);
    //return end();
    while (f != l && f != end())
    {
        f = erase(f);
    }
    return f;
}

// Removes an element from the map.
// @returns The number of elements that have been removed from the map.
//             Since this is not a multimap itshould be 1 or 0.
TreeMap::size_type TreeMap::erase(const K& key)
{
    ///@todo Implement this
    //assert(0);
    //return 0;
    if (!root_) return 0;
    Node * n = root_;
    while (n && n->data_.first != key)
    {
        if (key < n->data_.first)
            n = n->left_;
        else
        {
            n = n->right_;
        }
    }
    if (!n)
        return 0;
    if (n->left_ && n->right_)
    {
        Node * n2 = n->right_;
        while (n2->left_)
        {
            n2 = n2->left_;
        }
        if (n2->parent_ != n)
        {
            n2->parent_->left_ = n2->right_;
            if (n2->right_)
                n2->right_->parent_ = n2->parent_;
            n2->right_ = n->right_;
            n2->right_->parent_ = n2;
        }
        n2->left_ = n->left_;
        n2->left_->parent_ = n2;
        n2->parent_ = n->parent_;
        if (n->parent_)
        {
            if (n->parent_->left_ == n)
                n2->parent_->left_ = n2;
            else
                n2->parent_->right_ = n2;
        }
        else
        {
            root_ = n2;
        }
    }
    else if (n->left_)
    {
        if (n->parent_)
        {
            if (n->parent_->left_ == n)
                n->parent_->left_ = n->left_;
            else
                n->parent_->right_ = n->left_;
            n->left_->parent_ = n->parent_;
        }
        else
        {
            root_ = n->left_;
            root_->parent_ = NULL;
        }
    }
    else if (n->right_)
    {
        if (n->parent_)
        {
            if (n->parent_->left_ == n)
                n->parent_->left_ = n->right_;
            else
                n->parent_->right_ = n->right_;
            n->right_->parent_ = n->parent_;
        }
        else
        {
            root_ = n->right_;
            root_->parent_ = NULL;
        }
    }
    else
    {
        if (n->parent_)
        {
            if (n->parent_->left_ == n)
                n->parent_->left_ = NULL;
            else
                n->parent_->right_ = NULL;
        }
        else
            root_ = NULL;
    }
    delete n;
    return 1;
}

// Erases all the elements of a map.
void TreeMap::clear( )
{
    //TreeMapDetail::erase(this, 0);  /// Stupid helper usage example
    ///@todo Implement this
    //assert(0);
    Node * n = root_;
    while (n)
    {
        if (n->left_)
            n = n->left_;
        else if (n->right_)
            n = n->right_;
        else
        {
            Node * n2 = n->parent_;
            if (n2)
            {
                if (n2->left_ == n)
                    n2->left_ = NULL;
                else
                    n2->right_ = NULL;
            }
            delete n;
            n = n2;
        }
    }
    root_ = NULL;
}

bool TreeMap::struct_eq(const TreeMap& another) const
{
    ///@todo Implement this
    //assert(0);
    //return false;
    if (size() != another.size())
        return false;
    iterator it = begin();
    iterator it2 = another.begin();
    while (it != end() && it2 != another.end() && *it == *it2
        && !((it.node_->parent_?1:0) xor (it2.node_->parent_?1:0)) && (!it.node_->parent_ || it.node_->parent_->data_ == it2.node_->parent_->data_)
        && !((it.node_->left_?1:0) xor (it2.node_->left_?1:0)) && (!it.node_->left_ || it.node_->left_->data_ == it2.node_->left_->data_)
        && !((it.node_->right_?1:0) xor (it2.node_->right_?1:0)) && (!it.node_->right_ || it.node_->right_->data_ == it2.node_->right_->data_)
        )
    {
        it++;
        it2++;
    }
    if (it == end() && it2 == another.end())
        return true;
    return false;
}

bool TreeMap::info_eq(const TreeMap& another) const
{
    ///@todo Implement this
    //assert(0);
    if (size() != another.size())
        return false;
    for (iterator it = begin(); it != end(); ++it)
    {
        if (another.find(it->first) == another.end())
            return false;
    }
    return true;
}

// preincrement
TreeMap::const_iterator& TreeMap::const_iterator::operator ++()
{
    ///@todo Implement this
#if ORDER==0
    if (node_)
    {
        if (node_->right_)
        {
            node_ = node_->right_;
            while (node_->left_)
                node_ = node_->left_;
        }
        else
        {
            last = node_;
            Node * n = node_->parent_;
            while (n && n->right_ == node_)
            {
                node_ = n;
                n = n->parent_;
            }
            node_ = n;
            if (node_)
                last = node_;
        }
    }
#elif ORDER == -1
    if (node_)
    {
        if (node_->left_)
            node_ = node_->left_;
        else if (node_->right_)
            node_ = node_->right_;
        else
        {
            bool end = false;
            Node * n = node_;
            while (node_->parent_)
            {
                if (node_->parent_->left_ == node_ && node_->parent_->right_)
                {
                    node_ = node_->parent_->right_;
                    break;
                }
                else
                    node_ = node_->parent_;
            }
            if (!node_->parent_)
                node_ = NULL;
        }
    }
#endif
    return *this;
}

// postincrement
TreeMap::const_iterator TreeMap::const_iterator::operator++(int)
{
    ///@todo Implement this
    iterator temp = *this;
    ++*this;
    return temp;
}

// predecrement
TreeMap::const_iterator& TreeMap::const_iterator::operator--()
{
    ///@todo Implement this
#if ORDER == 0
    if (node_)
    {
        if (node_->left_)
        {
            node_ = node_->left_;
            while (node_->right_)
                node_ = node_->right_;
        }
        else
        {
            Node * n = node_->parent_;
            while (n && n->left_ == node_)
            {
                node_ = n;
                n = n->parent_;
            }
            node_ = n;
        }
    }
    else
    {
        node_ = last;
    }
#elif ORDER == -1
    assert(0);
#endif
    return *this;
}

// postdecrement
TreeMap::const_iterator TreeMap::const_iterator::operator--(int)
{
    ///@todo Implement this
    const_iterator temp = *this;
    --*this;
    return temp;
}


/// Assignment operator copy the source elements into this object.
TreeMap& TreeMap::operator=(const TreeMap& m)
{
    ///@todo Implement this
    //assert(0);
    if (&m == this)
        return *this;
    clear();
    Node * node_ = m.root_;
    while (node_)
    {
        unsafe_insert(node_->data_);
        if (node_->left_)
            node_ = node_->left_;
        else if (node_->right_)
            node_ = node_->right_;
        else
        {
            bool end = false;
            Node * n = node_;
            while (node_->parent_)
            {
                if (node_->parent_->left_ == node_ && node_->parent_->right_)
                {
                    node_ = node_->parent_->right_;
                    break;
                }
                else
                    node_ = node_->parent_;
            }
            if (!node_->parent_)
                node_ = NULL;
        }
    }
    return *this;
}
        
/// Returns an iterator addressing the first element in the map
TreeMap::iterator TreeMap::begin()
{ 
    ///@todo Implement this
    if (!root_) return end();
    Node * n = root_;
#if ORDER == 0 || ORDER == 1
    if (n)
        while (n->left_)
            n = n->left_;
#endif
    return iterator(n);
}

TreeMap::const_iterator TreeMap::begin() const
{ 
    ///@todo Implement this
    if (!root_) return end();
    Node * n = root_;
#if ORDER == 0 || ORDER == 1
    if (n)
        while (n->left_)
            n = n->left_;
#endif
    return const_iterator(n);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::iterator TreeMap::end()
{ 
    ///@todo Implement this
    return iterator(NULL);
}

/// Returns an iterator that addresses the location succeeding the last element in a map
TreeMap::const_iterator TreeMap::end() const
{ 
    ///@todo Implement this
    return const_iterator(NULL);
}

//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void print(const std::pair<int, std::string>& p)
{
    std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// The big mean test function ;)
void test()
{
    // A typedef used by the test.
    //typedef std::map<int, std::string> TEST_MAP;
    //typedef SmallMap<int, std::string> TEST_MAP;
    typedef TreeMap TEST_MAP;

    std::cout << "Testy uzytkownika" << std::endl;

          TEST_MAP m;  
    
    /*
    m[2] = "Merry";
    m[4] = "Jane";
    m[8] = "Korwin";
    m[4] = "Magdalena";
    */

    m[8] = "8";
    m[6] = "6";
    m[13] = "13";
    m[2] = "2";
    m[7] = "7";
    m[0] = "0";
    m[1] = "1";
    m[5] = "5";
    m[4] = "4";
    m[3] = "3";
    m[10] = "10";
    m[9] = "9";
    m[11] = "11";
    m[12] = "12";
    m[14] = "14";

    TEST_MAP m2(m);
    for_each(m.begin(), m.end(), print );
    for_each(m2.begin(), m2.end(), print );

    std::cout << "m2(m)" << std::endl;
    std::cout << "m info_eq m2: " << m.info_eq(m2) << std::endl;
    std::cout << "m struct_eq m2: " << m.struct_eq(m2) << std::endl;

    m2[15] = "15";

    std::cout << "m2[15] = 15" << std::endl;
    std::cout << "m info_eq m2: " << m.info_eq(m2) << std::endl;
    std::cout << "m struct_eq m2: " << m.struct_eq(m2) << std::endl;

    m2.erase(8);
    m2.erase(15);
    m2[8] = "8";

    std::cout << "m2.erase(8)" << std::endl;
    std::cout << "m info_eq m2: " << m.info_eq(m2) << std::endl;
    std::cout << "m struct_eq m2: " << m.struct_eq(m2) << std::endl;

    m2 = m;

    std::cout << "m2 = m" << std::endl;
    std::cout << "m info_eq m2: " << m.info_eq(m2) << std::endl;
    std::cout << "m struct_eq m2: " << m.struct_eq(m2) << std::endl;

    m2[15] = "15";

    std::cout << "m2[15] = 15" << std::endl;
    std::cout << "m info_eq m2: " << m.info_eq(m2) << std::endl;
    std::cout << "m struct_eq m2: " << m.struct_eq(m2) << std::endl;

    m2.erase(8);
    m2.erase(15);
    m2[8] = "8";

    std::cout << "m2.erase(8)" << std::endl;
    std::cout << "m info_eq m2: " << m.info_eq(m2) << std::endl;
    std::cout << "m struct_eq m2: " << m.struct_eq(m2) << std::endl;

/*
    m.erase(2);
    m.erase(10);
    m.erase(7);
    m.erase(6);
    m.erase(13);
*/
    while (m.begin() != m.end())
    {
        m.erase(m.begin()->first);
    }

    for_each(m.begin(), m.end(), print );
    //system("PAUSE");
}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /home/common/dyd/aisdi/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//    std::cout << "AISDI cwiczenie 4: wchodze do funkcji main." << std::endl;
//    test();
//    // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//    Test2();
//    //system("PAUSE");
//    return EXIT_SUCCESS;
//}
