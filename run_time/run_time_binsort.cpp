#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

#define NARRAY 7   // Array size
#define NBin 6  // Number of Bins
#define INTERVAL 10  // Each Bin capacity

struct Node {
  int data;
  struct Node *next;
};

void BinSort(int arr[]);
struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBins(struct Node *list);
int getBinIndex(int value);

// Sorting function
void BinSort(int arr[]) {
  int i, j;
  struct Node **Bins;

  // Create Bins and allocate memory size
  Bins = (struct Node **)malloc(sizeof(struct Node *) * NBin);

  // Initialize empty Bins
  for (i = 0; i < NBin; ++i) {
    Bins[i] = NULL;
  }

  // Fill the Bins with respective elements
  for (i = 0; i < NARRAY; ++i) {
    struct Node *current;
    int pos = getBinIndex(arr[i]);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = Bins[pos];
    Bins[pos] = current;
  }

  // Print the Bins along with their elements
  for (i = 0; i < NBin; i++) {
    cout << "Bin[" << i << "] : ";
    printBins(Bins[i]);
    cout << endl;
  }

  // Sort the elements of each Bin
  for (i = 0; i < NBin; ++i) {
    Bins[i] = InsertionSort(Bins[i]);
  }

  cout << "-------------" << endl;
  cout << "Bins after sorted" << endl;
  for (i = 0; i < NBin; i++) {
    cout << "Bin[" << i << "] : ";
    printBins(Bins[i]);
    cout << endl;
  }

  // Put sorted elements on arr
  for (j = 0, i = 0; i < NBin; ++i) {
    struct Node *node;
    node = Bins[i];
    while (node) {
      arr[j++] = node->data;
      node = node->next;
    }
  }

  for (i = 0; i < NBin; ++i) {
    struct Node *node;
    node = Bins[i];
    while (node) {
      struct Node *tmp;
      tmp = node;
      node = node->next;
      free(tmp);
    }
  }
  free(Bins);
  return;
}

// Function to sort the elements of each Bin
struct Node *InsertionSort(struct Node *list) {
  struct Node *k, *nodeList;
  if (list == 0 || list->next == 0) {
    return list;
  }

  nodeList = list;
  k = list->next;
  nodeList->next = 0;
  while (k != 0) {
    struct Node *ptr;
    if (nodeList->data > k->data) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = nodeList;
      nodeList = tmp;
      continue;
    }

    for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
      if (ptr->next->data > k->data)
        break;
    }

    if (ptr->next != 0) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = ptr->next;
      ptr->next = tmp;
      continue;
    } else {
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return nodeList;
}

int getBinIndex(int value) {
  return value / INTERVAL;
}

// Print Bins
void print(int ar[]) {
  int i;
  for (i = 0; i < NARRAY; ++i) {
    cout << setw(3) << ar[i];
  }
  cout << endl;
}

void printBins(struct Node *list) {
  struct Node *cur = list;
  while (cur) {
    cout << setw(3) << cur->data;
    cur = cur->next;
  }
}

// Driver code
int main(void) {
    mt19937 gen(std::random_device{}());
    uniform_int_distribution<int> dist(1, 1000000);
    for (int n = 100; n <= 1000; n += 900) {
        int array[n];
        for (int i = 0; i < n; i++) {
            array[i] = dist(gen);
        }

        auto start = chrono::high_resolution_clock::now();
        BinSort(array);
        auto end = chrono::high_resolution_clock::now();

        cout << "n = " << n << ", elapsed time: " << chrono::duration_cast<chrono::seconds>(end - start).count()<<endl;

    }
//    int array[NARRAY] = {42, 32, 33, 52, 37, 47, 51};
//    cout << "Initial array: " << endl;
//    print(array);
//    cout << "-------------" << endl;
//    BinSort(array);
//    cout << "-------------" << endl;
//    cout << "Sorted array: " << endl;
//    print(array);
}
