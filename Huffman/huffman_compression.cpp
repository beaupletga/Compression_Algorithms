#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Node.h"
using namespace std;


// To compile and execute the following code all you need is to paste this line into your terminal :
// g++ -o huffman huffman_compression.cpp Node.cpp && ./huffman


// http://cermics.enpc.fr/polys/oap/node49.html


// sort decreasing way
bool sort_pair(pair<char,float> i,pair<char,float> j)
{
  if(i.second<j.second){
    return true;
  }
  return false;
}

bool sort_node(Node* i,Node* j)
{
  if(i->get_probability()<j->get_probability()){
    return true;
  }
  return false;
}

bool is_in(vector<pair<char,float> > list,char letter)
{
  for (int i=0;i<list.size();i++)
  {
    if (list[i].first==letter)
    {
      return true;
    }
  }
  return false;
}

float get_probability(string string_to_code,char letter)
{
  float count=0;
  for (int i=0;i<string_to_code.size();i++)
  {
    if(string_to_code[i]==letter)
    {
      count++;
    }
  }
  return count/string_to_code.size();
}

vector<pair<char,float> > set_probabilities(string string_to_code)
{
  vector<pair<char,float> > list;
  for (int i=0;i<string_to_code.size();i++)
  {
    if (!is_in(list,string_to_code[i]))
    {
      float probability=get_probability(string_to_code,string_to_code[i]);
      pair<char,float> tmp(string_to_code[i],probability);
      list.push_back(tmp);
    }
  }
  return list;
}

void print_letter_and_proba(vector<pair<char,float> > list)
{
  for(int i=0;i<list.size();++i)
  {
    cout<<list[i].first<< "  "<<list[i].second<<endl;
  }
}

void print_letter_and_code(vector<pair<char,float> > list,Node* root)
{
  cout<<endl;
  for (int i=0;i<list.size();++i)
  {
    cout<<list[i].first<<"  "<<root->get_path(list[i].first)<<endl;
  }
}

string print_code_text(string text,Node* root)
{
  string coded_text="";
  for(int i=0;i<text.size();++i)
  {
    coded_text+=root->get_path(text[i]);
  }
  return coded_text;
}

string decode(string encoded_text,Node* root)
{
  string clear_text="";
  int j;
  for(int i=0;i<encoded_text.size();i++)
  {
    j=0;
    while(j<encoded_text.size())
    {
      char letter=root->search(encoded_text.substr(i,j));
      if(letter)
      {
        clear_text+=letter;
        i+=j-1;
        break;
      }
      else
      {
        j++;
      }
    }
  }
  return clear_text;
}



int main()
{
  string string_to_code="Bonjour je m'appelle Serge Beauplet";


  cout<<"Clear text : "<<string_to_code<<endl;

  vector<pair<char,float> > list=set_probabilities(string_to_code);
  std::sort(list.begin(), list.end(), sort_pair);

  print_letter_and_proba(list);

  vector<Node*> node_list;

  for(int i=0;i<list.size();++i)
  {
    Node* tmp=new Node(list[i].first,list[i].second);
    node_list.push_back(tmp);
  }

  while (node_list.size()>1)
  {
    Node* forest_root= new Node(NULL,0);
    forest_root->add_son(node_list[0],0);
    forest_root->add_son(node_list[1],1);
    forest_root->update_value();

    node_list.erase(node_list.begin());
    node_list.erase(node_list.begin());
    node_list.push_back(forest_root);
    std::sort(node_list.begin(), node_list.end(), sort_node);
  }

  Node* root=node_list[0];
  root->set_path();

  print_letter_and_code(list,root);

  string coded_text=print_code_text(string_to_code,root);

  cout<<"Encoded text : "<<coded_text<<endl;

  string clear_text=decode(coded_text,root);

  cout<<clear_text<<endl;

  return 0;
}
