#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<unordered_set>
#include<time.h>
#include <fstream>

using namespace std;

void CPM(vector<vector<int>>& h,int shift,int P){	// 1 的位置在第 n 個 求出相對應的 CPM 
	
	for(int j=0;j<P;j++){
		int idex = (j+shift)%P;
		h[idex][j]=1;
		
	}
} 

void display(vector<vector<int>>& v){
	int m = v.size();
	for(int i=0;i<m;i++){
		for(int j=0;j<v[i].size();j++){
			cout<<v[i][j]<<' ';
		}
		cout<<endl;
		
	}
}
void display_B(vector<vector<int>>& v){
	int m = v.size();
	for(int i=0;i<m;i++){
		for(int j=0;j<v[i].size();j++){
			cout<<v[i][j]-1<<' ';
		}
		cout<<endl;
		
	}
}
vector<int> BFS(vector<vector<int>>& H,int t,int c,int P,int VN,unordered_set<int>& vis_CN){
	//Construct tree with H to find farest children	
	//且要避開 已有CPM的位置  
	int m = H.size(),n = H[0].size();
	
	unordered_set<int> CN_vis;			//紀錄造訪過的CN 
	unordered_set<int> VN_vis;			//紀錄造訪過的VN
	
	VN_vis.insert(VN);				//vis 過此VN 
	
	vector<vector<int>> tree_CN;	//存取 tree 每層的 CN 
	vector<int> L1;
	
	queue<pair<int,int>>  q;
	for(int i=0;i<m;i++){
		if(H[i][VN]==1){
			CN_vis.insert(i);		//vis 過此CN 
			L1.push_back(i);
			q.push({i,VN});
			
		}
			
	} 
	tree_CN.push_back(L1);
	
	bool is = true;
	while(!q.empty()){
		if(CN_vis.size()==m)
			break;
			
		
		int q_size = q.size();
		
		vector<int> level_CN;
		
		for(int k=0;k<q_size;k++){
			int row_id = q.front().first;
			int col_id = q.front().second;
			
			q.pop();
			
			
			if(is){			// go through col
				for(int j=0;j<n;j++){
					
					if(H[row_id][j]==1&&!VN_vis.count(j)){		//沒有拜訪過 VN 才可進入
						VN_vis.insert(j); 
						q.push({row_id,j});
					}
				}
			}
			else{
				
				for(int i=0;i<m;i++){
					
					if(H[i][col_id]==1&&!CN_vis.count(i)){
						CN_vis.insert(i);
						level_CN.push_back(i);
						q.push({i,col_id});
					}
				}
				
				
			}
			
			
		}
		if(!is)
			tree_CN.push_back(level_CN);
		is = !is;
	}
	//cout<<"tree"<<endl;
	//(tree_CN);
	//cout<<"tree end!"<<endl;
	vector<int> cand;
	int Level = tree_CN.size();
	if(CN_vis.size()==m){		//若全部CN 都 vis 過 ,回傳最底下的CN  
		for(auto e:tree_CN[Level-1])
			cand.push_back(e);
		
	} 
	else{
		//回傳 沒有 vis 過的 CN
		
		for(int i=0;i<m;i++){	
			if(!CN_vis.count(i)){
				cand.push_back(i);
			}
		}
	}
	
	for(int i=0;i<cand.size();i++){
		if(vis_CN.count(cand[i]/P)){
			cand.erase(cand.begin()+i);
			i--;
		}
	}
	
	if(cand.size()>0)
		return cand;
	
	//回看樹每一層是 否有 可用 idex 
	for(int i=Level-2;i>=0;i--){
		vector<int> pre = tree_CN[i];
		for(int i=0;i<pre.size();i++){
			if(vis_CN.count(pre[i]/P)){
				pre.erase(pre.begin()+i);
				i--;
			}
		}
		if(pre.size()>0)
			return pre;
	}
	
	return {};
		
	
}



vector<vector<int>> QCPEG(int t ,int c,int P,int dv,vector<int>& deg,vector<vector<int>>& B){
	int m = c*P;
	int n = t*P;
	vector<vector<int>> H(m,vector<int>(n,0));
	unordered_set<int> E;			//紀錄前面VN 所連的CN 之聯集 
	
	// 第一組 VN
	cout<<"CPM VN block: "<<0<<endl;
	for(int i=0;i<dv;i++){
		int r = rand()%c;
		
		while(E.count(r)){
			
			r = rand()%c;
			
		}
		
		int shift = rand()%(P);			//決定CPM shift 
		B[r][0] = (P-shift)%P + 1;
		
		vector<vector<int>> h(P,vector<int>(P,0));
		CPM(h,shift,P);					//得到CPM 
		
		//放入大 H 
		for(int j=0;j<P;j++){
			for(int w=0;w<P;w++){
				if(h[j][w]==1)
					H[r*P+j][w]=1;
			}
		}
		deg[r]++;			//CN block degree +1
		//cout<<"CN "<<r<<" deg "<<deg[r]<<endl;
		E.insert(r);
		//cout<<"q== "<<i<<" new_edge: "<<r<<' '<<"shift: "<<shift<<endl;
		
	} 
	
	
	
	for(int k=1;k<t;k++){
		cout<<"CPM VN block: "<<k<<endl;
		
		unordered_set<int> vis_CN;			//存取此VN 已經有 weight 的 CN 
		
		for(int q=0;q<dv;q++){
			
			if(q==0){
				//從前面的VN 所連的CN找出 degree 最小的做相連 
				
				int low_d = t;		//CN degree 最小的 block idex 
				
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
				
				vector<vector<int>> h(P,vector<int>(P,0));
				int r = rand()%P;
				CPM(h,r,P);					//得到CPM 
				//放入大 H 
				for(int j=0;j<P;j++){
					for(int w=0;w<P;w++){
						if(h[j][w]==1)
							H[new_edge*P+j][k*P+w]=1;
					}
				}
				
				B[new_edge][k] = (P-r)%P + 1;
				
				deg[new_edge]++;
				
				vis_CN.insert(new_edge);	//對此block 做標記 已有 CPM 
				
				
				//cout<<"q== 0 new_edge: "<<new_edge<<' '<<"shift: "<<r<<endl;
				
			}
			else{
				
				if(E.size()<c){ 
					
					
					vector<int> zerodeg_CN;
					for(int y=0;y<c;y++){
						if(deg[y]==0)
							zerodeg_CN.push_back(y);
					}
					for(int i=0;i<c;i++){
						if(deg[i]==0){
							int new_edge = zerodeg_CN[rand()%(zerodeg_CN.size())];	//得到 CN block degree 為 0 的 idex 
							
							vector<vector<int>> h(P,vector<int>(P,0));
							int r = rand()%P;
							CPM(h,r,P);					//得到CPM 
							//放入大 H 
							for(int j=0;j<P;j++){
								for(int w=0;w<P;w++){
									if(h[j][w]==1)
										H[new_edge*P+j][k*P+w]=1;
								}
							}
							
							B[new_edge][k] = (P-r)%P+1;
							
							deg[new_edge]++;
							
							vis_CN.insert(new_edge);	//對此block 做標記 已有 CPM
							E.insert(new_edge);
							//cout<<"q== "<<q<<" new_edge: "<<new_edge<<' '<<"shift: "<<r<<endl;
							break;			//找到就停止 只增加一條edge 
						}
					}
				}
				else{
					
					vector<int> cn_set = BFS(H,t,c,P,k*P,vis_CN);	//找出最底下的 CN set 或沒 vis 到的 CN 
					
					//cout<<"cn_set size   "<<cn_set.size()<<endl; 
					
					//for(auto e:cn_set)
						//cout<<e<<' ';
					//cout<<endl;
					
					
					vector<int> low_deg_set; 
					int low_d = t;
					int new_edge;
					int idex;
					
					map<int,vector<int>> mp;
					
					for(int i=0;i<cn_set.size();i++){
						idex = cn_set[i]/P;
						mp[idex].push_back(cn_set[i]%P);
						if(deg[idex]<low_d){
							low_d = deg[idex];			//找到最低 degree 的 idex 
						}
					}
					for(int i=0;i<cn_set.size();i++){
						idex = cn_set[i]/P;
						if(deg[idex]==low_d){
							low_deg_set.push_back(idex);	//放入 最低 degree set
						}
					}
					int new_idex = low_deg_set[rand()%low_deg_set.size()];
					int size = mp[new_idex].size();
					
					int r = mp[new_idex][rand()%size];
					//cout<<"q== "<<q<<endl;
					//cout<<"new_idex: "<<new_idex<<endl;
					//cout<<"new block idex: "<<r<<endl;
					vector<vector<int>> h(P,vector<int>(P,0));
					
					CPM(h,r,P);					//得到CPM 
					//放入大 H 
					for(int j=0;j<P;j++){
						for(int w=0;w<P;w++){
							if(h[j][w]==1)
								H[new_idex*P+j][k*P+w]=1;
						}
					}
							
					B[new_idex][k] = (P-r)%P+1;
								
					deg[new_idex]++;
					vis_CN.insert(new_idex);	//對此block 做標記 已有 CPM
					
					
				}
	
			}

		}
	}
	
	
	return H;
	
}




int main(){
	
	srand(time(0));
	
	
	//***************************************************************************
	int P ,dv,c,t;
	cout<<"CPM size: ";
	cin>>P;
	cout<<"Column weight: ";
	cin>>dv;
	cout<<"number of rows in Base matirx: ";
	cin>>c;												//base matrix  row    數量 
	cout<<"number of columns in Base matirx: ";	
	cin>>t;												//base matirx  column 數量 
		
	
	
	
	int n = t*P;		// H col 數 
	int m = c*P;		// H row 數 
	
	vector<vector<int>> h(P,vector<int>(P,0));
	
	vector<int> deg(c,0);	//紀錄 CN 的degree 
	
	vector<vector<int>> B(c,vector<int>(t,0));
	

	//-----------------Start Record the time---------------------
    time_t  start = clock();


	vector<vector<int>>H = QCPEG(t,c,P,dv,deg,B);

	//-------------------Record the end time---------------------
    time_t end = clock();
	double diff = end - start; // ms


    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second";
	//display(H);
	display_B(B);
	
	for(auto e:deg)
		cout<<e<<' ';
	cout<<endl;
	
	
	
	
	
	// //寫入檔案 CSV
	// fstream file;
	// file.open("QC_PEG Base matrix.csv");
	
	// for(int i=0;i<c;i++){
	// 	for(int j=0;j<t;j++){
			
	// 		file<<B[i][j]-1<<",";
	// 	}
	// 	file<<endl;
	// }
	// file.close();
	
	
	// //Base maxtrix 寫入檔案 text
	// ofstream ofs;
	// ofs.open("QC_PEG Base matrix.txt");
    // if (!ofs.is_open()) {
    //     cout << "Failed to open file.\n";
    //     return 1; // EXIT_FAILURE
    // }
	
	// for(int i=0;i<c;i++){
		
    // 	for(int j=0;j<t;j++){
    		
    // 		ofs<<B[i][j]-1<<" ";
    			
	// 	}
		
	// 	ofs<<"\n";
	// }
	// ofs.close();
	
	
	
	return 0;
}
