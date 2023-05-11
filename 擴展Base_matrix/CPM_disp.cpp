#include<iostream>
#include<vector>
#include<algorithm>

#include<string.h>
#include <sstream>
#include <fstream>


using namespace std;


vector<vector<int>> get_CPM(int P,int shift,vector<vector<int>>& I){
	
	vector<vector<int>> C(P,vector<int>(P,0));
	for(int i=0;i<(P);i++){
		int idex = (i+shift)%P;
		C[i][idex]=1;
	}

	return C;
} 





int main(){
	int P;
	cout<<"enter CPM size: "<<endl;
	cin>>P;
	
	
	
	vector<vector<int>> B;
	
	//readfile
	fstream file;
	//file.open("DSS.csv");
	//file.open("IRCMS.csv");
	//file.open("sidon_M.csv");
	file.open("QC_PEG Base matrix.csv");
	
	//讀檔讀到跳行字元
	int i=0;
	string line;

    while(getline(file,line))
    {
        stringstream lineStream(line);
        string cell;
        vector<int> row;
        while(std::getline(lineStream,cell,','))
        {
            row.push_back(atoi(cell.c_str()));	//把string 轉成char* 再轉成 int   
        }

        B.push_back(row);
    }
	file.close();
	
	
	
	int m = B.size();
	int n = B[0].size();
	for(int j=0;j<m;j++){
		for(int k=0;k<n;k++){
			cout<<B[j][k]<<' ';
		}
		cout<<endl;
	}
	
	/*
	int m = 2;
	int n = 4;
	vector<vector<int>> b(m,vector<int>(n,0));
	
	b[0][1]=3;
	b[0][0]=1;
	*/
	
	
	
	
	
	vector<vector<int>> I(P,vector<int>(P,0));
	for(int i=0;i<(P);i++){
		for(int j=0;j<(P);j++){
			if(i==j){
				I[i][j]=1;
			}
		
		}
		
	}
	
	
	vector<vector<int>> H(m*P,vector<int>(n*P,0));
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			vector<vector<int>> C = get_CPM(P,B[i][j]%P,I);
			
			//vector<vector<int>> C = get_CPM(P,(b[i][j]%P),I);
			
			for(int q=0;q<P;q++){
				for(int k=0;k<P;k++){
					H[i*P+q][j*P+k] = C[q][k];
					
				}
			}
			
			
		}
	}
	
	/*
	for(int i=0;i<(m*P);i++){
		for(int j=0;j<(n*P);j++){
			cout<<H[i][j]<<' ';
		}
		cout<<endl;
	}
	*/
	
	
	//寫入檔案 text
	ofstream ofs;
	ofs.open("H_base.txt");
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; // EXIT_FAILURE
    }
    
   	//dv = m;
   	//dc = n;
    ofs <<P*n<<" "<<P*m<< "\n";
    ofs <<m<<" "<<n<<"\n";
    //col weight
    for(int j=0;j<P*n;j++)
    	ofs <<m<<" ";
    ofs<<"\n";
    //row weight
    for(int i=0;i<P*m;i++){
    	ofs <<n<<" ";
	}
	ofs<<"\n";
	//寫入每個 col 為 1 的 row idex 
	for(int j=0;j<P*n;j++){
		int count=0;
    	for(int i=0;i<P*m;i++){
    		if(H[i][j]==1){
    			ofs<<i+1<<" ";
    			count++;
			}
		}
		
		while(count<m){
			ofs<<0<<" ";
    		count++;
		}
		ofs<<"\n";
	}
	//寫入每個 row 為 1 的 col idex 
	for(int i=0;i<P*m;i++){
		int count=0;
    	for(int j=0;j<P*n;j++){
    		if(H[i][j]==1){
    			ofs<<j+1<<" ";
    			count++;
			}
		}
		while(count<n){
			ofs<<0<<" ";
    		count++;
		}
		ofs<<"\n";
	}
	
	return 0;
}

