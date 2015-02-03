
#include <stdio.h>
#include <stdlib.h>

char** poles;
char polenum;
char disknum;
char src;
char dest;

int print(){
	int i, j;
	for(i=0;i<polenum;i++){
		for(j=0;j<disknum;j++){
			if(poles[i][0]==0) printf("-");
			else printf("%c", (poles[i][j]==0)? ' ' : poles[i][j]+'0');
		}
		printf(" ");
	}
	printf("\n");
}

int validate_move(int src, int dst){
	int top1=0, top2=0;
	//First pole empty
	if(poles[src][0]==0) return 1;

	//Destination pole empty
	if(poles[dst][0]==0) return 0;

	//Find the top disk for each pole
	while(poles[src][top1+1]) top1++;
	while(poles[dst][top2+1]) top2++;

	if(poles[src][top1]>poles[dst][top2]) return 1;
	return 0;
}

int move(int src, int dst){
	if(validate_move(src, dst)) return 1;
	int disk;
	int i=0;

	//Get the top ring of the source
	while(poles[src][i+1]) 
		i++;

	//Remove the disk
	disk = poles[src][i];
	poles[src][i] = 0;

	//Get the position where it belongs
	i=0;
	while(poles[dst][i])
		i++;

	//Add the disk
	poles[dst][i] = disk;

	print();

	return 0;
}

void TH(int n, int a, int b, int c){
	if(n==1) move(a, b);
	else{
		TH(n-1, a, c, b);
		move(a, b);
		TH(n-1, c, b, a);
	}
}

void clear(){
	int i;
	//Free everything
	for(i=0;i<polenum;i++){
		free(poles[i]);
	}
	free(poles);
}

int main(int argc, char *argv[]){
	int i, j, count;
	//Number of arguments
	if(argc==1){
		polenum = 3;
		disknum = 4;
		src = 0;
		dest = 1;
	}
	//Initialize poles
	poles = (char**)malloc(polenum*sizeof(char*));
	for(i=0;i<polenum;i++){
		//Initialize each pole
		poles[i] = (char*) malloc(disknum*sizeof(char));
		for(j=0;j<disknum;j++){
			//Reset each disk space
			poles[i][j] = 0;
		}
	}
	//Set the source pole
	count = disknum;
	for(i=0;i<disknum;i++){
		poles[src][i] = count;
		count--;
	}
	print();
	TH(disknum, 0, 1, 2);

	clear();
}