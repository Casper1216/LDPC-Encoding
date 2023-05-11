#include<iostream>
#include<vector>

using namespace std;

bool isSidon(vector<int>& num,int idex,int m){
	
	int n = num.size();
	vector<int> v(m,0);
	
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			int sum = (num[i]+num[j])%m;
			
			if(v[sum]>0)
				return false;
			
			v[sum]++;
		}
	}
	
	return true;
}

vector<vector<int>> generateSidon(int m){
	vector<vector<int>> G(m,vector<int>(2,0));
	
	for(int i=1;i<=m-1;i++){	//m-1 set
		G[i][1] = i;
		
		
		for(int k=i+1;k<m+i;k++){
			G[i].push_back(k);
			
			if(!isSidon(G[i] , i , m)){
				G[i].pop_back();
			}
		}
		/*
		for(auto e:G[i])
			cout<<e<<' ';
		cout<<endl;
		*/
	}
	return G;
}

vector<int> BiggestSidon(vector<vector<int>>& G,int m){
	int maxL = G[0].size();
	int idex=0;
	
	for(int i=1;i<=m-1;i++){
		
		if(maxL<G[i].size()){
			idex=i;
			maxL = G[i].size();
		}
		
	}
	
	return G[idex];
}
