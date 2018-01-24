
using namespace std;


class Node
{
public:
  Node(char letter,float probability);

  float get_probability();
  char get_letter();
  string get_path();
  void set_path();

  void add_son(Node* son,int right_or_left);
  void update_value();
  Node* get_son(int right_or_left);
  string get_path(char letter);
  char search(string sample);
private:
  Node* right_son;
  Node* left_son;
  char letter;
  float probability;
  string path;
};
