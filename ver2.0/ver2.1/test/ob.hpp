class CSVData
{ 
	private:
		int index;
	public:
		int a;
		int b;
		int sum;
};

class CalcClass
{
	public:
		void add(CSVData Data);
	private:
};

void CalcClass::add(CSVData Data){
	Data.sum = Data.a + Data.b;
}
