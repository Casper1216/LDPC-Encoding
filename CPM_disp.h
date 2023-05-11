#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>



int** getmatrix(int m,int n){		//CMP size P ,shift n 
	int** C = (int**)malloc(m*sizeof(int*));
	for(int i=0;i<m;i++){
		C[i] = (int*)malloc(n*sizeof(int));
	} 
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(i==j){
					C[i][j]=1;
				}
			else{
				C[i][j]=0;
			}
		}
	}
	return C;
}
int** get_zeromatrix(int m,int n){		//CMP size P ,shift n 
	int** C = (int**)malloc(m*sizeof(int*));
	for(int i=0;i<m;i++){
		C[i] = (int*)malloc(n*sizeof(int));
	} 
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			
			C[i][j]=0;
		}
	}
	return C;
}

void getCPM (int** C,int** Z,int P,int n){		//CMP size P ,shift n 

	for(int j=0;j<P;j++){
		for(int i=0;i<P;i++){
			int idex = (j+n)%P;
			C[i][idex] = Z[i][j];
		}
	}
}


int** CPM_disp(int** B,int J,int L,int P){	//mat is J*L matrix ,CPM size P
	int** H = (int**)malloc(J*P*sizeof(int*));
	for(int i=0;i<J*P;i++){
		H[i] = (int*)malloc(L*P*sizeof(int));
	} 
	
	int** Z = getmatrix(P,P);
	int** C = getmatrix(P,P);
	for(int i=0;i<J;i++){
		for(int j=0;j<L;j++){
			getCPM(C,Z,P,(B[i][j])%P);
			
			
			for(int q=0;q<P;q++){
				for(int k=0;k<P;k++){
					H[q+i*P][k+j*P] = C[q][k];
				}
			}
			
		}
	}
	return H;
	
}

