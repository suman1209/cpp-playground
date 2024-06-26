#include <iostream>
using namespace std;
#include<list>

class YouTubeChannel{
public:
    string Name;
    string OwnerName;
    int SubscribersCount;
    list<string> PublishedVideoTitles;

    YouTubeChannel(string name, string ownerName){
        Name = name;
        OwnerName = ownerName;
        SubscribersCount = 0;
    }

    void print_info(){
        cout << "Name: " << Name << endl;
        cout << "OwnerName: " << OwnerName << endl;
        cout << "SubscriberCount: " << SubscribersCount << endl;
    }
};

int main(){
    YouTubeChannel ytChannel("Suman", "Suman Navaratnarjah");
    ytChannel.SubscribersCount = 1000000;
    ytChannel.PublishedVideoTitles = {"deep learning", "robotics"};
    ytChannel.print_info();
}