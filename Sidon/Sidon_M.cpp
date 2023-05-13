#include<iostream>
#include<vector>
#include <fstream>
#include "Sidon.h"
#include<time.h>
using namespace std;

int main(){
	
		srand(time(0));
	// Start Record the time
    time_t  start = clock();
	
	//***************************************************************************
	
	int m,L;
	cout<<"CPM size: "<<endl;
	cin>>m;
	cout<<"number of col: "<<endl;
	cin>>L;
	vector<vector<int>> G = generateSidon(m);
	/*
	for(int i=0;i<G.size();i++){
		for(int j=0;j<G[i].size();j++){
			cout<<G[i][j]<<' ';
		}
		cout<<endl;
	}*/
	
	
	vector<int> seq = BiggestSidon(G,m);
	cout<<seq.size()<<endl;
	for(int i=0;i<seq.size();i++){
		cout<<seq[i]<<' ';
	}
	
	cout<<endl;
	if(seq.size()<2*L-1){
		cout<<"L is not long enough"<<endl;
		return 0;
	}
	
	
	
	
	//sidon M
	
	//int L = (seq.size()+1)/2; 
	
	
	vector<int> s1(seq.begin(),seq.begin()+L);	//0~L-1
	vector<int> s2(seq.begin()+L,seq.begin()+2*L-1);	//L~end
	s2.insert(s2.begin(),0);
	cout<<"s1: "<<endl;
	for(auto e:s1)
		cout<<e<<' ';
	cout<<endl;
	cout<<"s2: "<<endl;
	for(auto e:s2)
		cout<<e<<' ';
	cout<<endl;
	
	vector<vector<int>> E(4,vector<int>(L,0));
	
	for(int i=0;i<L;i++){
		E[1][i] = s1[i];
		E[2][i] = s2[i];
		E[3][i] = (s1[i]+s2[i])%m;
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<L;j++){
			cout<<E[i][j]<<' ';
		}
		cout<<endl;
	}
	
	// Record the end time
    time_t end = clock();
	double diff = end - start; // ms
    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second";
	
	
	//寫入檔案 CSV
	fstream file;
	file.open("sidon_M.csv");
	
	for(int i=0;i<4;i++){
		for(int j=0;j<L;j++){
			
			file<<E[i][j]<<",";
		}
		file<<endl;
	}
	
	file.close();
	
	
	
	
	/***********************************************************/
	/*
	//建構 col 4 的siden
	 
	//寫入檔案 CSV
	fstream file;
	file.open("B_sidon_col_w_4.csv");
    
    
    int col = 26;
    int s = seq.size();
    for(int j=0;j<col;j++){
		
		file <<0<<",";
	}
	file<<endl;
    int i=0,loc=0;
    for(i=0;i<loc+col;i++){
		
		file << seq[i]<<",";
	}
	file<<endl;
	loc = i;
	for(i;i<loc+col;i++){
    	int c = (i)%s;			//接著繼續擺放 
		file<<seq[c]<<",";
	}
	file<<endl;
	
	loc = i;
	for(i;i<loc+col;i++){
		//cout<<i<<endl;
    	int c = (i)%s;	
		file<<seq[c]<<",";
	}
	file<<endl;
	file.close();
	*/
	
	return 0;
}
