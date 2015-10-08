#include <mpi.h>  // <stdio.h> より先 
#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h> 
#include "statistics.h"

using namespace std;
using namespace alglib;

int csvfile_open(string filename)
{
	ifstream fin(filename);

	if( !fin ) {
		cout << "Error:Input data file not found" << endl;
		return;
	}

	string str;
	int hoge,huga;
	while( getline( fin, str ) ){ //ファイルから行入力
		string token;
		stringstream ss, ss2;

		//istringstream stream( str );

		//getlineの第1引数は読み出し開始位置を表す
		//以下のコードの第1引数は現在の読み出し位置を表す
		//第2引数は読み出し先を指定
		//第3引数は終端とする文字を指定する
		while( getline( fin, token, ',' ) ) {//ファイルから列入力。終わりまで
			ss << token;//数値に変換
			ss >> hoge;
		}
		ss2 << token;//数値に変換
		ss2 >> huga;
	}
	cout >> hoge >> huga >> endl;
	return;
}

int main(int argc, char* argv[]) { 
	int myrank, buffer; 
	MPI_Status status; 

	// MPIライブラリを初期化する。 
	MPI_Init(&argc, &argv); 

	// 自分のランクを調べる。 
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 

	printf("%d: start.\n", myrank); 

	int const TAG = 1234; 
 	//マスタノード 
	if (myrank == 0) { 
		csvfile_open(iris.csv);

		buffer = 10; 
		int i = 0;

		for(i = 1 ; i < 4 ; i++){
			cout << myrank <<": sent "<< buffer <<" to rank "<< i <<endl;
			MPI_Send(&buffer, 1, MPI_INT, i, TAG, MPI_COMM_WORLD); 
		}

		// MPI_Recv()は、ブロックする。 
		for(i = 1 ; i < 4 ; i++){
			MPI_Recv(&buffer, 1, MPI_INT, i, TAG, MPI_COMM_WORLD, &status); 
			cout << myrank <<": received "<< buffer <<" from rank "<<i<<endl;
		}

		// ALGLIBを用いた相関係数の算出

		real_1d_array x = "[0,1,4,9,16,25,36,49,64,81]";
		real_1d_array y = "[0,1,2,3,4,5,6,7,8,9]";
		double v;

		cout.precision(8);

		// 共分散
		v = cov2(x, y);
		cout << "共分散: " << double(v) << endl;

		// Pearsonの相関係数
		v = pearsoncorr2(x, y);
		cout << "Pearsonの相関係数: " << double(v) << endl;

		// Spearmanの相関係数
		v = spearmancorr2(x, y);
		cout << "Spearmanの相関係数: " << double(v) << endl;
	} 

	else if (myrank == 1) { 
		MPI_Recv(&buffer, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status); 
		cout << "私は相関分析をする。" << myrank <<": recv "<< buffer <<endl;
		//ここに相関分析の処理を書く

		buffer *= 2; 
		MPI_Send(&buffer, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD); 
	}

	else if (myrank == 2) { 
		MPI_Recv(&buffer, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status); 
		cout << "私はクラスタ分析をする。" << myrank <<": recv "<< buffer <<endl;
		//ここにクラスタ分析の処理を書く
		buffer *= 2; 
		MPI_Send(&buffer, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD); 
	} 

	else if (myrank == 3) { 
		MPI_Recv(&buffer, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status); 
		cout << "私はアソシエーション分析をする。" << myrank <<": recv "<< buffer <<endl;
		//ここにアソシエーション分析の処理を書く
		buffer *= 2; 
		MPI_Send(&buffer, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD); 
	} 

	MPI_Finalize(); 
	return 0; 
}
