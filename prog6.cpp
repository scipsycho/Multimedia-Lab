#include <iostream>
#include <string>
#include <map>
int main(){
  std::cout<<"Enter the string to be transmitted: ";
  std::string input;
  std::cin>>input;
  std::map<std::string,int>dictionary;

  int count=256,i,j;
  i=0;
  while(i<input.size()){

    //let's check if a substring is already in the dictionary
    for(j=i+1;j<input.size();j++)
      if(dictionary.find(input.substr(i,j-i+1))==dictionary.end())
        break;

    //output the ascii value
    if(j==i+1)
      std::cout<<int(input[i])<<std::endl;
    //or the dictionary index in  case of a substring
    else
      std::cout<<(dictionary.find(input.substr(i,j-i))->second)<<std::endl;

    //updating dictionary
    dictionary[input.substr(i,j-i+1)]=count++;
    i=j;
  }
}
