#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[], char* envp[])
{
	FILE* gnuplot = popen("gnuplot", "w");
		fprintf(gnuplot, "set term png\n");
		fprintf(gnuplot, "set output \"result.png\"\n");
		fprintf(gnuplot, "plot \"output.txt\" index 0, \"\" index 1, \"\" index 2\n");
		fprintf(gnuplot, "exit");
	fflush(gnuplot); //バッファを書き出す

	return EXIT_SUCCESS;
}
