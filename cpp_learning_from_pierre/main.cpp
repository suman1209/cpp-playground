#include<iostream>
#include "util.h"


int main(){
    int x = 5;
    int y = 6;
    int z = add(x, y);
    std::cout << "addition of two numbers: " << z;
    return z;
}