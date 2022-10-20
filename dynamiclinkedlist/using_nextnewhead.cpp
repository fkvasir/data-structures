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
    
    for (int i = 2; i <= 3; i++)
    {
        Link *newLink = new Link;
        assert(newLink != NULL);
        
        newLink -> head = i;
        newLink ->tail = headLink;
        
        
        tempLink -> tail = newLink;
        tempLink = newLink;
        
    }
   
    int size = 10;
    cout << "Enter size: ";
    cin >> size;
    tempLink = headLink;
    
    for (int i = 1; i <= size; i++)
    {
        cout << tempLink -> head << "  ";
        tempLink = tempLink -> tail;
        
    }
    
    
    for (int i = 1; i <= 3; i++)
    {
        Link *tempLink_1 = tempLink -> tail;
        delete tempLink;
        tempLink = tempLink_1;
    }
    return 0;
}
