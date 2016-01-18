#include "Aso.hpp"

//R�̃A�\�V�G�[�V�������͏o�͌��ʐ�p�̍s���J�E���g�֐�
int Aso::get_col(ifstream &ifs){

	int num = 0;
	string s;

	for(int i=1;!ifs.eof();i++){
		ifs >> s;

		//string => int
		stringstream ss;
		int si;
		ss << s;
		ss >> si;

		//�ǂݍ��񂾕������s���ƈ�v���Ă�����
		if(si == num+1){
			num++;
		};
	}
	return num;
}

void Aso::to_var(ifstream &ifs){
	string s, tmp;

	//���[�h������E��
	for(int i=0;i < 7;i++){
		ifs >> s;

		//������������,�Ȃ�
		while(s[s.size()-1] == ','){
			tmp = s;
			ifs >> s;
			s = tmp + s;
		};

		if(i==0)continue;
		if(i==1)lhs = s;
		if(i==2)continue;
		if(i==3)rhs = s;
		if(i==4){
			stringstream sss;
			double d;
			sss << s;
			sss >> d;
			support = d;
		}
		if(i==5){
			stringstream sss;
			double d;
			sss << s;
			sss >> d;
			confidence = d;
		}
		if(i==6){
			stringstream sss;
			double d;
			sss << s;
			sss >> d;
			lift = d;
		}
	}
}

//vector<aso_data> Bigdata::aso(const CSVData &mycsv){
all_data Aso::analyze(const CSVData &mycsv){
	double d[mycsv.get_index()];
	cout << "aso start" << endl;
	for(int i = 0; i < mycsv.get_index(); i++){
		d[i] = mycsv.csv_data[i];
	}

	//���V�X�e��
	double sum, avg;
	ofstream ofs2("all/association/transaction.txt");

	for(int i=0; i < mycsv.get_row(); i++){
		//1�s���Ƃɏ���
		sum = 0.0;
		for(int j = 0; j < mycsv.get_col(); j++){
			sum += d[i*mycsv.get_col()+j];
		}

		avg = sum/mycsv.get_col();
		for(int j=0;j<mycsv.get_col();j++){
			if(d[i*mycsv.get_col()+j]>avg){
				ofs2 << mycsv.rabel[j] << ",";
			}
		}
		ofs2 << endl;
	}
	ofs2.close();

	FILE *R = popen("R --vanilla --slave","w");
	fprintf(R, "suppressMessages(library(\"arules\"))\n");
	fprintf(R, "iris.tran<-read.transactions(file='all/association/transaction.txt',sep=',',format='basket')\n");
	fprintf(R, "invisible(capture.output(iris.ap<-apriori(iris.tran)))\n");
	fprintf(R, "sink(file = \"all/association/foo.txt\")\n");
	//fprintf(R, "suppressWarnings(inspect(head(SORT(iris.ap, by = \"support\"),n=6)))\n");
	fprintf(R, "suppressWarnings(inspect(iris.ap))\n");
	fprintf(R, "sink()\n");
	fprintf(R, "q(\"no\")\n");
	fflush(R);
	//(void)pclose(R);

	vector<Aso*> aso;//�Ԃ�l�錾
	Aso *a = new Aso();

	ifstream ifs("all/association/foo.txt");

	//ifs�s���擾	
	int col = 0;
	col = a->get_col(ifs);
	cout << col<<endl;
	ifs.clear();
	ifs.seekg(0,ios_base::beg);

	//1�s�ڃX�L�b�v
	string line, st;
	getline(ifs,line);

	//2�s�ڈȍ~
	for(int i = 0; i < col; i++){
		a->to_var(ifs);
		aso.push_back(a);
	}

	ifs.close();
	/*
	   RInside R;
	   R.parseEval("suppressMessages(library(\"arules\"))");
	   R.parseEval("iris.tran<-read.transactions(file='/home/s-kotake/R/ver2.0/ver2.2/all/association/transaction.txt',sep=',',format='basket')");
	   R.parseEval("iris.ap<-apriori(iris.tran)");
	   R.parseEval("sink(file = \"foo.txt\")");
	   R.parseEval("capture.output(inspect(iris.ap))");
	   R.parseEval("sink()");
	   */
	all_data all;
	all.myad = aso;
	return all;
}

