#include <iostream>

using namespace std;

class Node
{
public:
  Node(int value);
  void search_node();
  void add_node(Node* root,int value);
  void delete_node(int value);
private:
  Node* right_son;
  Node* left_son;
  int value;
};


Node::Node(int value)
{
  this->right_son=NULL;
  this->left_son=NULL;
  this->value=value;
}



void Node::add_node(Node* root,int value)
{
  Node node_to_add(value);
  Node* current=root;
  Node* previous;
  while(current)
  {
    previous=current;
    if(current->value>value)
    {
      current=current->left_son;
    }
    else
    {
      current=current->right_son;
    }
  }
  if(previous->value>value)
  {
    previous->left_son=&node_to_add;
    return;
  }
  else
  {
    previous->right_son=&node_to_add;
    return;
  }
}


int main()
{
  Node root(5);
  root.add_node(&root,10);
  


  return 0;
}
