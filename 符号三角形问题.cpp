#include <iostream>
using namespace std;
	class Triangle{
		friend int Compute(int);
		private:
 			int n, //第一行的符号个数
 			half, //n*(n+1)/4
 			count, //当前"+"号个数
 			**p; //符号三角矩阵
 			long sum; //已找到的符号三角形数
 			void Backtrack(int i);
};

void Triangle::Backtrack(int t) {
 	if ((count>half)||(t*(t-1)/2-count>half)) cout<<"No!"<<endl<<"=================="<<endl; 
 	else if(t>n) { sum++;cout<<"OK"<<endl<<"=================="<<endl; }
 	else {
 		cout<<"=================="<<endl;
 		for (int i=0;i<2;i++) {
 			p[1][t]=i; //第一行符号
 			count+=i; //当前"+"号个数
 			for(int j=2;j<=t;j++) {
 				p[j][t-j+1]=p[j-1][t-j+1]^p[j-1][t-j+2];
 				count+=p[j][t-j+1];
 			}
 			for(int k=1;k<=t;k++){
 				for(int m=1;m<=t-k+1;m++){
 					cout<<(p[k][m]?'+':'-');
				}
				cout<<endl;
			 } 
			 
 			Backtrack(t+1);
 			for (int j=2;j<=t;j++) 
			 	count-=p[j][t-j+1];
 			count-=i;
 		}
 	}
}

int Compute(int n) {
 Triangle X;
 X.n=n;
 X.count=0;
 X.sum=0;
 X.half=n*(n+1)/2;
 if(X.half%2==1) return 0;
 X.half=X.half/2; 
 int **p = new int*[n+1];
 for(int i=0;i<=n;i++) { p[i]=new int[n+1]; }
 for(int i=0;i<=n;i++) {
 	for(int j=0;j<=n;j++) p[i][j]=0;
 }
 X.p=p;
 X.Backtrack(1);
 for(int i=0;i<=n;i++) { delete []p[i]; }
 delete []p;
 p=0;
 return X.sum;
}


int main() {
 cout<<"n="<<7<<"时，共有"<<Compute(7);
 cout<<"个不同的符号三角形。"<<endl; 
 system("pause");
 return 0;
} 

