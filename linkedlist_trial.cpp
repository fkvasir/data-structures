#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
    int value;
    linkedlist * next;

};

int main(void)
{
    int counter, i;

    linkedlist * head = new(linkedlist);
    head->value = 1;

    for (i=1, i<3; i++)
    {
        ptr next=new(linkedlist);
        ptr next->value = i+1;
        ptr = ptr -> next
    }
    ptr->next=head;
    ptr = head;
    cout<<"Enter number of times: ";
    cin << counter
    for (i=1; i<counter; i++)
    {
        cout<< ptr-> value << "  ";
        ptr = ptr -> next;
        assert(head != NULL);
    }
    delete head;
return 0;
}
