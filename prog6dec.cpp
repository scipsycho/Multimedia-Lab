#include <iostream>
#include <string>
#include <vector>
#include <map>

int main(){
  int len;
  std::cout<<"Enter the number of codes: "<<std::endl;
  std::cin>>len;
  std::cout<<"Enter the array of codes (The Transmitted Message): "<<std::endl;
  std::vector<int> array(len);

  for(int i=0;i<len;i++)
    std::cin>>array[i];

  std::map<int,std::string>dictionary;
  for(int i=0;i<256;i++)
    dictionary[i]=char(i);


  std::string output="",temp;
  int prev,curr,count;
  count=256;


  prev=array[0];
  output+=char(prev);

  for(int i=1;i<len;i++){
    curr=array[i];
    temp=dictionary[curr];
    if(temp.size()>1)
      temp=temp.substr(0,1);
    dictionary[count++]=dictionary[prev]+temp;
    prev=curr;
    output+=dictionary[prev];
  }

  std::cout<<"The Message is : "<<output<<std::endl;

  std::map<int,std::string>::iterator i;
  for(i=dictionary.begin();i!=dictionary.end();i++)
    std::cout<<i->first<<": "<<i->second<<std::endl;
}
