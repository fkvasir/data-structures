#include <iostream>
#include <assert.h>

using namespace std;


struct Link
{
  int value;
  struct Link *nextlink;
};



int main(){
    struct Link *headLink = new Link;
    
    assert(headLink != NULL);
    
    headLink -> value = 1;
    headLink -> nextlink = NULL;
    Link *tempLink = headLink;
    
    for (int i = 2; i <= 3; i++)
    {
        Link *newLink = new Link;
        assert(newLink != NULL);
        
        newLink -> value = i;
        newLink ->nextlink = headLink;
        
        
        tempLink -> nextlink = newLink;
        tempLink = newLink;
        
    }
   
    int size;
    cout << "Enter size: ";
    cin >> size;
    tempLink = headLink;
    
    for (int i = 1; i <= size; i++)
    {
        cout << tempLink -> value;
        tempLink = tempLink -> nextlink;
        
    }
    
    
    for (int i = 1; i <= 3; i++)
    {
        Link *tempLink_1 = tempLink -> nextlink;
        delete tempLink;
        tempLink = tempLink_1;
    }
    return 0;
}
