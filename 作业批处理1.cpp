#include <iostream>
	using namespace std;
template <class Type>
	inline void Swap(Type &a, Type &b) {
 		Type temp=a;
 		a=b;
 		b=temp;
	}
	
class Flowshop {
	friend int Flow(int **M,int n,int bestx[]);
	private:
 	void Backtrack(int i);
 	int **M, // ����ҵ����Ĵ���ʱ��
 	*x, // ��ǰ��ҵ����
 	*bestx, // ��ǰ������ҵ����
 	*f2, // ���� 2 ��ɴ���ʱ��
 	f1, // ���� 1 ��ɴ���ʱ��
 	f, // ���ʱ���
 	bestf, // ��ǰ����ֵ
 	n; // ��ҵ��
};

void Flowshop::Backtrack(int i) {
 	if(i>n) {
 	for(int j=1; j<=n; j++) { bestx[j] = x[j]; }
 	bestf = f;
 	cout<<"enough!i="<<i<<">"<<n<<"  bestf="<<bestf<<endl; 
 	}
 	else {
 	for (int j = i; j <= n; j++) {
 		cout<<"i="<<i<<'\t'<<"j="<<j<<endl;
 		cout<<"f1="<<f1<<'+'<<M[x[j]][1]<<'=';
	 	f1+=M[x[j]][1];
 		cout<<f1<<endl;
 		//���� 2 ִ�е��ǻ��� 1 ����ɵ���ҵ�������� i-1
 		cout<<"f2["<<i<<"]="<<((f2[i-1]>f1)?f2[i-1]:f1)<<'+'<<M[x[j]][2]<<'=';
		f2[i]=((f2[i-1]>f1)?f2[i-1]:f1)+M[x[j]][2];
 		cout<<f2[i]<<endl;
 		
 		cout<<"f="<<f<<'+'<<f2[i]<<"=";
 		f+=f2[i];
 		cout<<f<<endl;
 		
 		if(f < bestf) { //��֦
 			cout<<"����j="<<j<<"��λ�õ�Ԫ�ػ�����i="<<i<<"��λȥ"<<endl; 
 			Swap(x[i], x[j]);
 			
			{
			cout<<"===================================="<<endl;
			cout<<'x'<<'\t';
 			for(int k=1;k<=i;k++)
 			cout<<x[k]<<'\t';
 			cout<<endl<<"f2"<<'\t';
 			for(int k=1;k<=i;k++)
 			cout<<f2[k]<<'\t';
 			cout<<endl;
 			cout<<"===================================="<<endl;
			}
	
 			cout<<endl<<"go to i="<<i+1<<endl;
 			Backtrack(i+1);
 		
 			Swap(x[i], x[j]);
 			cout<<"����j="<<j<<"��λ�õ�Ԫ�ػ��ص�i="<<i<<"��λȥ"<<endl; 
			cout<<endl<<"return to i="<<i<<endl;
 		}
 		else cout<<f<<">="<<bestf<<"cut down"<<endl;
 		
 		cout<<"f1="<<f1<<'-'<<M[x[j]][1]<<'=';
	 	f1-=M[x[j]][1];
 		cout<<f1<<endl;
 		
 		
 		cout<<"f="<<f<<'-'<<f2[i]<<"=";
 		f-=f2[i];
 		cout<<f<<endl;
 	}
 }
}

int Flow(int **M,int n,int bestx[]) {
 int ub=30000;
 Flowshop X;
 X.n=n;
 X.x=new int[n+1];
 X.f2=new int[n+1];
 X.M=M;
 X.bestx=bestx;
 X.bestf=ub;
 X.f1=0;
 X.f=0;
 for(int i=0;i<=n;i++) { X.f2[i]=0,X.x[i]=i; }
 X.Backtrack(1);
 delete []X.x;
 delete []X.f2;
 return X.bestf;
}
int main() { 
 int n=3,bf;
 int M1[4][3]={{0,0,0},{0,2,1},{0,3,1},{0,2,3}};
 int **M=new int*[n+1];
 for(int i=0;i<=n;i++) { M[i]=new int[3]; }
 cout<<"M(i,j)ֵ���£�"<<endl;
 for(int i=0;i<=n;i++) {
 for(int j=0;j<3;j++){ M[i][j]=M1[i][j]; }
 }
 int bestx[4];
 for(int i=1;i<=n;i++) {
 cout<<"(";
 for(int j=1;j<3;j++) cout<<M[i][j]<<" ";
 cout<<")";
 }
 cout<<endl;
 bf=Flow(M,n,bestx);
 for(int i=0;i<=n;i++) { delete []M[i]; }
 delete []M;
 M=0;
 cout<<endl<<"����ֵ�ǣ�"<<bf<<endl;
 cout<<"���ŵ����ǣ�";
 for(int i=1;i<=n;i++) { cout<<bestx[i]<<" "; }
 cout<<endl;
 system("pause");
 return 0;
} 

