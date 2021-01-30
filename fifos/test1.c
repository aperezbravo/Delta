#include <stdio.h>
#include <stdlib.h>

int main()
{
	if( popen("lbs", "z") == NULL)// || -1)
	{
		fprintf(stdout, "NULL was returned \n");
	}
	return 0;
}
