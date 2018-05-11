/*
TreeDr.cpp
Author:  Brian Weber
Submission  Date:  4/9/17
Purpose:  Test Drive
Statement  of Academic  Honesty:
The  following  code  represents  my  own  work.  I  have  neitherreceived  nor  given  inappropriate assistance. I have not copiedor  modified code from any source other than the course webpageor the course textbook. I recognize that any unauthorizedassistance or plagiarism will be handled in accordance  withthe  University  of  Georgia's  Academic  Honesty  Policy  and  thepolicies  of  this course.  I  recognize  that  my  work  is  basedon  an  assignment  created  by  the  Department  of ComputerScience at the University of Georgia. Any publishingor posting of source code for this project  is strictlyprohibited  unless  you  have written consent  from  the  Departmentof Computer Science  at the  University  of  Georgia.
*/

// Test driver
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "TreeType.h"

using namespace std;

int main()
{

  ifstream inFile;       // file containing operations
  ofstream outFile;      // file containing output
  string inFileName;     // input file external name
  string outFileName;    // output file external name
  string outputLabel;     
  string command;        // operation to be executed
  
  char item;
  string orderItem;
  TreeType tree;
  OrderType order;
  bool found;
  bool finished;
  int numCommands;
  
  cout << "This project was implemented by:" << endl;
  cout << "Brian Weber, #811973356, CRN: 26490" << endl;
  // Prompt for file names, read file names, and prepare files
  cout << "Enter name of input command file; press return." << endl;
  cin  >> inFileName;
  inFile.open(inFileName.c_str());

  cout << "Enter name of output file; press return." << endl;
  cin  >> outFileName;
  outFile.open(outFileName.c_str());

  cout << "Enter name of test run; press return." << endl;
  cin  >> outputLabel;
  outFile << outputLabel << endl;

  inFile >> command;

  numCommands = 0;
  while (command != "Quit")
    { 
      cout << command;
      if (command == "PutItem")
	{
	  inFile >> item; 
	  tree.PutItem(item);
	  outFile << item;
	  outFile << " is inserted" << endl;
	}
      else if (command == "DeleteItem")
	{
	  inFile >> item;
	  tree.DeleteItem(item);
	  outFile << item;
	  outFile << " is deleted" << endl;
	}
      else if (command == "GetItem")
	{
	  inFile >> item;

	  item = tree.GetItem(item, found);
	  if (found)
	    outFile << item << " found in list." << endl;
	  else outFile << item  << " not in list."  << endl;  
	} 
      else if (command == "GetLength")  
	outFile << "Number of nodes is " << tree.GetLength() << endl;
      else if (command == "IsEmpty")
	if (tree.IsEmpty())
	  outFile << "Tree is empty." << endl;
	else outFile << "Tree is not empty."  << endl;  
  
      else if (command == "PrintTree")
	{
	  cout << endl << " ";
	  tree.Print();
	  cout << endl;
	}  
      else if (command == "ResetTree")
	{
	  inFile >> orderItem;
	  if (orderItem == "PRE_ORDER")
	    order = PRE_ORDER;
	  else if (orderItem == "IN_ORDER")
	    order = IN_ORDER;
	  else order = POST_ORDER;    
         
	  tree.ResetTree(order);
	}
      else if (command == "GetNextItem")
	{
	  inFile >> orderItem;
	  if (orderItem == "PRE_ORDER")
	    order = PRE_ORDER;
	  else if (orderItem == "IN_ORDER")
	    order = IN_ORDER;
	  else order = POST_ORDER;    
	  item = tree.GetNextItem(order,finished);
	  outFile << "Next item is: " << item << endl;
	  if (finished)
	    outFile << orderItem << " traversal is complete." << endl;
	}     
      else if (command == "IsFull")
	if (tree.IsFull())
	  outFile << "Tree is full."  << endl;
	else outFile << "Tree is not full." << endl;  
      else if (command == "MakeEmpty")
	{
	  tree.MakeEmpty();
	  outFile << "Tree has been made empty." << endl;
	}
      else if (command == "LevelOrderPrint")
	{
	  cout << endl;
	  tree.LevelOrderPrint();
	}
      else if (command == "PostOrderPrint")
	{
	  cout << endl << " ";
	  tree.PostOrderPrint();
          cout << endl;
	}
      else if (command == "PreOrderPrint")
	{
	  cout << endl << " ";
	  tree.PreOrderPrint();
	  cout << endl;
	}
      else if (command == "InOrderPrint")
	{
	  cout << endl << " ";
	  tree.InOrderPrint();
	  cout << endl;
	}
      else if (command == "Error")
	{
	  // Error
	}
      else if (command == "MakeTree")
	{
	  tree.MakeEmpty();
     	  int num[10];
	  for (int i = 0; i < 10; i++) {
	    inFile >> num[i];
	    outFile << num[i] << " is inserted in array" << endl;
	  }
	  tree.PutItem(num[5]);
	  for (int j = 4; j > 0; j--) {
	    tree.PutItem(num[j]);
	  }
	  for (int k = 6; k < 10; k++) {
	    tree.PutItem(num[k]);
	  }
	  tree.PutItem(num[0]);
	  //tree.MakeTree(num);
	}
      else if (command == "MirrorImage")
	{
	  tree.MirrorImage();
	}
      else if (command == "Ancestors")
	{
	  ItemType value;
          inFile >> value;
	  cout << endl << " ";
	  tree.Ancestors(value);
	  cout << endl;
	}
      else cout << " Command not recognized." << endl;
      numCommands++;
      cout <<  " Command is completed."  << endl;
      inFile >> command;
    }
 
  cout << "Testing completed."  << endl;
  inFile.close();
  outFile.close();
  return 0;
}




