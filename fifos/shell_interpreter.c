#include <stdio.h>
#include <sdlib.h>

int main()
{
	//popen returns a file pointer to a pipe
	FILE *pipe;
	int status = 0;
	if( popen("ls -l", "r") == NULL)
	{
		fprintf(stdout, "an error occured\n");	
		exit(1);

	}
	return 0;
}
