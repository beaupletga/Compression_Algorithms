#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

// patch to use to_string function
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


int algo1(ifstream &infile)
{
  string compressed_string="";
  string word;
  int i,j,file_size=0;
  while (infile >> word)
  {
    i=0;
    // for the space between words
    file_size++;
    while (i<word.size())
    {
      // for the letter
      file_size++;
      compressed_string+=word[i];
      j=0;
      while(word[i+j]==compressed_string[compressed_string.size()-1])
      {
        j++;
      }
      i+=j;
      compressed_string+=patch::to_string(j);
    }
    compressed_string+=" ";
  }
  cout<<compressed_string<<endl;
  cout<<"Taille du string initial : "<<file_size<<endl;
  cout<<"Taille du string compressé : "<<compressed_string.size()<<endl;
  return 0;
}

int algo2(ifstream &infile)
{
  string compressed_string="";
  string word;
  int i,j,file_size=0;
  while (infile >> word)
  {
    i=0;
    // for the space between words
    file_size++;
    while (i<word.size())
    {
      // for the letter
      file_size++;
      compressed_string+=word[i];
      j=0;
      while(word[i+j]==compressed_string[compressed_string.size()-1])
      {
        j++;
      }
      i+=j;
      if (j!=1)
      {
        compressed_string+=patch::to_string(j);
      }
    }
    compressed_string+=" ";
  }
  cout<<compressed_string<<endl;
  cout<<"Taille du string initial : "<<file_size<<endl;
  cout<<"Taille du string compressé : "<<compressed_string.size()<<endl;
  return 0;
}



int main()
{

  // ifstream infile("sample.txt");
  // algo1(infile);
  ifstream infile("sample.txt");
  algo2(infile);
  return 0;
}
