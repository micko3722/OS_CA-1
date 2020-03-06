#include "process.h"

int main(int argc,char* argv[])
{
	// Intilaize Input String
	char input[11];
	// char to populate  if input error occurs
	char error[15] = " ";
	//bool to check at & bt > or = 0, true =0,false = -1
	int even = 0;
	
	//check if arguments are not null, (argc-1 it will pass enter)
	if((argc-1)!=0 && ((argc-1) %2)==0)
	{
		//auto Increment ID's, -------REFRENCE----- Storing Sruct in Array, https://stackoverflow.com/questions/10468128/how-do-you-make-an-array-of-structs-in-c				 		 
		// store struct arrray on heap, so it can be used in other functions in process.h
		process *arr_p = malloc(argc * sizeof(arr_p));
		int count = 0;
		for(int i=1;i<=argc-1;i+=2)
		{
			//check if at & bt are correct
			if(atoi(argv[i])>=0 && atoi(argv[i+1])>0)
			{		  
		  		count++;
				//add to struct array
				arr_p[count].id = count;
				arr_p[count].at = atoi(argv[i]);
				arr_p[count].bt = atoi(argv[i+1]);
			}
			else
			{
				//set to false 
			 	even = 1;
				//error will be printed with message
				strncpy(error,"AT!>0 & BT!>0",15);
				
			}
			
		}
		
		if(even!=1){
			print_process(arr_p,argc);
			do
			{ 
				printf("\n---------------------\nCommand List\n---------------------\n1. fifo -- FIFO scheduling \n2. sjf -- SJF scheduling\n4. stcf-- STCF\n3. rr -- Round Robin(Not working)\n4. compare -- compare scheduling\n5. quit -- Exit program\n---------------------\n");		
				//Take in User input
				printf("\nPlease Enter Input \n> ");
				// to lower converts to lowercase, avoid if statements checking uppercase
				fgets(input,11,stdin);
				//replace enter at the end with '\0' for str compare
				input[(strlen(input)-1)] = '\0';

					// -------Menu System------------
					if(strcmp(input,"fifo")==0)
					{
						fifo(arr_p,argc);
					}
					else if(strcmp(input,"sjf")==0)
					{
						sjf(arr_p,argc);
					}
					else if(strcmp(input,"stcf")==0)
					{
						stcf(arr_p,argc);
					}
					else if(strcmp(input,"rr")==0)
					{
						rr(arr_p,argc);
					}
					else if(strcmp(input,"compare")==0)
					{
						compare_sch(arr_p,argc);
					}
					else if(strcmp(input,"quit")==0)
					{
						// release memory from heap
						free(arr_p);	
						printf("\nExiting Program...Good-bye\n");
					}
					else
					{
					// output error if command is not recognised
					printf("\n---ERROR---\nInvalid Command\n");
					}

			}	
			while(strcmp(input,"quit")!=0);
		}
	else
		{
			printf("\nInput Data is not correct: %s\nNumber of Arguements passed = %d\n ",error,argc-1);
		}
	
	}
	return 0;
}



