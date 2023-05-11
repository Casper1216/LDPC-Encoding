#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<time.h>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include <fstream>
#include <climits>
#include<map>
using namespace std;

bool is_DSS(vector<int>& s,int v){
	unordered_map<int,int> mp;

	mp[0]=1;
	;
	bool ans = true;
	for(int i=0;i<s.size();i++){
		for(int j=0;j<s.size();j++){
			if(i!=j){
				int d = (int)(s[j]-s[i])%v;
				
				if(mp.count(d)){
					ans = false;
				}
			
				mp[d]++;
				
			}
			
		}
	}

	return ans;
}

bool is_DSS_2(vector<int>& s,set<int>& diff,int v){
	set<int> diff_o;	//d1 diff
	
	for(int i=0;i<s.size();i++){
		for(int j=0;j<s.size();j++){
			if(i!=j){
				int d = (int)(s[j]-s[i])%v;
				
				if(!diff.count(d)&&!diff_o.count(d)){
					diff_o.insert(d);
					
				}
				else
					return false;
				
				
			}
			
			
		}
	}
	

	return true;
}



void DSS(int v,int k,vector<int>& d1,vector<int>&d2){	//建立一個 (v,k,2) 的 DSS

	//建立 d1 
	d1.push_back(0);
	
	
	int count=0;
	
	while(d1.size()<k){
		
		
		int t = rand()%(v-1)+1;		
		
		d1.push_back(t);
	
		
		if(!is_DSS(d1,v)){			//有重複數字 or 不是DSS 刪除並重新找數字 
			
			d1.pop_back();
		}
		
		
		count++;
		//cout<<count<<endl;
		if(count>100000){
			cout<<"d1 cant find! "<<endl;
			break;
		}	
	}
	
	
	//紀錄 d1的 diff
	 
	set<int> diff;		//儲存差值 
	
	for(int i=0;i<d1.size();i++){
		for(int j=0;j<d1.size();j++){
			if(i!=j){
				int d = (int)(d1[j]-d1[i])%v;
			
				diff.insert(d);
			}
			
			
		}
	}
	
	
	//建立 d2
	d2.push_back(0);
	count=0;
	while(d2.size()<k){
		
		
		int t = rand()%(v-1)+1;		
		
		d2.push_back(t);
		
		
		if(!is_DSS_2(d2,diff,v)){		//有重複數字 or 不是DSS 刪除並重新找數字 
			
			d2.pop_back();
		}
		
		
		//cout<<count<<endl;
		if(count++>100000){
			cout<<"d2 cant find!"<<endl;
			break;
		}
	
		
	}
	
} 



bool check(vector<int>& d1,vector<int>& d2,int v){
	
	map<int,int> diff;
	for(auto e:d2){
		if(e!=0){
			if(find(d1.begin(),d1.end(),e)!=d1.end()){
				return false;
			}
		}
		
	}
	
	bool ans = true;
	
	for(int i=0;i<d1.size();i++){
		for(int j=0;j<d1.size();j++){
			if(i!=j){
				
				int d = (int)((d1[j]-d1[i]))%v;
				if(diff.count(d))
					ans = false;
				else
					diff[d]++;
			}
			
			
		}
	}
	cout<<"d1 diff size:  "<<diff.size()<<endl;
	
	
	for(int i=0;i<d2.size();i++){
		for(int j=0;j<d2.size();j++){
			int d = (int)(d2[j]-d2[i])%v;
			if(i!=j){
				
				if(diff.count(d))
					ans = false;
				else{
					diff[d]++;
				}
					
			}
			
			
		}
	}
	cout<<"total diff size:  "<<diff.size()<<endl;
	//for(auto e:diff)
	//	cout<<e.first<<' '<<e.second<<endl;
	
	
	
	return ans;
}




int main(){
	
	srand(time(0));
	int v=450;		//	v	>	k*(k-1)
	int k=12;
	int a = 7;		//要跟 v 互質 

	/*
	vector<int> d1(k,0);
	d1[1] = 13;
	d1[2] = 22;
	d1[3] = 33;
	d1[4] = 40;
	d1[5] = 151;
	d1[6] = 185;
	d1[7] = 187;
	d1[8] = 210;
	d1[9] = 279;
	d1[10] = 310;
	d1[11] = 342;
	
	vector<int> d2(k,0);
	d2[1] = 26;
	d2[2] = 30;
	d2[3] = 96;
	d2[4] = 106;
	d2[5] = 161;
	d2[6] = 256;
	d2[7] = 275;
	d2[8] = 337;
	d2[9] = 343;
	d2[10] = 378;
	d2[11] = 390;	
	if(check(d1,d2,v))
		cout<<"correct!"<<endl;
	else
		cout<<"NOT　correct!"<<endl;
	*/
	
	
	
	vector<int> d1;
	vector<int> d2;
	vector<int> d1_v(k,0);
	vector<int> d2_v(k,0);
	
	//random 找 ( v, k ,2 ) DSS
	
	int time = 0;
	do{
	
		
		d1.clear();
		d2.clear();
	
		DSS(v,k,d1,d2);
		
		sort(d1.begin(),d1.end());
		sort(d2.begin(),d2.end());
		
		for(auto e:d1)
			cout<<e<<' ';
		cout<<endl; 
		for(auto e:d2)
			cout<<e<<' ';
		cout<<endl; 
	
		if(is_DSS(d1,v)){
			cout<<"d1 is DSS"<<endl;
		}
		else
			cout<<"d1 is not DSS"<<endl;
		if(is_DSS(d2,v)){
			cout<<"d2 is DSS"<<endl;
		}
		else
			cout<<"d2 is not DSS"<<endl;
		if(check(d1,d2,v))
			cout<<"correct!"<<endl;
		else
			cout<<"NOT　correct!"<<endl;
		
		
	
	
		for(int i=0;i<k;i++){
			d1_v[i] = (a*d1[i])%v;
			d2_v[i] = (a*d2[i])%v;
		}
		
		sort(d1_v.begin(),d1_v.end());
		sort(d2_v.begin(),d2_v.end());
			
		for(auto e:d1_v)			
			cout<<e<<' ';
		cout<<endl; 
		for(auto e:d2_v)
			cout<<e<<' ';
		cout<<endl; 
		if(is_DSS(d1_v,v)){
				cout<<"d1_v is DSS"<<endl;
		}
		else
			cout<<"d1_v is not DSS"<<endl;
		if(is_DSS(d2_v,v)){
			cout<<"d2_v is DSS"<<endl;
		}
		else
			cout<<"d2_v is not DSS"<<endl;	
		if(check(d1_v,d2_v,v))
			cout<<"correct!"<<endl;
		else
			cout<<"NOT　correct!"<<endl;
			
		time++;
	}while(!check(d1_v,d2_v,v)&&time<1000);
	///////////////////////////////////////////////
	
	/*
		vector<int> mp;		//儲存差值 
	
		for(int i=0;i<d1.size();i++){
			for(int j=0;j<d1.size();j++){
				if(i!=j){
					int d = (int)(d1[j]-d1[i]);
				
					mp.push_back(d);
				}
				
				
			}
		}
		for(int i=0;i<d2.size();i++){
			for(int j=0;j<d2.size();j++){
				if(i!=j){
					int d = (int)(d2[j]-d2[i]);
					mp.push_back(d);
				}
				
				
			}
		}
		cout<<"total mp size: "<<mp.size()<<endl;
		for(auto e:mp)
			cout<<e<<' ';
		cout<<endl;
		
	
		///////////////////////////////////////
		vector<int> mp2;		//儲存差值 
	
		for(int i=0;i<d1.size();i++){
			for(int j=0;j<d1.size();j++){
				if(i!=j){
					int d = (int)(d1_v[j]-d1_v[i]);
				
					mp2.push_back(d);
				}
				
				
			}
		}
		for(int i=0;i<d2.size();i++){
			for(int j=0;j<d2.size();j++){
				if(i!=j){
					int d = (int)(d2_v[j]-d2_v[i]);
					mp2.push_back(d);
				}
				
				
			}
		}
		cout<<"total mp size: "<<mp.size()<<endl;
		for(auto e:mp)
			cout<<e<<' ';
		cout<<endl;
	*/
	
	
	
	
	
	
	
	
	

	int L = k;
	int P = v;		// P > 2L*(L-1)
	
	//bulid Base matrix
	vector<vector<int>> E(4,vector<int>(L,0));
	
	for(int i=0;i<L;i++){
		E[1][i] = d1[i];
		E[2][i] = d2[i];
		E[3][i] = (d1[i]+d2[i])%P;
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<L;j++){
			cout<<E[i][j]<<' ';
		}
		cout<<endl;
	}
	
	//寫入檔案 CSV
	fstream file;
	file.open("DSS.csv");
	
	for(int i=0;i<4;i++){
		for(int j=0;j<L;j++){
			
			file<<E[i][j]<<",";
		}
		file<<endl;
	}
	
	file.close();
	
	
	
	
	return 0;
}
