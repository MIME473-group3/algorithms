all : asd asd3

CXXFLAGS:= -O3 -DNDEBUG -std=c++11

#CXXFLAGS:= -g3 -std=c++11

asd : test.cc
	g++ ${CXXFLAGS} test.cc timer.cc ../../lib/aisdi/libtest_hash.so -o asd 
asd3 : test.cc
	g++ ${CXXFLAGS} test.cc timer.cc ../../lib/aisdi/libtest_hash3.so -o asd3 
	
clean :
	rm asd
	rm asd3
debug :
	g++ -g3 -std=c++11 test.cc timer.cc ../../lib/aisdi/libtest_hash.so -o asd_debug 

view:
	lynx /materialy/AISDI/hash/info/index.html
