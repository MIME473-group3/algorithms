/*
 * initializer.cpp
 *
 *  Created on: 21 Jul 2014
 *      Author: adam
 */

// Initializer list example

struct B {
  int b;
  B(int i = 0) : b(i) {}
};

struct C : B {
  using B::B;
};

struct D : B  {
  D(int i) : B(i) {}
};



int main () {
  D d = {1};
  C c = {1};
}

