
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include "CPM_disp.h"


int main(){
	int P = 4;
	int n=2;
	
	int** Z = getmatrix(P,P);
	int** C = get_zeromatrix(P,P);
	getCPM(C,Z,P,3);
	
	int J=2,L=3;
	int** B = get_zeromatrix(J,L);
	
	
	int** H = CPM_disp(B,2,3,P);
	for(int i=0;i<J*P;i++){
		for(int j=0;j<L*P;j++){
			printf("%d ",H[i][j]);
			
		}
		printf("\n");
	}
	return 0;
}


