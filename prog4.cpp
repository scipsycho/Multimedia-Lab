#include<iostream>
#include<queue>
#include<string>
#include<stack>

using namespace std;

struct node{

	char ch;
	int data;

	struct node* left;
	struct node* right;
	node(int dat,char c):data(dat),left(nullptr),right(nullptr),ch(c){}

};

// to find the location of a character in tree
pair<struct node*,string> searchNode(struct node* root,struct node* find,string str=""){

	// base case : character not found
	if(root == nullptr)
		return make_pair(nullptr,"");

	// character has been found
	if(root == find)
		return make_pair(root,str);

	pair<struct node*, string> temp = searchNode(root->left,find,str+"0");

	// character in left subtree
	if(temp.first !=nullptr)
		return temp;

	// character in right subtree
	return searchNode(root->right,find,str+"1");
}

// to find the location of a character in tree
pair<struct node*,string> search(struct node* root,char inp,string str=""){

	// base case : character not found
	if(root == nullptr)
		return make_pair(nullptr,"");

	// character has been found
	if(root->ch == inp)
		return make_pair(root,str);

	pair<struct node*, string> temp = search(root->left,inp,str+"0");

	// character in left subtree
	if(temp.first !=nullptr)
		return temp;

	// character in right subtree
	return search(root->right,inp,str+"1");
}

// print the ascii value of char
void print(char ch,int i=7){

	// base case
	if(i<0)
		return;

	// recursive call
	print(ch/2,i-1);
	// to ensure print is done in correct order
	cout<<ch%2;
}

// recursive calls to modify tree frequency values due to additions
void correct_tree(string str,struct node* root){

	// base case
	if(root==nullptr)
		return;

	// increment the frequency from root to new character
	root->data++;
	for(int i=0;i<str.size();i++){
		if(str[i]=='0')
			root=root->left;
		else
			root=root->right;
		root->data++;
	}
}

// level order traversal + finding locations for tree violations
pair<struct node*,struct node*> display_lo(struct node* root,bool flag = false){
	// base case
	if(root == nullptr)
		return make_pair(nullptr,nullptr);

	pair<struct node*,struct node*> found;
	struct node* temp;
	queue<struct node*> stk;
	stk.push(root);
	stk.push(nullptr);

	stack<struct node*> order;

	// normal level order traversal
	while(true){

		temp = stk.front();
		stk.pop();

		if(temp == nullptr)
			if(stk.empty())
				break;

		if(flag)
			order.push(temp);
		else cout<<temp->ch<<"("<<temp->data<<")";

		if(temp->right != nullptr)
			stk.push(temp->right);

		if(temp->left != nullptr)
			stk.push(temp->left);
	}

	found.first = nullptr;
	found.second = nullptr;

	if(!flag)
		return found;

	// finding violations in the tree
	struct node* previous = order.top();
	order.pop();
	struct node* current;

	while(!order.empty()){
		current = order.top();
		order.pop();

		if(current->data >= previous->data){
			previous = current;
			continue;
		}
		// violation found
		found.first = previous;
		//cout<<"in here "<<previous->ch<<previous->data<<endl;
		break;
	}
	// no violation
	if(found.first == nullptr)
		return found;
	// find the farthest node satisfying the property
	while(!order.empty()){
		if(current->data == found.first->data-1){
			found.second = current;
			//cout<<"in here "<<current->ch<<current->data<<endl;
		}

		current = order.top();
		order.pop();
	}
	// return both the positions
	return found;
}

int recursive(struct node* root){

	// base case
	if(root->left == nullptr && root->right == nullptr)
		return root->data;

	root->data = recursive(root->left) + recursive(root->right);
	return root->data;
}

// remove the tree violations
void exchange(struct node* &root,pair<struct node*,struct node*> violations){
	// find the parents of the violations
	pair<struct node*,string> left = searchNode(root,violations.first);
	pair<struct node*,string> right = searchNode(root,violations.second);

	struct node* leftparent = root;
	auto i = left.second.begin();
	for(;i != left.second.end()-1;i++){
		if(*i == 0)
			leftparent = leftparent->left;
		else leftparent = leftparent->right;
	}

	struct node* rightparent = root;
	auto j = right.second.begin();
	for(;j != right.second.end()-1;j++){
		if(*j == 0)
			rightparent = rightparent->left;
		else rightparent = rightparent->right;
	}

	// remove the violations
	if(*i == '0')
		leftparent->left = violations.second;
	else leftparent->right = violations.second;

	if(*j == '0')
		rightparent->left = violations.first;
	else rightparent->right = violations.first;

	// restructure the tree for correct frequencies
	recursive(root);
}

void dynamicHuffman(string str){

	// initialization
	node* root = new struct node(1,'|');
	root->left = new struct node(0,'!');

	bool check;
	struct node* cur = root;
	pair<struct node*,string> temp;
	pair<struct node*,struct node*> violations;

	cout<<"The encoded output is as follows : "<<endl;

	// add the first character
	auto i = str.begin();
	root->right = new struct node(1,*i);
	cout<<"1";
	cout<<*i;
	print(*i);
	cout<<endl;
	i++;

	// for the remaining characters in the string
	for(;i != str.end(); i++){
		check = false;
		// character present in tree or not
		temp = search(root,*i);

		if(temp.first == nullptr){
					check = true;
					// search zero node
					temp = search(root,'!');

					// initialize number node
					temp.first->data=0;
					temp.first->ch='@';

					temp.first->left = new struct node(0,'!');
					temp.first->right = new struct node(0,*i);

					// location of new character node
					temp.second = temp.second+"1";
					temp.first = temp.first->right;

			}
	// restructure the tree
	correct_tree(temp.second,root);

	// find the violations
	violations = display_lo(root,true);

	// no violation
	if(violations.first == nullptr){
		cout<<temp.second;
		if(check){
			cout<<*i;
			print(*i);
		}
		else cout<<*i;
		cout<<endl;
		continue;
	}

	// remove the violations
	exchange(root,violations);

	temp = search(root,*i);
	cout<<temp.second;
	if(check){
		cout<<*i;
		print(*i);
	}
	else cout<<*i;
	cout<<endl;
	}

	cout<<endl;
	display_lo(root);
	cout<<endl;
}

int main(){

	string str;
	cin>> str;

	dynamicHuffman(str);

	return 0;
}
