#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<unordered_set>
#include <fstream>
#include<time.h>
using namespace std;






vector<int> BFS(vector<vector<int>>& v,int VN){		//��x�} v �� VN ��subgraph �i�} ��X�̻���CN 
	int m = v.size(),n = v[0].size();
	unordered_set<int> CN_vis;	//�����y�X�L��CN 
	unordered_set<int> VN_vis;	//�����y�X�L��VN
	queue<pair<int,int>>  q;
	
	VN_vis.insert(VN);
	for(int i=0;i<m;i++){
		if(v[i][VN]==1){
			CN_vis.insert(i);
			
			q.push({i,VN});
			
		}
			
	} 
	
	
	cout<<"depth: "<<0<<endl;
	cout<<VN<<endl;
	int depth=1;
	
	
	
	bool is = true;
	while(!q.empty()){
		if(CN_vis.size()==m)
			break;
			
			
			
		int q_size = q.size();
		
		cout<<"depth: "<<depth<<"queue size: "<<q_size<<endl;
		depth++;
		
		
		for(int k=0;k<q_size;k++){
			int row_id = q.front().first;
			int col_id = q.front().second;
			
			q.pop();
			
			cout<<row_id <<' '<<col_id <<endl;
			
			if(is){			// go through col
				for(int j=0;j<n;j++){
					
					if(v[row_id][j]==1&&!VN_vis.count(j)){		//�S�����X�L VN �~�i�i�J
						VN_vis.insert(j); 
						q.push({row_id,j});
					}
				}
			}
			else{
				for(int i=0;i<m;i++){
					
					if(v[i][col_id]==1&&!CN_vis.count(i)){
						CN_vis.insert(i);
						q.push({i,col_id});
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



vector<vector<int>> PEG(int m ,int n,int dv,vector<int>& deg){
	
	vector<vector<int>> H(m,vector<int>(n,0));
	unordered_set<int> E;	//�����e��VN �ҳs��CN ���p�� 
	for(int k=0;k<dv;k++){
		H[k][0]=1;
		deg[k]++;
		E.insert(k);
	}
	
	
	for(int v=1;v<n;v++){
		cout<<"VN : "<<v<<endl;
		for(int k=0;k<dv;k++){
			
			if(k==0){
				//�q�e����VN �ҳs��CN��X degree �̤p�����۳s 
				int low_d = n;
				int new_edge;
				for(auto i:E){
					//cout<<i<<endl;
					if(deg[i]<low_d){
						new_edge = i;
						low_d = deg[i];
					}
				}
				H[new_edge][v]=1;
				deg[new_edge]++;
				cout<<"k==0 new_edge: "<<new_edge<<endl;
				
			}
			else{
				
				if(E.size()<m){ 
					for(int i=0;i<m;i++){
						if(deg[i]==0){
							H[i][v]=1;
							deg[i]++;
							E.insert(i);
							break;			//���N���� �u�W�[�@��edge 
						}
					}
				}
				else{
					
					vector<int> cn_set = BFS(H,v);
					for(auto i:cn_set)
						cout<<i<<' ';
					cout<<endl;
					
					int low_d = n;
					int new_edge;
					
					for(int i=0;i<cn_set.size();i++){
						
						if(deg[cn_set[i]]<low_d){
							new_edge = cn_set[i];
							low_d = deg[cn_set[i]];
						}
						
						
					}
					cout<<"new_edge: "<<new_edge<<endl;
					H[new_edge][v]=1;
					deg[new_edge]++;
					
				}
	
			}

		}
	}
	return H;
	
}

void disp(vector<vector<int>>& v){
	int m = v.size(),n = v[0].size();
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<v[i][j]<<' ';
		}
		cout<<endl;
		
	}
}


int main(){
	// Start Record the time
    time_t  start = clock();
	
	//***************************************************************************
	int dv =2;
	int n = 6;
	int m = 4;
	
	vector<int> deg(m,0);	//���� CN ��degree 
	vector<vector<int>>H = PEG(m,n,dv,deg);
	//disp(H);
	
	// Record the end time
    time_t end = clock();
	double diff = end - start; // ms
    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second";
	
	
	
	//�g�J�ɮ� CSV
	fstream file;
	file.open("PEG_regular.csv");
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			
			file<<H[i][j]<<",";
		}
		file<<endl;
	}
	file.close();
	
	
	//�g�J�ɮ� text
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
    	ofs <<dv<<" ";
    ofs<<"\n";
    for(int i=0;i<m;i++){
    	ofs <<deg[i]<<" ";
	}
	ofs<<"\n";
	//�g�J�C�� col �� 1 �� row idex 
	for(int j=0;j<n;j++){
		int count=0;
    	for(int i=0;i<m;i++){
    		if(H[i][j]==1){
    			ofs<<i+1<<" ";
    			count++;
			}
		}
		
		while(count<dv){
			ofs<<0<<" ";
    		count++;
		}
		ofs<<"\n";
	}
	//�g�J�C�� row �� 1 �� col idex 
	for(int i=0;i<m;i++){
		int count=0;
    	for(int j=0;j<n;j++){
    		if(H[i][j]==1){
    			ofs<<j+1<<" ";
    			count++;
			}
		}
		while(count<dc){
			ofs<<0<<" ";
    		count++;
		}
		ofs<<"\n";
	}
	
	
    ofs.close();
    
	return 0;
}
