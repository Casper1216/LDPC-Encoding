#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<math.h>
#include<set>

using namespace std;


 
int main()
{
	//n = 79,89;
	
	
	
 	//q=2, 給定n 找m 
	
	//
	int n = 97;
	double m=11;
	/*
	for(int i=1;i<=100;i++){
		m = log2((n*i+1));
		if(m==(int)m)		//判斷是否為整數 
			cout<<m<<endl;
	}
	*/
	
	
	int gf = pow(2,m);
	
 	set<int> qn;
 	for(int j=1;j<n;j++){
 		qn.insert((j*j)%n);
	 }
	 for(auto e:qn)
	 	cout<<e<<' ';
	cout<<endl;
	 	
	
	set<int> K;
 	for(auto e:qn){
 		for(int i=0;i<1000;i++){
 			int	temp = (int)(e*pow(2,i))%n;
 			
 			if(temp>=0)
 				K.insert(temp);
		 }	
	}
	 for(auto e:K)
	 	cout<<e<<' ';
    return 0;
}
