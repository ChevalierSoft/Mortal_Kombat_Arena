#include <stdlib.h>
#include <stdio.h>
#define N 20

int range = 2;

void aff(int mat[N][N]){
	int i = 0, j = 0;
	for (i=0; i < N; i++){
		for (j=0; j < N; j++){
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
}

void zero(int mat[N][N]){
	int i = 0, j = 0;
	for (i=0; i < N; i++){
		for (j=0; j < N; j++){
			mat[i][j]=0;
		}
	}
}

void collision_carre(int mat[N][N], int x, int y ){
	int i = 0, j = 0;

	for(i = x-range; i < x+range ; ++i){
		for(j = y-range; j < y+range ; ++j){
			if(i>=0  && i<N && j<N && j>=0){
					mat[i][j]+=1;
			}
		}
	}
}
void collision_triangle_g(int mat[N][N], int x, int y ){
	int i = x, j = y;
	int yi;
	int ax=1;

	for (;j<y+range; j++){
		for(i=x;i<x+ax; i++){
			if(i>=0  && i<N && j<N && j>=0)
				mat[j][i]+=1;
		}
		ax++;
	}
	yi=j;	//yi pour le followup²²&
	ax-=2;
	for (;j<yi+range; j++){
		for(i=x;i<x+ax; i++){
			if(i>=0  && i<N && j<N && j>=0)
				mat[j][i]+=1;
		}
		ax--;
	}

}
void collision_cercle(int mat[N][N], int x, int y ){
	int i = x, j = y;
	int yi;
	int ax=1;

	for (;j<y+range; j++){
		for(i=x;i<x+ax; i++){
			if(i>=0  && i<N && j<N && j>=0)
				mat[j][i]+=1;
		}
		ax++;
	}
	yi=j;	//yi pour le followup²²&
	ax-=2;
	for (;j<yi+range; j++){
		for(i=x;i<x+ax; i++){
			if(i>=0  && i<N && j<N && j>=0)
				mat[j][i]+=1;
		}
		ax--;
	}
	//ça ça fait de la chiasse
	/*
	j = y;
	for (;j<yi+range; j++){
		for(i=x;i>x-ax; i--){
			if(i>=0  && i<N && j<N && j>=0)
				mat[j][i]+=1;
		}
		ax++;
	}
*/


}


int main(){
	int x,y;
	int mat[N][N];
	zero(mat);
	aff(mat);
	printf("x : ");scanf("%d", &x);
	printf("y : ");scanf("%d", &y);
	printf("Range : ");scanf("%d", &range);


	while(x != -11){
		//collision_carre(mat, x, y);
		collision_carre(mat, x, y);
		aff(mat);
		printf("x : ");	scanf("%d", &x);
		printf("y : ");	scanf("%d", &y);
		printf("Range : ");	scanf("%d", &range);
		if (x == -1)
			zero(mat);
	}

	return(0);
}

























/**/
