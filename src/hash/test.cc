#include <map>
#include <string>
using namespace std;
 
#if 1
 #include "aisdihashmap.h"

template<>
int AISDIHashMap<std::string, int>::InnerList::NodeCounter::count = 0;

static AISDIHashMap<string, int> m;

#else
 static map<string, int> m;
#endif

#ifdef _SUNOS
#include "/materialy/AISDI/hash/maptester.h"
#else
#include "maptester.h"
#endif

bool MapTester::insert(const string& s, int i) {return (m.insert(make_pair(s, i))).second;}
unsigned MapTester::remove(const string& s) {return (unsigned)m.erase(s);}
void MapTester::modifyOrAdd(const string& s, int i) {m[s]=i;}
int MapTester::read(const string& s) {return m[s];}
bool MapTester::find(const string& s) { return m.find(s)!=m.end(); }
size_t MapTester::size() { return m.size(); }
