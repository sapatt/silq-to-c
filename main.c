#include <unistd.h>
#include <stdio.h>


void startChanging(int argc, char** argv, FILE* source, FILE* dest)
{
	char c;
	char c2;
	while(c = fgetc(source) != NULL)
	{
		//Overwrite this part with our data now
		if(c == 'g')
		{
			c2 = fgetc(source);
		
			switch(c2)
			{
				case 'S':
			
				break;
				case 'N':


				break;
				case 'Z':

				break;
				case 'Q':

			break;
			case 'R':

			break;
		}
	}
}

int main(int argc, char** argv)
{
	//First, we create a copy of the program
	FILE* source, dest;
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
	char* dest_file = "algo_rewrite.silq";
	dest = fopen(dest_file, "w");
	if(dest == NULL)
	{
		fclose(dest_file);
		fclose(source);
		return -1;
	}

	startChanging(argc, argv, source, dest);

}
