#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<unordered_set>
#include<time.h>
#include <fstream>

using namespace std;

void disp(vector<vector<int>>& v){
	int m = v.size();
	for(int i=0;i<m;i++){
		for(int j=0;j<v[i].size();j++){
			cout<<v[i][j]<<' ';
		}
		cout<<endl;
		
	}
}

vector<int> mask_BFS(vector<vector<int>>& col_idex,vector<vector<int>>& row_idex,int x,int y){	
	//masking (x,y) ���X��n��edge �ﶵ	
	
	int m = row_idex.size(),n = col_idex.size();
	
	//�� mask �� edge 
	int dis;
	for(int j=0;j<row_idex[x].size();j++){
		if(row_idex[x][j]==y)
			dis=j;
	}
	row_idex[x].erase(row_idex[x].begin()+dis);
	
	for(int i=0;i<col_idex[y].size();i++){
		if(col_idex[y][i]==x)
			dis = i;
	}
	col_idex[y].erase(col_idex[y].begin()+dis);
	
	//********************************************
	cout<<"col"<<endl;
	disp(col_idex);
	cout<<"row"<<endl;
	disp(row_idex);
	//******************************************
	
	//�H�U��X CN �� �Կ�H 
	
		
	unordered_set<int> CN_vis;	//�����y�X�L��CN 
	unordered_set<int> VN_vis;	//�����y�X�L��VN
	queue<pair<int,int>>  q;
	
	VN_vis.insert(y);
	for(int i=0;i<col_idex[y].size();i++){
		
		CN_vis.insert(col_idex[y][i]);
		q.push({col_idex[y][i],y});
		
			
	} 
	
	bool is = true;
	cout<<"depth: "<<0<<endl;
	cout<<y<<endl;
	int depth=1;
	
	while(!q.empty()){
		if(CN_vis.size()==m)
			break;
		
		int q_size = q.size();
		cout<<"depth: "<<depth<<endl;
		depth++;
		for(int k=0;k<q_size;k++){
			int row_id = q.front().first;
			int col_id = q.front().second;
			q.pop();
			
			cout<<row_id <<' '<<col_id <<endl;
			
			
			if(is){			// go through col
				for(int j=0;j<row_idex[row_id].size();j++){
					
					if(!VN_vis.count(row_idex[row_id][j])){
						
						VN_vis.insert(row_idex[row_id][j]);
						q.push({row_id,row_idex[row_id][j]});
					}
				}
			}
			else{
				for(int i=0;i<col_idex[col_id].size();i++){
					
					if(!CN_vis.count(col_idex[col_id][i])){
						
						CN_vis.insert(col_idex[col_id][i]);
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
	vector<int> cand(temp.begin(),temp.end());	//�Կ�H 
	sort(cand.begin(),cand.end());
	
	cout<<"cand: ";
	for(auto i:cand)
		cout<<i<<' ';
	cout<<endl;
	
	return cand;
	
}



int main(){
	
	srand(time(0));
	
	int dv =2;
	int n = 6;
	int m = 4;
	
	vector<int> deg(m,0);	//���� CN ��degree 
	vector<vector<int>> col_idex(n,vector<int>(dv,0));	
	vector<vector<int>> row_idex(m);
	col_idex[0][0]=0;
	col_idex[0][1]=1;
	
	col_idex[1][0]=1;
	col_idex[1][1]=2;
	
	col_idex[2][0]=2;
	col_idex[2][1]=3;
	
	col_idex[3][0]=0;
	col_idex[3][1]=3;
	
	col_idex[4][0]=1;
	col_idex[4][1]=3;
	
	col_idex[5][0]=1;		//���_���I 
	col_idex[5][1]=2;
	
	row_idex[0].push_back(0);
	row_idex[0].push_back(3);
	
	row_idex[1].push_back(0);
	row_idex[1].push_back(1);
	row_idex[1].push_back(4);
	row_idex[1].push_back(5);	//���_���I  

	row_idex[2].push_back(1);
	row_idex[2].push_back(2);
	row_idex[2].push_back(5);
	
	row_idex[3].push_back(2);
	row_idex[3].push_back(3);
	row_idex[3].push_back(4);
	
	/*
	int dv =3;
	int n = 4;
	int m = 5;
	
	col_idex[0].push_back(0);
	col_idex[0].push_back(1);
	col_idex[0].push_back(2);
	
	col_idex[1].push_back(2);
	col_idex[1].push_back(3);
	col_idex[1].push_back(4);

	
	col_idex[2].push_back(1);
	col_idex[2].push_back(3);
	col_idex[2].push_back(4);
	
	col_idex[3].push_back(0);
	col_idex[3].push_back(3);
	col_idex[3].push_back(4);
	
	row_idex[0].push_back(0);
	row_idex[0].push_back(3);
	
	row_idex[1].push_back(0);
	row_idex[1].push_back(2);

	row_idex[2].push_back(0);
	row_idex[2].push_back(1);
	
	row_idex[3].push_back(1);
	row_idex[3].push_back(2);
	row_idex[3].push_back(3);
	
	row_idex[4].push_back(1);
	row_idex[4].push_back(2);
	row_idex[4].push_back(3);
	*/
	
	//���_���I
	int x=1,y=5; 

	vector<int> cand = mask_BFS(col_idex,row_idex,x,y);
	
	
	//********************************************
	//�� �Կ�H�� ��X�Ĥ@�� degree�̤p�� 
	
	int low_d=n,new_cn;
	
	for(int i=0;i<cand.size();i++){
		int deg = row_idex[cand[i]].size();
		if(deg<low_d){
			low_d = deg;
			new_cn = cand[i];
		}
	}
	
	//�s�^ edge 
	
	col_idex[y].push_back(new_cn);
	row_idex[new_cn].push_back(y);
	
	sort(col_idex[y].begin(),col_idex[y].end());
	sort(row_idex[new_cn].begin(),row_idex[new_cn].end());
		
	//************************************************
	cout<<"col"<<endl;
	disp(col_idex);
	cout<<"row"<<endl;
	disp(row_idex);
	//******************************************
	
	
	return 0;
	
}
