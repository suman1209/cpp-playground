#include<iostream>
using namespace std;

int main(){
    int x[] = {4, 5, 6};
    int *head = x;
    for(int i = 0; i < 3; i++){
        cout << "head: " << head << endl;
        cout << "value that head points to: " << *head << endl;
        head ++;
    }
    return 0;
}