#include <iostream>
using namespace std;

struct Node {
  int value;
  struct Node* next;
};

int i, n;

int main() {
    Node* hold;
    Node* one = NULL;
    Node* two = NULL;
    Node* three = NULL;
    Node* four = NULL;
    Node* five = NULL;

    one = new Node();
    two = new Node();
    three = new Node();
    four = new Node();
    five = new Node ();


    one->value = 1;
    two->value = 2;
    three->value = 3;
    four->value = 4;
    five-> value =5;

    one->next = two;
    two->next = three;
    three->next = four;
    four->next = five;
    five -> next = one;

    cout<<"Input: ";
    cin>>n;

    hold = one;
    int size;
    cout<< "Enter size: ";
    cin >> size;
    for(i=0;i<size;i++)
    {
        cout<<hold->value<<"  ";
        hold = hold->next;
    }

    delete one;
    delete two;
    delete three;
    return 0;
}


