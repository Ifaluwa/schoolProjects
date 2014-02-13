#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
void printHelp()
{
	printf("Usage: grep-lite [OPTION]... PATTERN\n"
		"Search for PATTERN in standard input. PATTERN is a\n"
		"string. grep-lite will search standard input line by\n"
		"line, and (by default) print out those lines which\n"
		"contain pattern as a substring.\n"
		"\n"
 		"-v, --invert-match     select non-matching lines\n"
  		"-n, --line-number      print line numbers with output\n"
 		"-q, --quiet            suppress all output\n"
		"\n"
		"Exit status is 0 if any line is selected, 1 otherwise;\n"
		"if any error occurs, then the exit status is 2.\n");
}

int main(int argc, char * * argv)
{
	
	//PRINTS HELP
	int i;
        for(i = 1; i < argc; i++)
        {
        if(strcmp(argv[i], "--help") == 0)
                {
                        printHelp();
                        return EXIT_SUCCESS;
                }
        }

	//CHECK FOR BOGUS COMMANDS
	for(i = 1; i < argc - 1; i++)
	{
	if(strcmp(argv[i], "-v") == 0) return TRUE;
	else if(strcmp(argv[i], "-n") == 0) return TRUE;
	else if(strcmp(argv[i], "-q") == 0) return TRUE;
	else if(argv[i][0] == "-")
		{
			fprintf(stderr, "Error! Bogus Command line arguments!" argv[i]);
			 return 2;
		}
	else funcdefault  = TRUE
	}
	
}
