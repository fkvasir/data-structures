#include <iostream>
#include <assert.h>

using namespace std;


struct Link
{
  int head;
  struct Link *tail;
};

int main(){
    struct Link *headLink = new Link;
    assert(headLink != NULL);
    headLink -> head = 1;
    headLink -> tail = NULL;
    Link *tempLink = headLink;
    int num;
    cout << "Enter max number: ";
    cin >> num;
    for (int i = headLink->head + 1; i <= num; i++)
    {
        Link *newLink = new Link;
        assert(newLink != NULL);
        newLink -> head = i;
        newLink ->tail = headLink;
        tempLink -> tail = newLink;
        tempLink = newLink;
        
    }
    int size;
    cout << "Enter size: ";
    cin >> size;
    tempLink = headLink;
    for (int i = headLink -> head + 1; i <= size; i++)
    {
        cout << tempLink -> head << "  ";
        cout << tempLink -> head << " : " << tempLink -> tail<< endl;
        tempLink = tempLink -> tail;
        
    }
    if (tempLink -> tail == NULL)
    {
        cout << "Invalid";
    }
    if (Link *tempLink= tempLink -> tail)
    {
        for (int i = headLink-> head + 1; i <= num; i++)
        {
        delete tempLink;
        tempLink = tempLink -> head;
        }
    }
    return 0;
}
