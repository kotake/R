#include "CSVData.hpp"

//template <class T>
void CSVData::save_to(const string filename){

}

//template <class T>
void CSVData::load_from(const string filename){

	//CSVData object;

	ifstream fin, row_num_check;
	fin.open(filename);

	if(!fin){
		cout << "�t�@�C�����I�[�v���ł��܂���B"<<endl;
	}
	row_num_check.open(filename);

	//char buf;

	string line,temp;

	col_num = 0;
	row_num = 0;
	index = 0;

	//1�s�ڂ�rabel�Ƃ��ēǂݍ���
	getline(fin,line);
	stringstream s1;
	s1<<line;
	string value;
	while(getline(s1,value,','))
	{	
		if(value == "\0")//�Z������̏ꍇ0������
		{ 
			value = "0";
		}

		rabel.push_back(value);
		col_num++;
	}	

	cout<<"col_num:"<< col_num <<endl;;

	//���̓t�@�C���̍s���m�F
	while(getline(row_num_check, temp)){
		row_num++;
	}
	row_num = row_num - 1;

	//2�s�ڂ���ǂݍ���
	while(getline(fin, line)){
		stringstream s2;
		s2 << line;
		double d;
		//�������ǂݍ��񂾍s����J���}�܂ł̓ǂݍ��݂��J��Ԃ�
		while(getline(s2, value, ',')){
			if(value == "\0")//�Z������̏ꍇ0������
			{ 
				value = "0";
			}
			stringstream ss(value);
			ss >> d;
			csv_data.push_back(d);

			index++;
		}
	}

	if(index % row_num!=0)
	{
		cout<<"������csv�t�@�C���ł͂���܂���B�c���̃T�C�Y�����킹�Ă��������B"<<endl;
	}

	if(col_num != index / row_num) cout<<"�Ȃɂ�����������"<<endl;
	cout << "index:"<< index<<" row_num:"<< row_num << " col_num:"<< index / row_num << endl;
}
