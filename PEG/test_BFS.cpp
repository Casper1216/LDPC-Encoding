#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<unordered_set>
#include<time.h>
#include <fstream>

using namespace std;

vector<int> BFS(vector<vector<int>>& col_idex,vector<vector<int>>& row_idex,int VN){		//對矩陣 v 的 VN 做subgraph 展開 找出最遠的CN 
	int m = row_idex.size(),n = col_idex.size();
		
	unordered_set<int> CN;	//紀錄造訪過的CN 
	queue<pair<int,int>>  q;
	for(int i=0;i<col_idex[VN].size();i++){
		
		
		CN.insert(col_idex[VN][i]);
		q.push({col_idex[VN][i],VN});
		
			
	} 
	
	bool is = true;
	while(!q.empty()){
		if(CN.size()==m)
			break;
		
		int q_size = q.size();
		for(int k=0;k<q_size;k++){
			int row_id = q.front().first;
			int col_id = q.front().second;
			
			q.pop();
			
			
			if(is){			// go through col
				for(int j=0;j<row_idex[row_id].size();j++){
					
					if(row_idex[row_id][j]!=col_id){
						q.push({row_id,row_idex[row_id][j]});
					}
				}
			}
			else{
				for(int i=0;i<col_idex[col_id].size();i++){
					
					if(col_idex[col_id][i]!=row_id){
						
						CN.insert(col_idex[col_id][i]);
						q.push({col_idex[col_id][i],col_id});
					}
				}
			}
			
			
		}
		is = !is;
	}
	
	unordered_set<int> temp;
	while(!q.empty()){
		temp.insert(q.front().first);
		q.pop();
	}
	vector<int> ans(temp.begin(),temp.end());
	return ans;
}

void disp(vector<vector<int>>& v){
	int m = v.size();
	for(int i=0;i<m;i++){
		for(int j=0;j<v[i].size();j++){
			cout<<v[i][j]<<' ';
		}
		cout<<endl;
		
	}
}

int main(){
	
	srand(time(0));
	
	int dv =3;
	int n = 4;
	int m = 5;
	
	vector<int> deg(m,0);	//紀錄 CN 的degree 
	vector<vector<int>> col_idex(n);	
	vector<vector<int>> row_idex(m);
	
	col_idex[0].push_back(0);
	col_idex[0].push_back(1);
	col_idex[0].push_back(2);
	col_idex[1].push_back(2);
	col_idex[1].push_back(3);
	col_idex[1].push_back(4);
	col_idex[2].push_back(4);
	row_idex[0].push_back(0);
	row_idex[1].push_back(0);
	row_idex[2].push_back(0);
	row_idex[2].push_back(1);
	row_idex[3].push_back(1);
	row_idex[4].push_back(1);
	row_idex[4].push_back(2);



	col_idex[2].push_back(1);
	row_idex[1].push_back(2);
	col_idex[2].push_back(3);
	row_idex[3].push_back(2);
	col_idex[3].push_back(0);
	row_idex[0].push_back(3);
	
	
	col_idex[3].push_back(4);
	row_idex[4].push_back(3);
	vector<int> v = BFS(col_idex,row_idex,3);
	
	
	for(auto i :v)
		cout<<i<<' ';
	cout<<endl;
	cout<<"col"<<endl;
	disp(col_idex);
	cout<<"row"<<endl;
	disp(row_idex);
	
	
	return 0;
	
}
