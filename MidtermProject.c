#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure for the tree
typedef struct Node {
  int key;
  struct Node *left, *right;
} Node;

// Function to create a new node
Node* createNode(int key) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->key = key;
  newNode->left = newNode->right = NULL;
  return newNode;
}

// Function to insert a node into a binary search tree
Node* insert(Node* root, int key) {
  if (root == NULL) 
    return createNode(key);

  if (key < root->key)
      root->left = insert(root->left, key);
  else if (key > root->key)
      root->right = insert(root->right, key);

  return root;
}

// Function to delete a node with the minimum key value
Node* deleteMin(Node* root) {
  if (root == NULL) 
    return NULL;
  if (root->left == NULL) {
      Node* temp = root->right;
      free(root);
      return temp;
  }

  root->left = deleteMin(root->left);
  return root;
}

// Function to delete a node with a specific key value
Node* deleteNode(Node* root, int key) {
  if (root == NULL) 
    return NULL;
  if (key < root->key)
      root->left = deleteNode(root->left, key);
  else if (key > root->key)
      root->right = deleteNode(root->right, key);
  else {
      if (root->left == NULL) {
          Node* temp = root->right;
          free(root);
          return temp;
      } else if (root->right == NULL) {
          Node* temp = root->left;
          free(root);
          return temp;
      }

      Node* temp = root->right;
      while (temp->left != NULL)
          temp = temp->left;

      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

typedef struct AVLNode {
  int key;
  struct AVLNode *left, *right;
  int height;
} AVLNode;

// Function to create a new AVL node
AVLNode* createAVLNode(int key) {
  AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
  newNode->key = key;
  newNode->left = newNode->right = NULL;
  newNode->height = 1;
  return newNode;
}

// Function to get the height of a node
int getHeight(AVLNode* node) {
  if (node == NULL) return 0;
  return node->height;
}

// Function to calculate the balance factor of a node
int getBalance(AVLNode* node) {
  if (node == NULL) return 0;
  return getHeight(node->left) - getHeight(node->right);
}

int helperUpdateHeight(int a, int b)
{
  if(a>b)
  {
      return a;
  }
  return b;
}

// Function to update the height of a node
void updateHeight(AVLNode* node) {
  if (node != NULL)
      node->height = 1 + helperUpdateHeight(getHeight(node->left), getHeight(node->right));
}

// Function to perform a right rotation
AVLNode* rightRotate(AVLNode* y) {
  AVLNode* x = y->left;
  AVLNode* T2 = x->right;

  x->right = y;
  y->left = T2;

  updateHeight(y);
  updateHeight(x);

  return x;
}

// Function to perform a left rotation
AVLNode* leftRotate(AVLNode* x) {
  AVLNode* y = x->right;
  AVLNode* T2 = y->left;

  y->left = x;
  x->right = T2;

  updateHeight(x);
  updateHeight(y);

  return y;
}

// Function to insert a node into AVL tree
AVLNode* insertAVL(AVLNode* node, int key) {
  if (node == NULL) 
    return createAVLNode(key);

  if (key < node->key)
      node->left = insertAVL(node->left, key);
  else if (key > node->key)
      node->right = insertAVL(node->right, key);
  else
      return node; // Duplicate keys are not allowed

  updateHeight(node);

  int balance = getBalance(node);

  // Left Left Case
  if (balance > 1 && key < node->left->key)
      return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
      return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
  }

  return node;
}




// Function to delete a node with the minimum key value from AVL tree
AVLNode* deleteMinAVL(AVLNode* root) {
  if (root == NULL) 
  return NULL;




  if (root->left == NULL) {
      AVLNode* temp = root->right;
      free(root);
      return temp;
  }




  root->left = deleteMinAVL(root->left);
  return root;
}




// Function to delete a node with a specific key value from AVL tree
AVLNode* deleteNodeAVL(AVLNode* root, int key) {
  if (root == NULL) return NULL;




  if (key < root->key)
      root->left = deleteNodeAVL(root->left, key);
  else if (key > root->key)
      root->right = deleteNodeAVL(root->right, key);
  else {
      if (root->left == NULL) {
          AVLNode* temp = root->right;
          free(root);
          return temp;
      } else if (root->right == NULL) {
          AVLNode* temp = root->left;
          free(root);
          return temp;
      }




      AVLNode* temp = root->right;
      while (temp->left != NULL)
          temp = temp->left;




      root->key = temp->key;
      root->right = deleteNodeAVL(root->right, temp->key);
  }




  if (root == NULL) return root;




  updateHeight(root);




  int balance = getBalance(root);




  // Left Left Case
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);




  // Left Right Case
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }




  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);


  // Right Left Case
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }




  return root;
}




// Function to generate random data for computational experiments
int* generateRandomData(int size) {
  int* data = (int*)malloc(size * sizeof(int));
  for (int i = 0; i < size; ++i)
      data[i] = rand();
  return data;
}




int* generateOrderedData(int size) // for worst case scenarios
{
  int* data = (int*)malloc(size * sizeof(int));
  for (int i = 0; i < size; ++i)
      data[i] = i;
  return data;
}


void freeAVLTree(AVLNode* root) {
  if (root != NULL) {
    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
  }
}


void freeNonAVLTree(Node* root) {
  if (root != NULL) {
    freeNonAVLTree(root->left);
    freeNonAVLTree(root->right);
    free(root);
  }
}




// Function to measure the performance of operations on trees
void measurePerformanceRandomInput(int dataSize) {
    // Generate random data
    int* data = generateRandomData(dataSize);
    printf("NEW TEST Random: %d nodes \n \n", dataSize);

    // Perform operations and measure time for balanced tree (AVL)
    clock_t begin1, end1, begin2, end2;
    // Code for balanced tree operations (insert, delete, delete_min)
    
    begin1 = clock();
    AVLNode* AVLroot = createAVLNode(data[0]);
    for(int i = 1; i < dataSize; i++)
    {
        insertAVL(AVLroot, data[i]);
    }
    end1 = clock();
    double timeDifAVL = ((double) (end1-begin1))/ CLOCKS_PER_SEC;
    printf("The time complexity for assembling the balanced tree is %lf \n \n", timeDifAVL);

    //Call to delete the min node in AVL tree
    begin1 = clock();
    deleteMinAVL(AVLroot);
    end1 = clock();
    timeDifAVL = ((double) (end1-begin1))/ CLOCKS_PER_SEC;
    printf("The time complexity for deleting the MIN-NODE from the balanced tree is %lf \n \n", timeDifAVL);

    // Call for deleting a particular node
    begin1 = clock();
    deleteNodeAVL(AVLroot, data[dataSize/2]);
    end1 = clock();
    timeDifAVL = ((double) (end1-begin1))/ CLOCKS_PER_SEC;
    printf("The time complexity for deleting the middle-NODE from the balanced tree is %lf \n \n", timeDifAVL);
    printf("----------------- \n \n");

    // Perform operations and measure time for unbalanced tree (Binary Search Tree)
    begin2 = clock();
    Node* unbalancedRoot = createNode(data[0]);
    for(int i = 1; i < dataSize; i++)
    {
        insert(unbalancedRoot, data[i]);
    }
    end2 = clock();
    double timeDifNonAVL = ((double)(end2-begin2))/CLOCKS_PER_SEC;
    printf("The time complexity for assembling the unbalanced tree is %lf \n \n", timeDifNonAVL);

    // Code for unbalanced tree operations (insert, delete, delete_min)
    begin2 = clock();
    deleteMin(unbalancedRoot);
    end2 = clock();
    timeDifNonAVL = ((double)(end2-begin2))/CLOCKS_PER_SEC;
    printf("The time complexity for deleting the MIN-NODE from the unbalanced tree is %lf \n \n", timeDifNonAVL);

    begin2 = clock();
    deleteNode(unbalancedRoot, data[dataSize/2]);
    end2 = clock();
    timeDifNonAVL = ((double)(end2-begin2))/CLOCKS_PER_SEC;
    printf("The time complexity for deleting the middle-NODE from the unbalanced tree is %lf \n \n", timeDifNonAVL);
    printf("----------------------------------------------------------- \n");

    // Collect data and generate plots (not implemented in this example)
    // Free allocated memory
    free(data);
    freeAVLTree(AVLroot);
    freeNonAVLTree(unbalancedRoot);
}




void measurePerformanceSpecialInput(int dataSize) {
    // Generate random data
    int* data = generateOrderedData(dataSize);
    printf("NEW TEST Ordered: %d nodes \n \n", dataSize);
    // Perform operations and measure time for balanced tree (AVL)
    clock_t begin1, end1, begin2, end2;

    // Code for balanced tree operations (insert, delete, delete_min)
    begin1 = clock();
    AVLNode* AVLroot = createAVLNode(data[0]);
    for(int i = 1; i < dataSize; i++)
    {
        insertAVL(AVLroot, data[i]);
    }
    end1 = clock();
    double timeDifAVL = ((double) (end1-begin1))/ CLOCKS_PER_SEC;
    printf("The time complexity for assembling the balanced tree is %lf \n \n", timeDifAVL);
    
    //Call to delete the min node in AVL tree
    begin1 = clock();
    deleteMinAVL(AVLroot);
    end1 = clock();
    timeDifAVL = ((double) (end1-begin1))/ CLOCKS_PER_SEC;
    printf("The time complexity for deleting the MIN-NODE from the balanced tree is %lf \n \n", timeDifAVL);
    
    // Call for deleting a particular node
    begin1 = clock();
    deleteNodeAVL(AVLroot, data[dataSize/2]);
    end1 = clock();
    timeDifAVL = ((double) (end1-begin1))/ CLOCKS_PER_SEC;
    printf("The time complexity for deleting the middle-NODE from the balanced tree is %lf \n \n", timeDifAVL);
    printf("----------------- \n \n");
    
    // Perform operations and measure time for unbalanced tree (Binary Search Tree)
    begin2 = clock();
    Node* unbalancedRoot = createNode(data[0]);
    for(int i = 1; i < dataSize; i++)
    {
        insert(unbalancedRoot, data[i]);
    }
    end2 = clock();
    double timeDifNonAVL = ((double)(end2-begin2))/CLOCKS_PER_SEC;
    printf("The time complexity for assembling the unbalanced tree is %lf \n \n", timeDifNonAVL);

    // Code for unbalanced tree operations (insert, delete, delete_min)
    begin2 = clock();
    deleteMin(unbalancedRoot);
    end2 = clock();
    timeDifNonAVL = ((double)(end2-begin2))/CLOCKS_PER_SEC;
    printf("The time complexity for deleting the MIN-NODE from the unbalanced tree is %lf \n \n", timeDifNonAVL);

    begin2 = clock();
    deleteNode(unbalancedRoot, data[dataSize/2]);
    end2 = clock();
    timeDifNonAVL = ((double)(end2-begin2))/CLOCKS_PER_SEC;
    printf("The time complexity for deleting the middle-NODE from the unbalanced tree is %lf \n \n", timeDifNonAVL);
    printf("----------------------------------------------------------- \n");

    // Free allocated memory
    free(data);
    freeAVLTree(AVLroot);
    freeNonAVLTree(unbalancedRoot);
}


int main() {
  // Seed for random number generation
  srand(time(NULL));

  // Experiment with different problem sizes (average case)
  printf("Random number tests: \n");
  measurePerformanceRandomInput(100000);   // Change this value to experiment with different data sizes
  //measurePerformanceRandomInput(1000000);
  //measurePerformanceRandomInput(10000000);
  //measurePerformanceRandomInput(100000000);
  //measurePerformanceRandomInput(1000000000);


  // Experiment with different problem sizes (worst case)
  printf("Ordered number tests: \n");
  measurePerformanceSpecialInput(100000);   // Change this value to experiment with different data sizes
  //measurePerformanceSpecialInput(1000000);
  //measurePerformanceSpecialInput(10000000);
  //measurePerformanceSpecialInput(100000000);
  //measurePerformanceSpecialInput(1000000000);

  return 0;
}

// Add a function to free the trees
