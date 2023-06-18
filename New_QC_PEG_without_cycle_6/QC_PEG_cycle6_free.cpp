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

void CPM(vector<vector<int>>& h,int shift,int P){	// 1 ����m�b�� n �� �D�X�۹����� CPM 
	
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
void cycle6_DFS(vector<int>& equ,vector<vector<int>>& B,int x,int y,int P,
int start_x,int start_y,int dir,vector<vector<int>>& vis,bool& ans){
    //dir = 0 represent go up or down
    //dir = 1 represent go left or right
	//start_x start_y ��Base matrix ���X�o�I
    //cout<<x<<' '<<y<<endl;
    if(B[x][y]==0)
        return ;
    if(equ.size()==6&&(x==start_x&&y==start_y)){
        int sum = ((equ[0]-equ[1]) +(equ[2]-equ[3])+(equ[4]-equ[5]))%P;
        cout<<"Sum: "<<sum<<endl;
        // cout<<"equ: "<<endl;
        // for(auto e:equ){
        //     cout<<e<<" ";
        // }
        // cout<<endl;
        if(sum==0){
            ans =true;
        }
        return ;
    }
    else if(equ.size()>=6||vis[x][y]==1||ans)
        return ;
    
    int c = B.size();
    
    
    vis[x][y]=1;
    equ.push_back(B[x][y]);
    //cout<<"Su "<<x<<' '<<y<<" equ size: "<<equ.size()<<endl;
    
    if(dir==0){
        for(int i=0;i<c;i++){
            if(i!=x){
                cycle6_DFS(equ,B,i,y,P,start_x,start_y,1,vis,ans);
                
            }
                
        }
    }
    else if(dir==1){
        for(int j=0;j<=start_y;j++){
            if(j!=y){
            cycle6_DFS(equ,B,x,j,P,start_x,start_y,0,vis,ans);
            
            }
                
        }
    }
    vis[x][y]=0;
    equ.pop_back();
}
bool iscycle6_exist(vector<vector<int>>& B,int x,int y,int P){
	//�]��B��������1~P  
    //if(B[x][y]==0)
        //���L
    int c = B.size();
    
    int dir = 0;
    vector<int> equ;
    vector<vector<int>> cycle6;
    vector<vector<int>> vis(c,vector<int>(y,0));
    bool ans = false;
    cycle6_DFS(equ,B,x,y,P,x,y,0,vis,ans);
    //cout<<"Number of cycle 6: "<<cycle6.size()<<endl;
    
    

	return ans;
}


vector<int> BFS(vector<vector<int>>& H,int P,int VN,unordered_set<int>& vis_CN){
	//Construct tree with H to find farest children	
	//�B�n�׶} �w��CPM����m  
	int m = H.size(),n = H[0].size();
	
	unordered_set<int> CN_vis;			//Record visited CN 
	unordered_set<int> VN_vis;			//Record visited VN 
	
	VN_vis.insert(VN);					//vis �L��VN 
	
	vector<vector<int>> tree_CN;		//�s�� tree �C�h�� CN 
	vector<int> L1;						//tree �Ĥ@�h��CN   
	queue<pair<int,int>>  q;


	for(int i=0;i<m;i++){
		if(H[i][VN]==1){
			CN_vis.insert(i);		//vis �L��CN 
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
					
					if(H[row_id][j]==1&&!VN_vis.count(j)){		//�S�����X�L VN �~�i�i�J
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
	if(CN_vis.size()==m){		//�Y����CN �� vis �L ,�^�ǳ̩��U��CN  
		for(auto e:tree_CN[Level-1])
			cand.push_back(e);
		
	} 
	else{
		//�^�� �S�� vis �L�� CN
		
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
	
	//�^��tree�C�@�h�O�_�� �i�� idex 
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

void To_find_CPM(vector<vector<int>>& H,int P,int k,int q,int k_des,int q_des,unordered_set<int>& vis_CN,vector<vector<int>>& B
,vector<int>& deg,vector<vector<vector<int>>>& LOW_DEG,vector<vector<int>>& construct_order){
	
	//�ثe�n�إ߲� k ��col ,�� q ��CPM
	//�n�إߦܲ� k_des ��col ,�� q_des ��CPM

	//vector<vector<int>> construct_order //�x�s�إ�Base ������
	//vector<vector<vector<int>>> LOW_DEG //�x�s�C��CPM��low_deg_set

	int c = B.size(),t=B[0].size();
	int VN = k*P;

	if(q==0){
			//���s��@�� ��l�� CPM
			int pre_idex = construct_order[k][q] ;	//�W�@�ӫإߪ�CPM idex
			deg[pre_idex]--;							//degree -1
			vis_CN.erase(pre_idex);						//�R���W�@�ӫت�idex
			B[pre_idex][k]=0;
			//------------------------
			//�q�`�C��CN��go through �L�A�q�Ҧ�CN(���Fpre_idex �� CPM
			int new_idex ;
			int r = rand()%P;
			do{
				new_idex = rand()%c;

			}while(new_idex==pre_idex);

				
			vector<vector<int>> h(P,vector<int>(P,0));
			CPM(h,r,P);					//�o��CPM 
			//��J�j H 
			for(int j=0;j<P;j++){
				for(int w=0;w<P;w++){
					if(h[j][w]==1)
						H[new_idex*P+j][k*P+w]=1;
				}
			}
			
			B[new_idex][k] = (P-r)%P + 1;
			deg[new_idex]++;
			vis_CN.insert(new_idex);	//�惡block ���аO �w�� CPM 
			construct_order[k][q] = new_idex;
			return ;
			
		}
	//---------------------------------------------------
	vector<int> cn_set = BFS(H,P,k*P,vis_CN);	//��X�̩��U�� CN set �ΨS vis �쪺 CN 
						
	//cout<<"cn_set size   "<<cn_set.size()<<endl; 
	//for(auto e:cn_set)
		//cout<<e<<' ';
	//cout<<endl;
	
	
	vector<int> low_deg_set; 
	int low_d = B[0].size();				//dv = t
	int new_edge;
	int idex;
	
	map<int,vector<int>> mp;	//�NCN idex�� candidate 
								//���O��������CPM 
								//key �ĴX��CPM , value ��CPM ����idex  
	
	for(int i=0;i<cn_set.size();i++){
		idex = cn_set[i]/P;
		mp[idex].push_back(cn_set[i]%P);
		if(deg[idex]<low_d){
			low_d = deg[idex];				//���̧C degree �� CPM idex 
		}
	}
	for(int i=0;i<cn_set.size();i++){
		idex = cn_set[i]/P;
		if(deg[idex]==low_d){
			low_deg_set.push_back(idex);	//��Jlowest degree set
		}
	}
	vector<int> cand_list;
	for(auto e:mp){
		for(int i=0;i<e.second.size();i++){
			cand_list.push_back(P*e.first+e.second[i]);
		}
	}
	// cout<<"cand_list size   "<<cand_list.size()<<endl; 
	// for(auto e:cand_list)
	// 	cout<<e<<' ';
	// cout<<endl;

	int new_idex ;
	int Row_idex;
	int r;
	
	for(int i=0;i<cand_list.size();i++){
		Row_idex = cand_list[rand()%cand_list.size()];
		new_idex = Row_idex/P;
		r = Row_idex%P;		// r ���qCPM����X�Ӫ� idex

		B[new_idex][k] = (P-r)%P+1; 	//shift size ��J Base matrix 

		if(iscycle6_exist(B,new_idex,k,P)){	//��B[new_idex][k]�X�o�ˬdcycle 6
			for(int j=0;j<cand_list.size();j++){
				if(cand_list[j]==Row_idex){
					cand_list.erase(cand_list.begin()+j);
				}
			}
		}
		else{
			break;
		}	
	
	}
	if(!cand_list.empty()){
		LOW_DEG[k][q] = cand_list;		//update LOW_DEG
		B[new_idex][k] = (P-r)%P+1; 	//shift size ��J Base matrix 
		construct_order[k][q] = new_idex;


		//�W�����@�ӭn�[�JCPM idex : r					
	
		vector<vector<int>> h(P,vector<int>(P,0));
		CPM(h,r,P);					//�o��CPM h
		//��J�j H 
		for(int j=0;j<P;j++){
			for(int w=0;w<P;w++){
				if(h[j][w]==1)
					H[new_idex*P+j][k*P+w]=1;
			}
		}
				
		deg[new_idex]++;
		vis_CN.insert(new_idex);	//�惡block ���аO �w�� CPM
	}
	else{
		//candiate ���Χ��B�٦�cycle 6
		// �^�� q-1��CPM
		if(q-1>0){
			//-----------------------------�^��-------------------------------------
			int pre_idex = construct_order[k][q-1] ;	//�W�@�ӫإߪ�CPM idex
			deg[pre_idex]--;							//degree -1
			vis_CN.erase(pre_idex);						//�R���W�@�ӫت�idex
			B[pre_idex][k]=0;
			//CPM�bH����m���k0
			for(int j=0;j<P;j++){
				for(int w=0;w<P;w++){
					H[pre_idex*P+j][k*P+w]=0;
				}
			}

			//----------------------------------------------------------------------
			To_find_CPM(H,P,k,q-1,k_des,q_des,vis_CN,B,deg,LOW_DEG,construct_order);	//recursion to find another candidates from previous CPM
		}
		else{
			//go to previous col
			if(k-1==0)
				return ;
			q = t-1;
			int pre_k = k-1;
			//-----------------------------�^��-------------------------------------
			int pre_idex = construct_order[pre_k][q] ;	//�W�@�ӫإߪ�CPM idex
			deg[pre_idex]--;							//degree -1
			vis_CN.erase(pre_idex);						//�R���W�@�ӫت�idex
			B[pre_idex][pre_k]=0;
			//CPM�bH����m���k0
			for(int j=0;j<P;j++){
				for(int w=0;w<P;w++){
					H[pre_idex*P+j][pre_k*P+w]=0;
				}
			}

			//----------------------------------------------------------------------
			To_find_CPM(H,P,pre_k,q,k_des,q_des,vis_CN,B,deg,LOW_DEG,construct_order);	//recursion to find another candidates from previous CPM

		}

	}

	//--------------------------------------------------------------------

	//�]���^�� �n��|���إߧ����إߦn bottom up
	if(k<k_des){
		for(int j=k;j<k_des;j++){
			for(int i=q;i<q_des;i++){
				To_find_CPM(H,P,j,i,k_des,q_des,vis_CN,B,deg,LOW_DEG,construct_order);
			}
		}
		
	}
	if(q<q_des){
		for(int i=q;i<q_des;i++){
			To_find_CPM(H,P,k,i,k_des,q_des,vis_CN,B,deg,LOW_DEG,construct_order);
		}
	}	
	
	
}

vector<vector<int>> QCPEG(int t ,int c,int P,int dv,vector<int>& deg,vector<vector<int>>& B){
	//number of row : c
	//number of col : t
	int m = c*P;
	int n = t*P;
	vector<vector<int>> H(m,vector<int>(n,0));
	unordered_set<int> E;			//�����e��VN �ҳs��CN ���p�� 
	vector<vector<int>> construct_order(t,vector<int>(dv,-1));	//�x�s�إ�Base ������ 
																//construct_order[k][q] �N���k��col ��q�ӫإߪ�CPM idex
	vector<vector<vector<int>>> LOW_DEG(t,vector<vector<int>>(dv));	//�x�s�C��CPM��low_deg_set
																	//LOW_DEG[k][q] �N���k��col ��q�ӫإߪ�candidate list
	//Base matrix first col
	cout<<"CPM VN block: "<<0<<endl;
	for(int i=0;i<dv;i++){
		int r = rand()%c;
		
		while(E.count(r)){
			
			r = rand()%c;
			
		}
		
		int shift = rand()%(P);			//�M�wCPM shift 
		B[r][0] = (P-shift)%P + 1;
		
		vector<vector<int>> h(P,vector<int>(P,0));
		CPM(h,shift,P);					//�o��CPM 
		
		//��J�j H 
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
	
	
	//Base matrix (2 ~ t) col
	for(int k=1;k<t;k++){
		cout<<"CPM VN block: "<<k<<endl;
		
		unordered_set<int> vis_CN;			//�s����VN �w�g�� weight �� CN 
		
		for(int q=0;q<dv;q++){
			
			if(q==0){
				//�q�e����VN �ҳs��CN��X degree �̤p�����۳s 
				
				int low_d = t;		//CN degree �̤p�� block idex 
				
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
				CPM(h,r,P);					//�o��CPM 
				//��J�j H 
				for(int j=0;j<P;j++){
					for(int w=0;w<P;w++){
						if(h[j][w]==1)
							H[new_edge*P+j][k*P+w]=1;
					}
				}
				
				B[new_edge][k] = (P-r)%P + 1;
				
				deg[new_edge]++;
				
				vis_CN.insert(new_edge);	//�惡block ���аO �w�� CPM 
				
				construct_order[k][q] = new_edge;
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
							int new_edge = zerodeg_CN[rand()%(zerodeg_CN.size())];	//�o�� CN block degree �� 0 �� idex 
							
							vector<vector<int>> h(P,vector<int>(P,0));
							int r = rand()%P;
							CPM(h,r,P);					//�o��CPM 
							//��J�j H 
							for(int j=0;j<P;j++){
								for(int w=0;w<P;w++){
									if(h[j][w]==1)
										H[new_edge*P+j][k*P+w]=1;
								}
							}
							
							B[new_edge][k] = (P-r)%P+1;
							
							deg[new_edge]++;
							
							vis_CN.insert(new_edge);	//�惡block ���аO �w�� CPM
							E.insert(new_edge);
							construct_order[k][q] = new_edge;
							//cout<<"q== "<<q<<" new_edge: "<<new_edge<<' '<<"shift: "<<r<<endl;
							break;			//���N���� �u�W�[�@��edge 
						}
					}
				}
				else{
					//------------------------------------------------------------

					//add new CPM and ensure cycle 6 free
					cout<<"To find"<<endl;
					//�U���n�إ߲�k col ����q�� CPM

					To_find_CPM(H,P,k,q,k,q,vis_CN,B,deg,LOW_DEG,construct_order);	//recursion function

					//---------------------------------------------------------
					
					
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
	cin>>c;												//base matrix  row    �ƶq 
	cout<<"number of columns in Base matirx: ";	
	cin>>t;												//base matirx  column �ƶq 
		
	
	
	
	int n = t*P;		// H col �� 
	int m = c*P;		// H row �� 
	
	vector<vector<int>> h(P,vector<int>(P,0));
	
	vector<int> deg(c,0);	//���� CN ��degree 
	
	vector<vector<int>> B(c,vector<int>(t,0));
	

	//-----------------Start Record the time---------------------
    time_t  start = clock();

	vector<vector<int>>H = QCPEG(t,c,P,dv,deg,B);

	//-------------------Record the end time---------------------
    time_t end = clock();
	double diff = end - start; // ms


    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second"<<endl;
	
	display_B(B);
	//display(H);
	// for(auto e:deg)
	// 	cout<<e<<' ';
	// cout<<endl;
	
	
	// //�g�J�ɮ� CSV
	// fstream file;
	// file.open("QC_PEG Base matrix.csv");
	
	// for(int i=0;i<c;i++){
	// 	for(int j=0;j<t;j++){
			
	// 		file<<B[i][j]-1<<",";
	// 	}
	// 	file<<endl;
	// }
	// file.close();
	
	
	//Base maxtrix �g�J�ɮ� text
	ofstream ofs;
	ofs.open("QC_PEG Base matrix.txt");
	if (!ofs.is_open()) {
		cout << "Failed to open file.\n";
		return 1; // EXIT_FAILURE
	}
	
	for(int i=0;i<c;i++){
		
		for(int j=0;j<t;j++){
			
			ofs<<B[i][j]-1<<" ";
				
		}
		
		ofs<<"\n";
	}
	ofs.close();
	
	
	
	return 0;
}
