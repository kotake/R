#include <string>
//stringstream を使うためにインポート
#include<iostream>
#include <sstream>
//ifstreamを使うためにインポート

#include <fstream>
using namespace std;
int main(int argc,char *argv[])

{

	string str;

	stringstream ss;

	//以下のifstreamによって、csvFileNameに指定されたファイルが開かれます。

	//今回は5行5列のCSVファイルを想定します。

	//以下のように格納されてるイメージ。

	/*

	 *  1,2,3,4,5

	 *  6,7,8,9,10

	 *  11,12,13,14,15

	 *  16,17,18,19,20
	 *  21,22,23,24,25
	 */

	ifstream csvFile("test.csv");
	if(!csvFile){
		cout << "error"<<endl;
		return 1;
	}

	//以下の配列に5行5列のCSVファイルの数値データを格納します。

	double csvData[25];

	//５行分の読み出し。
	for (int row = 0; row < 5; row++)

	{

		//4列分読み出し。

		for (int col = 0; col < 4; col++)

		{

			//gelineの第1引数は読み出し開始位置を表します。

			//以下のコードの第1引数は現在の読み出し位置を表します。

			//第2引数は読み出し先を指定します。

			//第3引数は終端とする文字を指定します。

			getline(csvFile.seekg(0,ios_base::cur),str,',');

			//stringstreamに読みだしたstringを流す。

			ss.str(str);

			//stringstreamから配列に流す。

			//この時にstring型からdouble型の変換が暗黙的に行われる。

			ss>>csvData[5*row+col];

			//stringstreamを以下の２行のコードでクリアする。

			//これを行わないと前の文字が残り想定通りの数値が配列に格納できない

			ss.str("");

			ss.clear(stringstream::goodbit);

		}

		//改行コードまで読み込む。すなわち一番最後の列の数値を読み込む。

		getline(csvFile.seekg(0,ios_base::cur),str,'\n');

		ss.str(str);

		ss>>csvData[5*row+4];

		ss.str("");

		ss.clear(stringstream::goodbit);

	}

	//CSVファイルを閉じてファイルへのアクセス権を開放する。
	csvFile.close();

	//cout << str << endl;

	for (int row = 0; row < 5; row++)
	{
		//4列分読み出し。
		for (int col = 0; col < 5; col++)
		{
			cout << csvData[row*5+col]<< " ";	
		}
		cout <<endl;
	}

}
