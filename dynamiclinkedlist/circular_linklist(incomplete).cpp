#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
  int value;
  struct Node *nextnode;
};

int main()
{
  struct Node *nextnode;
  struct Node *headnode = new Node;

  headnode->value = 1;
  headnode = NULL;

  Node *tempnode = headnode;

  do
  {
    int i = 1;
    Node *nextnode = new Node;
    assert(new Node != NULL);
    ++i;
    new Node->value = i;
    new Node->nextnode = headnode;
    tempnode->nextnode = new Node;
    tempnode = new Node;
  } while (int i <= 3);
  tempnode = headnode;

  return i;
}
