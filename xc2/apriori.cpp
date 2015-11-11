//#include "bits/stdc++.h"
#include "head.hpp"

//using namespace std;

const int MIN_SUP = 1;
unsigned int row = 0;

map<vector<string>, int> C;
map<vector<string>, int> L;

char filename[] = "input.txt";
ofstream ofs("output.txt");

void aso(double *input)
{
	cout << "aso start"<<endl;
	C.clear();
	L.clear();

	bool mv=true;
	int num=2;
	while(true)
	{
		if (mv)
		{
			for(int i=0;i<index;i++){
				//cout << "input["<< i <<"]:"<< input[i] <<endl;
			}
			cout << endl;


			C1(input);
			ofs<<"C1"<<endl;
			output(C);

			L1();
			ofs<<endl<<"L1(C1の枝切り後)"<<endl;
			output(L);

			mv=!mv;
		}else
		{
			//ofs<<"else" <<endl;
			generate_C();
			if(C.size()==0)
				break;
			//cout<<"\nC"<<num<<"(要素からすべての組み合わせを表示)\n";
			//output(C);
			prune();
			if (C.size()==0)
			{
				break;
			}
			//cout<<"\nC"<<num<<" after prune(要素を枝切り) \n";
			//output(C);
			scan_D();
			//cout<<"\nC"<<num<<"after scaning dataset(枝切りした要素だけ回数数える)\n";
			//output(C);
			generate_L();
			if (L.size()==0)
			{
				break;
			}
			ofs<<"\nL"<<num<<"(C"<<num<<"を基準で枝切り後)\n";
			output(L);
			num++;
		}
		//ofs<<"-----------------------" <<endl;
	}
	cout << "finish." <<endl;
}

void C1(double *input)
{
	ifstream fin;
	fin.open(filename);
	if(!fin)
	{
		ofs <<"Input file opening error\n";
		//exit(0);
	}

	string n;
	vector<string> v;
	while(fin>>n)
		//while(>>n)
	{
		//	cout << n << endl;
		v.clear();
		if (n=="-1")
		{
			row++;
			continue;
		}
		v.push_back(n);
		if(C.count(v) == 1)//Cの中のvの数を数える
			C[v]++;
		else
			C[v]=1;
	}
	fin.close();

	/*
	   stringstream output_name;
	   output_name << "association/temp/out" << sheet_num << ".txt";
	   ofstream out;
	   out.open(output_name.str());
	   out << rabel[order[0]]<<" "<<rabel[order[1]];
	   out << " -1" << endl;

	   vector<double> tmp;
	   for(int i=0;i<row_num;i++){
	   tmp[i].push_back(input[i]);
	   tmp[i].push_back(input[i]);
	//copy(input.begin(), input.end(), back_inserter(tmp) );
	}

	out.close();
	*/
	//csv_dataを読み込む
	//岡システム
	double sum,avg;
	ofstream ofs("association/transaction.txt");
	for(int i=0;i<row_num;i++){
		//1行ごとに処理
		sum =0;
		for(int j=0;j<col_num;j++){
			sum += input[i*col_num+j];
		}
		avg = sum/col_num;
		for(int j=0;j<col_num;j++){
			if(input[i*col_num+j]>avg){
				ofs << rabel[j] << " ";
			}
		}
		ofs<<endl;
	}
	ofs.close();

	//exit(0);
}


void output(map<vector<string>, int> T)
{
	ofs<<"\n";
	vector<string> v;

	for(map<vector<string>, int>::iterator ii=T.begin();ii!=T.end();ii++)
	{
		v.clear();
		v=ii->first;
		for (int i = 0; i < v.size(); ++i)
		{
			ofs<</*"v["<<i<<"]:"<<*/v[i]<<" ";
		}

		ofs << /*" ---(frequency)----->> "<<*/ii->second<<"回 支持度：";
		ofs << (float)ii->second / (float)row;
		ofs << " 確信度：";
		ofs << " リフト値：";
		ofs << endl;
	}
}

void L1()
{

	for(map<vector<string>, int>::iterator ii=C.begin();ii!=C.end();ii++)
	{
		if (ii->second >= MIN_SUP)
		{
			L[ii->first]=ii->second;
		}
	}
}

void generate_C()
{
	//clean(C);
	C.clear();
	for(map<vector<string>, int>::iterator ii=L.begin();ii!=L.end();ii++)
	{

		for(map<vector<string>, int>::iterator jj=ii;jj!=L.end();jj++)
		{
			if(jj==ii)
				continue;
			vector<string> a,b;
			a.clear();
			b.clear();
			a=ii->first;//
			b=jj->first;//ここでも一応push_backしてる
			if(check_compatibility(a,b))	
			{
				a.push_back(b.back());
				sort(a.begin(), a.end());
				C[a]=0;
				//cout<<"if"<<endl;
			}
			//cout <<"a" <<endl;
		}
	}


}

bool check_compatibility(vector<string> a, vector<string> b)
{
	bool compatible=true;
	for (int i = 0; i < a.size()-1; ++i)
	{
		if (a[i]!=b[i])
		{
			compatible=false;
			break;
		}
	}
	return compatible;
}

void prune()
{
	vector<string> a,b;

	for(map<vector<string>, int>::iterator ii=C.begin();ii!=C.end();ii++)
	{
		a.clear();
		b.clear();

		a=ii->first;
		for(int i = 0;i<a.size();i++)
		{
			b.clear();
			for (int j = 0; j < a.size(); ++j)
			{
				if(j==i)
					continue;
				b.push_back(a[j]);
			}
			if(L.find(b)==L.end())//キーが設定されていなかったら
			{
				//cout <<"key" <<endl;
				ii->second=-1;
				break;
			}
		}
	}

	map<vector<string>, int> temp;
	temp.clear();
	for(map<vector<string>, int>::iterator ii=C.begin();ii!=C.end();ii++)
	{
		if (ii->second != -1)
		{
			temp[ii->first]=ii->second;
		}
	}

	C.clear();
	C=temp;
	temp.clear();
}

void scan_D()
{
	cout << "scan_D" <<endl;

	ifstream fin;
	fin.open(filename);
	if(!fin)
	{
		cout<<"Input file opening error\n";
		exit(0);
	}

	string n;
	vector<string> a;

	a.clear();

	for(int i =0;fin>>n;i++)/*while(fin>>n)*/
	{
		//cout << i <<endl;
		if(n=="-1" && a.size()>0)
		{
			set_count(a);
			a.clear();
			//cout << "if" <<endl;
		}else if(n!="-1")
		{
			a.push_back(n);
		}
	}
	fin.close();

	cout << "scan_d end"<<endl;
}

void set_count(vector<string> a)
{
	for(map<vector<string>, int>::iterator ii=C.begin();ii!=C.end();ii++)
	{
		vector<string> b;
		b.clear();
		b=ii->first;
		int true_count=0;
		if (b.size()<=a.size())
		{
			for (int i = 0; i < b.size(); ++i)
			{
				for (int j = 0; j < a.size(); ++j)
				{
					if(b[i]==a[j])
					{
						true_count++;
						break;
					}
				}
			}
		}

		if (true_count==b.size())
		{
			ii->second++;
		}
	}
}

void generate_L()
{
	L.clear();

	for(map<vector<string>, int>::iterator ii=C.begin();ii!=C.end();ii++)
	{
		if(ii->second >= MIN_SUP)
		{
			L[ii->first]=ii->second;
		}
	}
}
