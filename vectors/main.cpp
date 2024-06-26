#include<iostream>
#include<vector>

using namespace std;

int main(){
    /*
     * A vector is like an array, but it has more functionality,
     * it allows to dynamically change the size, i don't have to
     * define the size of the vector at the beginning;
     */
    vector<int> v1 = {1, 2, 3};
    v1.push_back(3);
    v1.push_back(3);
//    v1.pop_back();
    cout << "vector v1: " << v1[4] << endl;
    v1.shrink_to_fit();
    cout << v1.capacity() << endl;
    return 0;
}