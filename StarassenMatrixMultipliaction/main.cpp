#include <iostream>
#include <time.h>

using namespace std;
const int threshold = 2; 

int** CreateMatrix(int n){
	int **array;
	array = new int*[n];
	for(int i=0;i<n;i++){
		array[i] = new int[n];
	}
	return array;
}

void printMatrix(int n,int **A){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout << A[i][j] << '\t';
		}
		cout << endl;
	}
}

int** sumMatrix(int n,int **A,int **B){
	int **sum = CreateMatrix(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			sum[i][j] = A[i][j] + B[i][j];
		}
	}
	return sum;
}

int** subMatrix(int n,int **A,int **B){
	int **sub = CreateMatrix(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			sub[i][j] = A[i][j] - B[i][j];
		}
	}
	return sub;
}

// we will use just for 2x2 matrixes
int** multiMatrix(int n,int **A,int **B){
	int** mult = CreateMatrix(n);
	int sum=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			mult[i][j] = 0;
			for(int k=0;k<n;k++){
				mult[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return mult;
}

// Partition A Matrix To 4 Matrix
int** partitionMatrix(int n,int **A,int i_start,int j_start){
	n=n/2;
	int** res = CreateMatrix(2);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			res[i][j] = A[i+i_start][j+j_start];
		}
	}
	return res;
}

int** mergeMatrix(int n,int **A11,int **A12,int **A21,int **A22){
	n = n*2;
	int** res = CreateMatrix(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i<n/2 and j<n/2){
				res[i][j] = A11[i][j];
			}else if(i>=n/2 and j<n/2){
				res[i][j] = A21[i-n/2][j];
			}else if(i<n/2 and j>=n/2){
				res[i][j] = A12[i][j-n/2];
			}else{
				res[i][j] = A22[i-n/2][j-n/2];
			}
		}
	}
	return res;

}
int** strassen(int n,int **A,int **B){
	if(n<=threshold){
		return multiMatrix(n,A,B); 
	}else{
		// partition A and B to 4 matrix
		int **A11 = partitionMatrix(n,A,0,0);
		int **A12 = partitionMatrix(n,A,0,n/2);
		int **A21 = partitionMatrix(n,A,n/2,0);
		int **A22 = partitionMatrix(n,A,n/2,n/2);
		int **B11 = partitionMatrix(n,B,0,0);
		int **B12 = partitionMatrix(n,B,0,n/2);
		int **B21 = partitionMatrix(n,B,n/2,0);
		int **B22 = partitionMatrix(n,B,n/2,n/2);
		int **m1 = strassen(n/2,sumMatrix(n/2,A11,A22),sumMatrix(n/2,B11,B22));
		int **m2 = strassen(n/2,sumMatrix(n/2,A21,A22),B11);
		int **m3 = strassen(n/2,A11,subMatrix(n/2,B12,B22));
		int **m4 = strassen(n/2,A22,subMatrix(n/2,B21,B11));
		int **m5 = strassen(n/2,sumMatrix(n/2,A11,A21),B22);
		int **m6 = strassen(n/2,subMatrix(n/2,A21,A11),sumMatrix(n/2,B11,B12));
		int **m7 = strassen(n/2,subMatrix(n/2,A12,A22),sumMatrix(n/2,B21,B22));
		// create C partions
		int **C11 = subMatrix(n/2,sumMatrix(n/2,sumMatrix(n/2,m1,m4),m7),m5);
		int **C12 = sumMatrix(n/2,m3,m5);
		int **C21 = sumMatrix(n/2,m2,m4);
		int **C22 = subMatrix(n/2,sumMatrix(n/2,sumMatrix(n/2,m1,m3),m6),m2);
		return mergeMatrix(n/2,C11,C12,C21,C22);
	}
}

int main(){

	srand(time(NULL));
	int temp = 0;
	int n = 4;
	int **A = CreateMatrix(n);
	// seed Matrix A
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			A[i][j] = rand()%15+1;
		}
	}
	int **B = CreateMatrix(n);
	// seed Matrix B
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			B[i][j] = rand()%15+1;
		}
	}
	
	cout << "Matrix A:"<<endl;
	printMatrix(n,A);
	cout << "Matrix B:"<<endl;
	printMatrix(n,B);
	// Partion Works Perfectly
	// Merge Works Perfectly Too
	cout<<"A*B:"<<endl;
	printMatrix(n,strassen(n,A,B));
	return 0;
}
