#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void)
{
/*
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
*/

	string filename ="transaction.txt";
	string rscript=
		"suppressMessages(library(arules))\n"
		"iris.tran<-read.transactions(file='"filename"',sep=',',format='basket'))\n"
		"invisible(capture.output(iris.ap<-apriori(iris.tran)))\n"
		"suppressMessages(sink(file = \"foo.txt\"))\n"
		"suppressWarnings(inspect(head(SORT(iris.ap, by = \"support\"),n=6)))\n"
		"suppressMessages(sink())\n";
	//cout << rscript;

	FILE *rs = popen("Rscript --vanilla --save --slave script.R","w");
	pclose(rs);

}
