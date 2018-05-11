/*
TreeType.h
Author:  Brian Weber
Submission  Date:  4/9/17
Purpose:  Tree Type header
Statement  of Academic  Honesty:
The  following  code  represents  my  own  work.  I  have  neitherreceived  nor  given  inappropriate assistance. I have not copiedor  modified code from any source other than the course webpageor the course textbook. I recognize that any unauthorizedassistance or plagiarism will be handled in accordance  withthe  University  of  Georgia's  Academic  Honesty  Policy  and  thepolicies  of  this course.  I  recognize  that  my  work  is  basedon  an  assignment  created  by  the  Department  of ComputerScience at the University of Georgia. Any publishingor posting of source code for this project  is strictlyprohibited  unless  you  have written consent  from  the  Departmentof Computer Science  at the  University  of  Georgia.
*/
#include <queue>
#include <string>
#include <fstream>
typedef int ItemType;
struct TreeNode;
#include "QueType.h"
enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
//template<class ItemType>
class TreeType
{
 public:
  TreeType();                     // constructor
  ~TreeType();                    // destructor
  TreeType(const TreeType& originalTree); 
  void operator=(const TreeType& originalTree);
  // copy constructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  ItemType GetNextItem(OrderType order, bool& finished);
  void Print() const;
  void LevelOrderPrint();
  void PreOrderPrint();
  void InOrderPrint();
  void PostOrderPrint();
  void Ancestors(ItemType value);
  void PrintAncestors(TreeNode* tree, ItemType value);
  struct TreeNode* MirrorImage();
  struct TreeNode* Mirror(struct TreeNode* root);
  struct TreeNode* MakeTree(int list[]);
  struct TreeNode* ArrayToTree(int list[], int start, int end);
 private:
  TreeNode* PtrToSuccesor(TreeNode*& tree);
  TreeNode* root;
  QueType preQue;
  QueType inQue;
  QueType postQue;
};

