//
// Created by suman on 6/26/24.
//
#include <iostream>
#include <string>
using namespace std;

int main(){
    int a = 2;
    /*
    b is a reference of a, if we modify b, then a is also modified
     */
    int &b = a;
    int &c = b;
    c = 3;
    cout << a <<endl;
    cout << b << endl;
    cout << c << endl;
    bool x = true;
    bool &y = x;

    cout << x << " " << y << endl;
    /*
     access the memory address/identifier of a variable using ampersand sign*/
    cout << "memory location of c: " << &a << endl;
    cout << "memory location of a: " << &b << endl;
    cout << "memory location of b: " << &c << endl;
    cout << "memory location of x and y" << &x << endl << &y;
    string sample_string = "hello world";
    cout << endl << "sample string " << sample_string;
    return 0;
}