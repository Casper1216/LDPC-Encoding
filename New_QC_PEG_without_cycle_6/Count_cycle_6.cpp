#include<iostream>
#include<vector>
#include <sstream>
#include <fstream>
using namespace std;
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

void cycle6_DFS(vector<vector<int>>& cycle6,vector<int>& equ,vector<vector<int>>& B,int x,int y,int P,
int start_x,int start_y,int dir,vector<vector<int>>& vis){
    //dir = 0 represent go up or down
    //dir = 1 represent go left or right
    //cout<<x<<' '<<y<<endl;
    if(B[x][y]<0)
        return ;
    if(equ.size()==6&&(x==start_x&&y==start_y)){
        int sum = ((equ[0]-equ[1]) +(equ[2]-equ[3])+(equ[4]-equ[5]))%P;

        // cout<<"Sum: "<<sum<<endl;
        // cout<<"equ: "<<endl;
        // for(auto e:equ){
        //     cout<<e<<" ";
        // }
        // cout<<endl;

        if(sum==0){
            cycle6.push_back(equ);
        }
        return ;
    }
    else if(equ.size()>=6||vis[x][y]==1)
        return ;
    
    int c = B.size();
    int t = B[0].size();
    vis[x][y]=1;
    equ.push_back(B[x][y]);
    //cout<<"Su "<<x<<' '<<y<<" equ size: "<<equ.size()<<endl;
    if(x==start_x&&dir==0){     //在與start_x 想同col位置時，不能更向上搜尋

        for(int i=start_x;i<c;i++){
            if(i!=x){
                cycle6_DFS(cycle6,equ,B,i,y,P,start_x,start_y,1,vis);
                
            }    
        }
    }
    else{
        if(dir==0){
            for(int i=0;i<c;i++){
                if(i!=x){
                    cycle6_DFS(cycle6,equ,B,i,y,P,start_x,start_y,1,vis);
                    
                }
                
            }
        }
        else if(dir==1){
            for(int j=start_y;j<t;j++){///////////////////////////////////////
                if(j!=y){
                    cycle6_DFS(cycle6,equ,B,x,j,P,start_x,start_y,0,vis);
                }
                    
            }
        }
    }
    
    vis[x][y]=0;
    equ.pop_back();
}
int count_cycle6(vector<vector<int>>& B,int P){
	
    int c = B.size();
    int t = B[0].size();
    int dir = 0;
    vector<int> equ;
    vector<vector<int>> cycle6;
    
    for(int i=0;i<c-1;i++){         //0~c-2 row
        for(int j=0;j<t-2;j++){     //0~j-3 col 
            vector<int> equ;
            vector<vector<int>> vis(c,vector<int>(t,0));
            cout<<"Start : "<<i<<" "<<j<<endl;
            cycle6_DFS(cycle6,equ,B,i,j,P,i,j,0,vis);
            //cout<<"Cycle 6 size : "<<cycle6.size()<<endl;
        }
    }
    
    //--------------------------------------------------
    display(cycle6);
    //--------------------------------------------------

	return cycle6.size();
}

void CPM(vector<vector<int>>& h,int shift,int P){	// 1 的位置在第 n 個 求出相對應的 CPM 
	
	for(int j=0;j<P;j++){
		int idex = (j+shift)%P;
		h[idex][j]=1;
		
	}
} 

int main(){
    int P ,dv,c,t;
	cout<<"CPM size: ";
	cin>>P;
	cout<<"number of rows in Base matirx: ";
	cin>>c;												//base matrix  row    數量 
	cout<<"number of columns in Base matirx: ";	        //base matirx  column 數量
	cin>>t;	
    vector<vector<int>> B(c,vector<int>(t,0));

    //--------------------test case------------------------
    // //ans : 6 cycles
    // B[0][0]=2;B[0][1]=0;B[0][2]=1;//B[0][3]=3;
    // B[1][0]=1;B[1][1]=0;B[1][2]=2;//B[1][3]=1;
    // B[2][0]=1;B[2][1]=1;B[2][2]=1;//B[2][3]=2;
    //-----------------------------------------------------
    

    //--------------read txt------------------
	FILE *fp1 = fopen("QC_PEG Base matrix.txt", "r");
	if (fp1 == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
	for(int i=0;i<c;i++){
		for(int j=0;j<t;j++){
    		fscanf(fp1,"%d ",&B[i][j]);
		}
	}
	display(B);
    
	//----------------------------------------

   
    
    int ans = count_cycle6(B,P);
    cout<<"ans: "<<ans<<endl;
    int Num_cycle6 = ans*P;
    cout<<"Number of cycle 6: "<<Num_cycle6<<endl;

    return 0;
}