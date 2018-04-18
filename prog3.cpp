#include <iostream>
#include <functional> #include <string>
#include <map>
#include <queue>
using namespace std;
struct node{
  char sym;
  bool isleaf;
  int freq;
  node *left, *right;
};

node* newNode(char ch, int f=0){
    node* ele=new node;
    ele->sym=ch;
    ele->isleaf=true;
    ele->freq=f;
    ele->left=ele->right=nullptr;
    return ele;
}

string print(node* root,char a, string s=""){

  if(root->isleaf && root->sym==a)
    return s;
  else if(root->isleaf)
    return "";

  string t=print(root->left,a,s+"0") + print(root->right,a,s+"1");

  return t;
}
int main(){
  string input,output;
  cin>>input;
  map<char,node*> count;
  for(int i=0;i<input.length();i++){
    if(count.find(input[i])==count.end()){
      count[input[i]]=newNode(input[i]);
    }
    (count[input[i]]->freq)+=1;
  }

  auto cmp=[](node* left,node* right) { return ((left->freq) > (right->freq)); };
  priority_queue<node*,vector<node*>,decltype(cmp)> q(cmp);

  map<char,node*>::iterator i;
  i=count.begin();
  for(;i!=count.end();i++){
    q.push(i->second);
  }

  node *left, *right,*head;
  while(!q.empty()){
    if(q.size()==1){
      head=q.top();
      q.pop();
      break;
    }
    left=q.top();
    q.pop();
    right=q.top();
    q.pop();
    head=newNode('\0',(left->freq) + (right->freq));
    head->left=left;
    head->right=right;
    head->isleaf=false;
    q.push(head);
  }

  cout<<"Enter the string to encode using the above string as average: ";
  cin>>output;

  for(int j=0;j<output.length();j++)
    cout<<print(head,output[j])<<" ";
  cout<<endl;
}
