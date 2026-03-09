#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startChanging(int argc, char** argv, FILE* source, FILE* dest)
{
	int argCounter = 1;
	int c;
	int c2;
	while((c = fgetc(source)) != EOF)
	{
		//Overwrite this part with our data now
		if(c == 'g')
		{
			c2 = fgetc(source);
			if(c2 == EOF)
			{
				fputc(c, dest);
				break;
			}

			switch(c2)
			{
				case 'S':
				case 'N':
				case 'Z':
				case 'R':
					fprintf(dest, "%d", atoi(argv[argCounter]));
					argCounter++;
				break;
				case 'Q':
					fprintf(dest, "%f", atof(argv[argCounter]));
					argCounter++;
				break;
				default:
					fputc(c, dest);
					fputc(c2, dest);
				break;
			}
		}
		else
		{
				fputc(c, dest);
		}
	}

	return;
}

//We assume that numbers are passed through CLI in order they are to be replaced. Your fault if they arent
int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("For this specific file, you need to do ./main num1 num2\n");
		return -1;
	}
	//First, we create a copy of the program
	FILE* source;
	FILE* dest;
	char* filename = "algo.silq";
	source = fopen(filename, "r");
	if(source == NULL)
	{
		fclose(source);
		return -1;
	}


	//We denote in algo.silq numbers as:
	//gS = boolean
	//gN = natural numbers
	//gZ = integers
	//gQ = rational
	//gR = reals
	// All of these are inherently classical in this program, as we are writing a C program.
	
	//Pre-determined file name
	char* dest_file = "algo_rewrite.slq";
	dest = fopen(dest_file, "w");
	if(dest == NULL)
	{
		fclose(dest);
		fclose(source);
		return -1;
	}

	startChanging(argc, argv, source, dest);

	int pipefds[2];
	pipe(pipefds);

	fclose(source);
	fclose(dest);
	//We now have a file called algo_rewrite.silq, that took the template silq program and turned it into a viable rewritten one for our values.
	if(fork() == 0)
	{
		close(pipefds[0]);
		dup2(pipefds[1], STDOUT_FILENO); // dup stdout of our child program to the write of the parent
		close(pipefds[1]);
		execlp("silq", "silq", "algo_rewrite.slq", "--run", NULL);	
	}

	close(pipefds[1]);
	//We now have everything we need to compute things in C!
	char c;
	while(read(pipefds[0], &c, 1) > 0)
	{
		write(1, &c, 1);
	}

}
