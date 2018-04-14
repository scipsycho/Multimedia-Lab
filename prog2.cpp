#include<iostream>
#include<string>
using namespace std;

int main(){
	string str;
	cout<<"Enter the string you want to compress: ";
	cin>>str;
	int count=1;
	char prev=str[0];
	for(int i=1;i<str.size();i++){
		if(str[i]==prev)
			count++;
		else{
			cout<<prev<<count;
			count=1;
			prev=str[i];
		}
	}
	cout<<endl;
}
