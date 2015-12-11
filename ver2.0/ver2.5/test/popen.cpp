#include <stdio.h>
#include <stdlib.h>
#include <string>
#define BUF 256
 
int main (int argc, char *argv[])
{
	FILE *fp;
	std::string cmdline = "ls";
	if ( (fp = popen(cmdline.c_str(),"r")) == NULL) {
		perror ("can not exec commad");
		exit(EXIT_FAILURE);
	}
	char buf[BUF];

	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		printf("=> %s", buf);
	}

	(void) pclose(fp);

	exit (EXIT_SUCCESS);
}
