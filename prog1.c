#include<stdio.h>
void main(){
	FILE *f1;
	f1=fopen("prog1_text.txt","w");
	printf("Enter the data you want to write in the file (Press . to end): ");
	char ch;
	ch=getchar();
	while(ch!='.'){
		putc(ch,f1);
		ch=getchar();
	}
	fclose(f1);
	printf("Writing....\nCLosing File....\n");
}
