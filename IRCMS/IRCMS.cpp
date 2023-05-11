#include<iostream>
#include<vector>
#include <fstream>
#include<time.h>
using namespace std;


void disp(vector<vector<int>>& v){
	int m = v.size(),n = v[0].size();
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<v[i][j]<<' ';
		}
		cout<<endl;
		
	}
}


void allposs_seq(vector<int>& h,int len,vector<vector<int>>& ans,vector<int>& temp,int idex){	
	//找出sequence h ，長度為 len 的所有組合 
	// h 中element 不會重複 
	// hi,...,hlen 屬於 h 找出所有可能 ( hi,...,hlen ) 每個元素不相同 
	
	if(temp.size()==len){
		ans.push_back(temp);
		return ;
	}
	
	
	for(int i=idex;i<h.size();i++){
		temp.push_back(h[i]);
		allposs_seq(h,len,ans,temp,i+1);
		temp.pop_back();
	}
	
	
}

void permutation(vector<vector<int>>& ans,vector<int>& seq,int idex){
	if(idex==seq.size()){
		ans.push_back(seq);
		return ;
	}
		
	for(int i=idex;i<seq.size();i++){
		swap(seq[idex],seq[i]);		//交換
		permutation(ans,seq,idex+1);
		swap(seq[idex],seq[i]);		//交換回來 
	}
}


void all_permutation(vector<vector<int>>& all,vector<vector<int>>& s){
	
	for(int i=0;i<s.size();i++){
		vector<int> a = s[i];
		vector<vector<int>> ans;
		permutation(ans,a,0);
		
		for(int j=0;j<ans.size();j++){
			all.push_back(ans[j]);
		}
	}
	
}

vector<int> IRCMS(vector<int>& h,int J){
	vector<int> g;
	g.push_back(0);
	g.push_back(1);
	
	vector<vector<int>> all_h;
	vector<int> t;
	allposs_seq(h,3,all_h,t,0);
	vector<vector<int>> all_per_h;
	all_permutation(all_per_h,all_h);
	
	int g_len = g.back();
	
	while(g.size()<J){
		g_len++;
		//cout<<"g_len: "<<g_len<<endl;
		
		
		
		vector<vector<int>> all_g;
		vector<int> temp;
		allposs_seq(g,2,all_g,temp,0);
		vector<vector<int>> all_per_g;
		all_permutation(all_per_g,all_g);
		
		bool flag = false;
		
		for(int k=0;k<all_per_g.size();k++){
			for(int q=0;q<all_per_h.size();q++){
				
				
				
				int left = ((g_len-all_per_g[k][0])*(all_per_h[q][2]-all_per_h[q][0]));
				int right = ((all_per_g[k][1]-all_per_g[k][0])*(all_per_h[q][1]-all_per_h[q][0]));
				
				//cout<<all_per_g[k][0]<<' '<<all_per_g[k][1]<<' '<<all_per_h[q][0]<<' '<<all_per_h[q][1]<<' '<<all_per_h[q][2]<<endl;
				//cout<<"left: "<<left<<" right: "<<right<<endl;
				
				if(left==right){
				
					flag = true;
					break;
				}
					
			}
			if(flag)
				break;
		}
		if(!flag){
			g.push_back(g_len);
		}
	}
	
	return g;
}


int main(){
	
	srand(time(0));
	// Start Record the time
    time_t  start = clock();
	
	//***************************************************************************
	
	int L;
	cout<<"number of col: ";
	cin>>L;
	
	
	vector<int> h;
	
	for(int i=0;i<L/2;i++){
		h.push_back(i);
	}
	
	for(int i=L/2+1;i<=L;i++){
		h.push_back(i);
	}
	
	int J = 4;
	
	
	vector<int> g = IRCMS(h,J);
	
	int CPM_size = h.back()*g.back();
	
	for(auto i:g)
		cout<<i<<' ';
	cout<<endl;
	cout<<"CPM size lower bound: "<<CPM_size<<endl;
	cout<<"H size row: "<<J<<" col: "<<L<<endl;
	
	
	
	
	// Record the end time
    time_t end = clock();
	double diff = end - start; // ms
    cout<<"total: "<<(diff / CLOCKS_PER_SEC)<< "second";
    
    
    //Base maxtrix 寫入檔案 text
	

	ofstream ofs;
	ofs.open("IRCMS Base matrix.txt");
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
	
	for(int j=0;j<J;j++){
		
    	for(int i=0;i<L;i++){
    		cout<<g[j]*h[i]<<' ';
    		ofs<<g[j]*h[i]<<" ";
    			
		}
		cout<<endl;
		ofs<<"\n";
	}
	
	
	ofs.close();
	

	/* 
	//寫入檔案 CSV
	
	fstream file;
	file.open("IRCMS.csv");
	
	for(int j=0;j<J;j++){
		for(int i=0;i<L;i++){
			cout<<g[j]*h[i]<<' ';
			file<<g[j]*h[i]<<",";
		}
		cout<<endl;
		file<<endl;
	}
	file.close();
	
	*/ 
	
	
	
	return 0;
}
