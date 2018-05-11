/*
TreeType.cpp
Author:  Brian Weber
Submission  Date:  4/9/17
Purpose:  Tree Type imlementation
Statement  of Academic  Honesty:
The  following  code  represents  my  own  work.  I  have  neitherreceived  nor  given  inappropriate assistance. I have not copiedor  modified code from any source other than the course webpageor the course textbook. I recognize that any unauthorizedassistance or plagiarism will be handled in accordance  withthe  University  of  Georgia's  Academic  Honesty  Policy  and  thepolicies  of  this course.  I  recognize  that  my  work  is  basedon  an  assignment  created  by  the  Department  of ComputerScience at the University of Georgia. Any publishingor posting of source code for this project  is strictlyprohibited  unless  you  have written consent  from  the  Departmentof Computer Science  at the  University  of  Georgia.
*/
#include <iostream>
#include <queue>
using namespace std;
#include "TreeType.h"
struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};

bool TreeType::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int CountNodes(TreeNode* tree);

int TreeType::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}


int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found);

ItemType TreeType::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}


void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 

void Insert(TreeNode*& tree, ItemType item);

void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}


void Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
} 
void DeleteNode(TreeNode*& tree);

void Delete(TreeNode*& tree, ItemType item);

void TreeType::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << "is not in tree\n";
}


void Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

void GetPredecessor(TreeNode* tree, ItemType& data);

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data);  // Delete predecessor node.
  }
}

void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}

void PrintTree(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
    PrintTree(tree->left);   // Print left subtree.
    cout << tree->info << " ";
    PrintTree(tree->right);  // Print right subtree.
  }
}

void TreeType::Print() const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(root);
}

TreeType::TreeType()
{
  root = NULL;
}

void Destroy(TreeNode*& tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}


void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

void TreeType::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}


void CopyTree(TreeNode*& copy, 
     const TreeNode* originalTree);

TreeType::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

void TreeType::operator= 
     (const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  }

}
void CopyTree(TreeNode*& copy, 
     const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}
// Function prototypes for auxiliary functions.

void PreOrder(TreeNode*, QueType&);
// Enqueues tree items in preorder.


void InOrder(TreeNode*, QueType&);
// Enqueues tree items in inorder.


void PostOrder(TreeNode*, QueType&);
// Enqueues tree items in postorder.


void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
  switch (order)
  { 
  case PRE_ORDER:    preQue.MakeEmpty();
		             PreOrder(root, preQue);
                     break;
  case IN_ORDER:     inQue.MakeEmpty();
					 InOrder(root, inQue);
                     break;
  case POST_ORDER:  postQue.MakeEmpty();
					PostOrder(root, postQue);
                     break;
  }
}


void PreOrder(TreeNode* tree, 
     QueType& preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL)
  {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}


void InOrder(TreeNode* tree, 
     QueType& inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL)
  {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}


void PostOrder(TreeNode* tree, 
     QueType& postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}


ItemType TreeType::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER  : preQue.Dequeue(item);
                      if (preQue.IsEmpty())
                        finished = true;
                      break;
    case IN_ORDER   : inQue.Dequeue(item);
                      if (inQue.IsEmpty())
                        finished = true;
                      break;
    case  POST_ORDER: postQue.Dequeue(item);
                      if (postQue.IsEmpty())
                        finished = true;
                      break;
  }
  return item;
}

void TreeType::LevelOrderPrint(){
  if (root == NULL)  return;
  queue<TreeNode*> q;
  q.push(root);
  int loop = 0;
  while (1)
    {
      int nodeCount = q.size();
      if (nodeCount == 0) break;
      if ((loop == 1) && (nodeCount == 2)) {
        cout << "            /    \\" << endl;
      } else if ((loop == 1) && (nodeCount == 1)) {
	cout << "            /" << endl;      
      } else if ((loop == 2) && (nodeCount == 4)) {
        cout << "        /  \\      /  \\" << endl;
      } else if ((loop == 2) && (nodeCount == 3)) {
	cout << "        /  \\      /" << endl;
      } else if ((loop == 2) && (nodeCount == 2)) {
	cout << "        /  \\" << endl;
      } else if ((loop == 2) && (nodeCount == 1)) {
	cout << "        /" << endl;
      } else if ((loop == 3) && (nodeCount == 8)) {
        cout << "    /  \\  /  \\  /  \\  /  \\" << endl;
      } else if ((loop == 3) && (nodeCount == 7)) {
	cout << "    /  \\  /  \\  /  \\  /" << endl;
      } else if ((loop == 3) && (nodeCount == 6)) {
	cout << "    /  \\  /  \\  /  \\" << endl;
      } else if ((loop == 3) && (nodeCount == 5)) {
        cout << "    /  \\  /  \\  /" << endl;
      } else if ((loop == 3) && (nodeCount == 4)) {
	cout << "    /  \\  /  \\" << endl;
      } else if ((loop == 3) && (nodeCount == 3)) {
        cout << "    /  \\  /" << endl;
      } else if ((loop == 3) && (nodeCount == 2)) {
	cout << "    /  \\" << endl;
      } else if ((loop == 3) && (nodeCount == 1)) {
        cout << "    /" << endl;
      } else if ((loop == 4) && (nodeCount == 4)) {
	cout << "  / \\ / \\" << endl;
      } else if ((loop == 4) && (nodeCount == 3)) {
	cout << "  / \\ /" << endl;
      } else if ((loop == 4) && (nodeCount == 2)) {
        cout << "  / \\" << endl;
      } else if ((loop == 4) && (nodeCount == 1)) {
        cout << "  /" << endl;
      } else if ((loop == 5) && (nodeCount == 4)) {
        cout << " / \\ / \\" << endl;
      } else if ((loop == 5) && (nodeCount == 3)) {
        cout << " / \\ /" << endl;
      } else if ((loop == 5) && (nodeCount == 2)) {
        cout << " / \\" << endl;
      } else if ((loop == 5) && (nodeCount == 1)) {
        cout << " /" << endl;
      }
      while (nodeCount > 0)
        {
	  TreeNode *node = q.front();
	  if (loop == 0) {
	    cout << "              " << node -> info;
	  } else if (loop == 1) {
	    cout << "        " << node -> info;           
	  } else if (loop == 2) {
	    cout << "    " << node -> info;
	  } else if (loop == 3) {
	    cout << "  " << node -> info;
	  } else {
	    cout << " " << node -> info;
          }
	  q.pop();
	  if (node->left != NULL)
	    q.push(node->left);
	  if (node->right != NULL)
	    q.push(node->right);
	  nodeCount--;
        }
      cout << endl;
      loop++;
    }
} // Level Order Print

void TreeType::PreOrderPrint(){
  ItemType item;
  bool done = false;
  PreOrder(root, preQue);
  while (done == false){
    item = GetNextItem(PRE_ORDER , done);
    cout << item << " ";
  }
} // Pre Order Print

void TreeType::InOrderPrint(){
  ItemType item;
  bool done = false;
  InOrder(root, inQue);
  while (done == false){
    item = GetNextItem(IN_ORDER , done);
    cout << item << " ";
  } 
} // In Order Print

void TreeType::PostOrderPrint(){
  ItemType item;
  bool done = false;
  PostOrder(root, postQue);
  while (done == false){
    item = GetNextItem(POST_ORDER , done);
    cout << item << " ";
  }
} // Post Order Print

struct TreeNode* TreeType::MakeTree(int list[]){
  return (ArrayToTree(list, 0, 10));
} // MakeTree

struct TreeNode* TreeType::ArrayToTree(int list[], int start, int end){
  if (start > end) return NULL;
  int mid = (start + end)/2;
  root->info = list[mid];
  //struct TreeNode* root = new TreeNode(list[mid]);
  root->left = ArrayToTree(list, start, mid-1);
  root->right = ArrayToTree(list, mid+1, end);
  return root;
} // Array To Tree

struct TreeNode* TreeType::MirrorImage(){
  // Calls  recursive  function  Mirror.
  // Post:  A tree that  is  the  mirror  image  the tree is  returned.
  Mirror(root);
  return root;
} // Mirror Image

struct TreeNode* TreeType::Mirror(struct TreeNode* root){
  if (root != NULL) {
    struct TreeNode* temp;
    Mirror(root -> left);
    Mirror(root -> right);
    temp = root -> left;
    root -> left = root -> right;
    root -> right = temp;
  }
  return root;
} // Mirror

void TreeType::Ancestors(ItemType value){
  //Precondition:  Tree is  initialized
  //Postcondition:  The  ancestors  of the  node whose  info member  is  valuehave  been printed.
  PrintAncestors(root, value);
} // Ancestors

void TreeType::PrintAncestors(TreeNode* tree, ItemType value) {
  if (tree->info != value) {
    cout << tree->info << " ";
    if (tree->info < value) {
      PrintAncestors(tree -> right, value);
    } else {
      PrintAncestors(tree -> left, value);
    }
  }
} // Print Ancestors 
