#include<iostream>
#include<fstream>

using namespace std;

int main(void)
{
		
	FILE *R = popen("R --vanilla --save --slave","w");
	fprintf(R, "library(\"arules\") \n");
	fprintf(R, "iris.tran<-read.transactions(file='transaction.txt',sep=',',format='basket')\n");
	fprintf(R, "iris.ap<-apriori(iris.tran)\n");
	fprintf(R, "sink(file = \"foo.txt\")\n");
	fprintf(R, "inspect(head(SORT(iris.ap, by = \"support\"),n=6))\n");
	fprintf(R, "sink()\n");
	fprintf(R, "q(\"no\")\n");
	fflush(R);
	pclose(R);
}
