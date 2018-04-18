#include <iostream>
#include <ctime>
#include <random>

int main(){

    srand(time(NULL));
  for(int i=0;i<10;i++){
    std::cout<<rand()%10<<std::endl;
  }
}
