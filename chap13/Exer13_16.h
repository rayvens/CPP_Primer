#ifndef EXER13_14_H
#define EXER13_14_H
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;
struct numbered {
	numbered() : mysn(rand()) {}
	numbered(const numbered&) : mysn(rand()) {}
	int mysn = 0;
};
void f(const numbered &s) { cout << s.mysn << endl; } // correct implementation
#endif