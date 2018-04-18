#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <random>
#define SIZE 9
#define UNASSIGNED 0

bool SolveSudoku(std::vector<std::vector<int> >&);
bool FindUnAssignedPos(std::vector<std::vector<int> > &,int&,int&);
bool isSafe(std::vector<std::vector<int> >&,int,int,int);
void createGrid(std::vector<std::vector<int> >&);
void display(std::vector<std::vector<int> >&);
bool isSolvable(std::vector<std::vector<int> >);
int menu(){
  int choice;
  std::cout<<std::endl;
  std::cout<<"1. Enter Values"<<std::endl;
  std::cout<<"2. Reset"<<std::endl;
  std::cout<<"3. Submit"<<std::endl;
  std::cout<<"*. Exit"<<std::endl;
  std::cout<<"Choose: ";
  std::cin>>choice;
  return choice;
}
int main(){

    std::vector< std::vector<int> >grid(SIZE,std::vector<int>(SIZE,UNASSIGNED)),intial_state;
    createGrid(grid);
    display(grid);
    intial_state=grid;
    int key,row,col,val;
    key=menu();
    while(true){
      if(key==1){
        std::cout<<"Enter row, column and values (1-indexed): ";
        std::cin>>row>>col>>val;
        if(val>=1 && val <=9 && isSafe(grid,row-1,col-1,val))
          grid[row-1][col-1]=val;
      }
      else if(key==2)
        grid=intial_state;
      else if(key==3){
          key=1;
          for(row=0;row<SIZE;row++){
            for(col=0;col<SIZE;col++)
              if(grid[row][col]==UNASSIGNED){
                key=0;
                std::cout<<"Not so easy boy, Get back to it!!!"<<std::endl;
                break;
              }
            if(!key)
              break;
          }

          if(key){
            std::cout<<"Congratulations!!! You have completed the hardest game in the world!!"<<std::endl;
            exit(0);
          }

      }
      else{
        std::cout<<"Exiting...."<<std::endl;
        exit(0);
      }

      display(grid);
      key=menu();
    }


}

void createGrid(std::vector<std::vector<int> > &grid){

  SolveSudoku(grid);
  std::vector<int> array,temp;
  for(int i=0;i< (SIZE*SIZE);i++)
        temp.push_back(i);

  int n,t;
  n=temp.size();

  srand(time(NULL));
  for(int i=0;i<n;i++){
      t=rand()%temp.size();
      array.push_back(temp[t]);
      temp.erase(temp.begin()+t);
  }


  int i=0;
  while(i<n){
      t=grid[array[i]/SIZE][array[i]%SIZE];
      grid[array[i]/SIZE][array[i]%SIZE]=UNASSIGNED;
      if(!isSolvable(grid))
        grid[array[i]/SIZE][array[i]%SIZE]=t;
      i++;
  }
}

bool isSolvable(std::vector<std::vector<int> > grid){

  int count;
  int val;
  bool changed=false;
  int count_un=0;
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){

      if(grid[i][j]!=UNASSIGNED){
        count_un++;
        continue;
      }

      count=0;
      val=-1;

      for(int num=1;num<=SIZE;num++)
        if(isSafe(grid,i,j,num)){

          count++;
          if(count>1)
            break;

          val=num;
        }
      if(count==1){
        grid[i][j]=val;
        changed=true;
      }
    }
  }

  if(count_un==SIZE*SIZE)
    return true;
  if(!changed)
    return false;

  return isSolvable(grid);
}


bool SolveSudoku(std::vector<std::vector<int> > &grid){

  int row, col,t;
  if(!FindUnAssignedPos(grid,row,col))
    return true;

  std::vector<int> array,temp;
  for(int i=1;i<=SIZE;i++)
    temp.push_back(i);


  srand(time(NULL));
  for(int i=0;i<SIZE;i++){
    t=rand()%temp.size();
    array.push_back(temp[t]);
    temp.erase(temp.begin()+t);
  }

  for(int i=0;i<SIZE;i++){

    if(isSafe(grid,row,col,array[i])){

      grid[row][col]=array[i];

      if(SolveSudoku(grid))
        return true;

      grid[row][col]=UNASSIGNED;
    }
  }

  return false;

}

bool FindUnAssignedPos(std::vector<std::vector<int> > &grid,int &row, int &col){

  for(row=0;row<SIZE;row++)
    for(col=0;col<SIZE;col++)
      if(grid[row][col]==UNASSIGNED)
        return true;

  return false;
}

bool isSafe(std::vector<std::vector<int> > &grid,int row,int col,int val){

  if(grid[row][col]!=UNASSIGNED)
    return false;

  for(int i=0;i<SIZE;i++)
    if(grid[row][i]==val || grid[i][col]==val)
      return false;

  int box=sqrt(SIZE);
  for(int i=0;i<box;i++)
    for(int j=0;j<box;j++)
      if(grid[i + (row/box)*box][j+ (col/box)*box]==val)
        return false;


  return true;
}

void display(std::vector<std::vector<int> > &grid){

  std::cout<<std::endl;

  int box=sqrt(SIZE);
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      if(grid[i][j]==UNASSIGNED)
        std::cout<<"_ ";
      else
        std::cout<<grid[i][j]<<" ";
      if((j+1)%box==0)
        std::cout<<" ";
    }
    std::cout<<std::endl;
    if((i+1)%box==0)
      std::cout<<std::endl;
  }
}
