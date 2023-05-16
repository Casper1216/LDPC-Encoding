#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<unordered_set>
#include<time.h>
#include <fstream>

using namespace std;


vector<int> BFS(vector<vector<int>>& col_idex,vector<vector<int>>& row_idex,int VN){		
	//做subgraph 展開 找出最遠的CN 
	int m = row_idex.size(),n = col_idex.size();
		
	unordered_set<int> CN_vis;	//紀錄造訪過的CN 
	unordered_set<int> VN_vis;	//紀錄造訪過的VN
	queue<pair<int,int>>  q;
	
	VN_vis.insert(VN);
	for(int i=0;i<col_idex[VN].size();i++){
		
		
		CN_vis.insert(col_idex[VN][i]);	
		q.push({col_idex[VN][i],VN});	
			
	} 
	
	bool is = true;
	while(!q.empty()){
		if(CN_vis.size()==m)
			break;
		
		int q_size = q.size();
		for(int k=0;k<q_size;k++){
			int row_id = q.front().first;
			int col_id = q.front().second;
			
			q.pop();
			
			
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
	vector<int> ans(temp.begin(),temp.end());
	return ans;
}


void PEG(int m ,int n,int dv,vector<int>& deg,vector<vector<int>>& col_idex,vector<vector<int>>& row_idex){
	
	
	unordered_set<int> E;		//紀錄前面VN 所連的CN 之聯集 
		
	
	for(int k=0;k<dv;k++){
		
		int r = rand()%(m);
		while(deg[r]==1)
			r = rand()%m;
		col_idex[0].push_back(r);		//idex 為 0~n-1
		row_idex[r].push_back(0);		//idex 為 0~m-1
		deg[r]++;
		E.insert(r);
	}
	
	
	for(int v=1;v<n;v++){
		cout<<"VN : "<<v<<endl;
		for(int k=0;k<dv;k++){
			
			if(k==0){
				//從前面的VN 所連的CN找出 degree 最小的做相連 
				int low_d = n;
				
				vector<int> lowdeg_set; 
				
				for(auto i:E){
					if(deg[i]<low_d){
						low_d = deg[i];
					}
				}
				for(auto i:E){
					
					if(deg[i]==low_d){
						lowdeg_set.push_back(i);
					}
				}
				int new_edge = lowdeg_set[rand()%lowdeg_set.size()];
				col_idex[v].push_back(new_edge);
				row_idex[new_edge].push_back(v);
				deg[new_edge]++;
				//cout<<"k== 0 new_edge: "<<new_edge<<endl;
				
			}
			else{
				
				if(E.size()<m){ 
					
					
					vector<int> zerodeg_CN;
					for(int y=0;y<m;y++){
						if(deg[y]==0)
							zerodeg_CN.push_back(y);
					}
					for(int i=0;i<m;i++){
						if(deg[i]==0){
							int new_edge = zerodeg_CN[rand()%(zerodeg_CN.size())];
							col_idex[v].push_back(new_edge);
							row_idex[new_edge].push_back(v);
							
							deg[new_edge]++;
							E.insert(new_edge);
							//cout<<"k== "<<k<<" new_edge: "<<new_edge<<endl;
							break;			//找到就停止 只增加一條edge 
						}
					}
				}
				else{
					
					vector<int> cn_set = BFS(col_idex,row_idex,v);	//找出最底下的CN set 
					//for(auto i:cn_set)
					//	cout<<i<<' ';
					//cout<<endl;

					vector<int> lowdeg_set; 
					int low_d = n;
					int new_edge;
					
					for(int i=0;i<cn_set.size();i++){

						if(deg[cn_set[i]]<low_d){
							low_d = deg[cn_set[i]];
						}
					}
					for(int i=0;i<cn_set.size();i++){

						if(deg[cn_set[i]]==low_d){
							lowdeg_set.push_back(cn_set[i]);
						}
					}
					new_edge = lowdeg_set[rand()%lowdeg_set.size()];
					//cout<<"new_edge: "<<new_edge<<endl;
					col_idex[v].push_back(new_edge);
					row_idex[new_edge].push_back(v);
					deg[new_edge]++;
					
				}
	
			}

		}
	}
	
	
	
	
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
	// Start Record the time
    time_t  start = clock();
	
	//***************************************************************************
	int dv ,n,m;
	
	cout<<"1dv: ";
	cin>>dv; 
	cout<<"Code length: ";
	cin>>n; 
	cout<<"number of CN: ";
	cin>>m; 
	vector<int> deg(m,0);	//紀錄 CN 的degree 
	vector<vector<int>> col_idex(n);	
	vector<vector<int>> row_idex(m);
	PEG(m,n,dv,deg,col_idex,row_idex);
	
	
	
	
	// Record the end time
    time_t end = clock();
	double diff = end - start; // ms
    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second";
	

	
	//寫入檔案 text
	ofstream ofs;
	ofs.open("PEG_H.txt");
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    int dc=0;
	for(int i=0;i<m;i++){
		if(deg[i]>dc){
			dc = deg[i];
		} 
	}
    ofs <<n<<" "<<m<< "\n";
    ofs <<dv<<" "<<dc<<"\n";
    
    for(int j=0;j<n;j++)
    	ofs <<col_idex[j].size()<<" ";
    ofs<<"\n";
    for(int i=0;i<m;i++){
    	ofs <<deg[i]<<" ";
	}
	ofs<<"\n";
	//寫入每個 col 為 1 的 row idex 
	for(int i=0;i<n;i++){
		sort(col_idex[i].begin(),col_idex[i].end());
		for(int j=0;j<col_idex[i].size();j++)
			ofs<<(col_idex[i][j]+1)<<" ";
		ofs<<"\n";
	}
	//寫入每個 row 為 1 的 col idex 
	for(int j=0;j<m;j++){
		sort(row_idex[j].begin(),row_idex[j].end());
		for(int i=0;i<row_idex[j].size();i++)
			ofs<<(row_idex[j][i]+1)<<" ";
		for(int k = dc-row_idex[j].size();k>0;k--){
			ofs<<0<<" ";
		}
		ofs<<"\n";
	}
	
	
    ofs.close();
    
	return 0;
}
