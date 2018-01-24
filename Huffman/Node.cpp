#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include "Node.h"

using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}



Node::Node(char letter,float probability)
{
  this->right_son=NULL;
  this->left_son=NULL;
  this->letter=letter;
  this->probability=probability;
  this->path="";
}

char Node::get_letter()
{
  return this->letter;
}

string Node::get_path()
{
  return this->path;
}

Node* Node::get_son(int right_or_left)
{
  if (right_or_left==0)
  {
    return this->left_son;
  }
  return this->right_son;
}

// 0 for left, 1 for right
void Node::add_son(Node* son,int right_or_left)
{
  if (right_or_left==0)
  {
    this->left_son=son;
    return;
  }
  this->right_son=son;
  return;
}

void Node::update_value()
{
  this->probability=this->right_son->probability+this->left_son->probability;
}

float Node::get_probability()
{
  return this->probability;
}

char Node::search(string sample)
{
  Node* cursor=this;
  for(int i=0;i<sample.size();++i)
  {
    if (cursor==NULL)
    {
      return NULL;
    }
    else if(sample[i]=='0')
    {
      cursor=cursor->left_son;
    }
    else
    {
      cursor=cursor->right_son;
    }
  }
  if (cursor->letter)
  {
    return cursor->letter;

  }
  return NULL;
}


void Node::set_path()
{
  queue<Node*> node_queue;
  node_queue.push(this);
  while (node_queue.size()>=1)
  {
    if(node_queue.front()->left_son)
    {
      node_queue.front()->left_son->path=node_queue.front()->path+"0";
      node_queue.front()->right_son->path=node_queue.front()->path+"1";
      node_queue.push(node_queue.front()->left_son);
      node_queue.push(node_queue.front()->right_son);
    }
    node_queue.pop();
  }
}

string Node::get_path(char letter)
{
  queue<Node*> node_queue;
  node_queue.push(this);
  while (node_queue.size()>=1)
  {
    if (node_queue.front()->letter==letter)
    {
      return node_queue.front()->path;
    }
    else if(node_queue.front()->left_son)
    {
      node_queue.push(node_queue.front()->left_son);
      node_queue.push(node_queue.front()->right_son);
    }
    node_queue.pop();
  }
}
