#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	//create a proccess, ID, Arrival Time, Burst Time
	int id;
	int at;
	int bt;
} process;

// //https://stackoverflow.com/questions/29248585/c-checking-command-line-argument-is-integer-or-not
// int isNumber(char argv[])
// {
    

//     //checking for negative numbers
//     if (argv[0] == '-')
// 	{
        
//     	for (int i = 1; atoi(argv[i]) != 0; i++)
//     	{
//         //if (number[i] > '9' || number[i] < '0')
//         	if (!isdigit(atoi(argv[i])))
// 			{
//             	return -1;
// 			}
//     	}
// 	}
//     return 1;
// }

void sort_by_bt(process arr_p[],int argc)
{
	// sort struct array by burst time (used in fifo to sort at), Reccomened bubble sort by Nichita Postalachi
	// ----------------- Refrence ---------------------- https://hackr.io/blog/bubble-sort-in-c
	int arr_c = (argc-1)/2;
	process temp;
	for(int i=1;i<=arr_c;++i)
	{
		//store current struct in temp
		temp = arr_p[i];
			
			for(int j=1;j<=(arr_c -i);++j)
			{
				//compare at, skip if at = 0
				if(arr_p[j].bt>arr_p[j+1].bt && arr_p[j].bt!=arr_p[j+1].bt )
				{
				temp = arr_p[j];
				arr_p[j] = arr_p[j+1];
				arr_p[j+1]=temp;
				}
				
			}
					
	}
}
void sort_by_at(process arr_p[],int argc)
{
	int arr_c = (argc-1)/2;
	process temp;
	for(int i=1;i<=arr_c;++i)
	{
		//store current struct in temp
		temp = arr_p[i];
			
			for(int j=1;j<=(arr_c -i);++j)
			{
				//check if array is 
				if(arr_p[j].at>arr_p[j+1].at )
				{
				temp = arr_p[j];
				arr_p[j] = arr_p[j+1];
				arr_p[j+1]=temp;
				}
			}
					
	}

}

//function to print all process
void print_process(process arr_p[],int argc)
{
	printf("\nSuccessfully Added Process\n-----------------------");
	for(int i=1;i<=(argc-1)/2;++i)
	{
		printf("\nProcess P%d\n------------\nAT = %d\nBT = %d\n",arr_p[i].id,arr_p[i].at,arr_p[i].bt);
	}
	printf("\n---------------------");
}

//----------------------------------FIFO ALGORITHIM------------------------------------
void fifo(process arr_p[],int argc)
{
	//intialize for turnaround and average turnaround
	int turn=0;
	double avgturn=0;
	//intialize response time
	int resp=0;
	double avgresp=0;
	// count of array elements
	int arr_c = (argc-1)/2;
	// completion time
	int comptime=0;
	int firstturn=0;
	// Intialize Timeline
	int timeline = 0;
	printf("\n----------------------\nFIFO TIMELINE\n----------------------\n");

	//sort by arrival time
	sort_by_at(arr_p,argc);
	for(int i=1;i<=arr_c;++i)
	{		
		timeline=arr_p[i].at;
		printf("\nT = %d  P%d\n", timeline,arr_p[i].id);
		//get the completion time
		comptime+= arr_p[i].bt;
		//get the average turn around time
		turn = (comptime - arr_p[i].at);
		//add each turn around
		avgturn += turn;
		
		//skip first element when cal Response
		if(arr_p[i].at!= 0)
		{
			// calculate all response times
			firstturn += arr_p[i-1].bt;
			resp = (firstturn - arr_p[i].at);
			avgresp +=resp;
			//printf("\nresponse time= %d-%d = %d\n  Avg = %lf\n",firstturn,arr_p[i].at,resp,avgresp);
		}
	}
	//divide to get average Turn around & Response time;
	avgturn = (avgturn/arr_c);
	avgresp = (avgresp/arr_c);
	printf("\n----------------------\nAverage Turn Around: %lf\nAverage Response Time: %lf\n",avgturn,avgresp);

};

void sjf(process arr_p[],int argc)
{
	//intialize for turnaround and average turnaround
	int turn=0;
	double avgturn=0;
	//intialize response time
	int resp=0;
	double avgresp=0;
	// count of array elements
	int arr_c = (argc-1)/2;
	// completion time
	int comptime=0;
	int firstturn=0;
	// Intialize Timeline
	int timeline = 0;

		printf("\n----------------------\nSJF TIMELINE\n----------------------\n");

	sort_by_bt(arr_p,argc);
	for(int i=1;i<=arr_c;++i)
	{		
		
		printf("\nT = %d  P%d\n", timeline,arr_p[i].id);
		timeline+=arr_p[i].bt;
		//get the completion time
		comptime+= arr_p[i].bt;
		//get the average turn around time
		turn = (comptime - arr_p[i].at);
		//add each turn around
		avgturn += turn;
		
		//skip first element when cal Response
		if(arr_p[i].at!= 0)
		{
			// calculate all response times
			firstturn += arr_p[i-1].bt;
			resp = (firstturn - arr_p[i].at);
			avgresp +=resp;
			//printf("\nresponse time= %d-%d = %d\n  Avg = %lf\n",firstturn,arr_p[i].at,resp,avgresp);
		}
	}
	//divide to get average Turn around & Response time;
	avgturn = (avgturn/arr_c);
	avgresp = (avgresp/arr_c);
	printf("\n----------------------\nAverage Turn Around: %lf\nAverage Response Time: %lf\n",avgturn,avgresp);

}

void rr(process arr_p[],int argc)
{
	//intialize for turnaround and average turnaround
	int turn=0;
	double avgturn=0;
	//intialize response time
	int resp=0;
	double avgresp=0;
	// count of array elements
	int arr_c = (argc-1)/2;
	// completion time
	int comptime=0;
	int firstturn=0;
	// Intialize Timeline
	int timeline = 0;
	int tot_btime = 0;
	int time_q = 5;
		printf("\n----------------------\nRound Robin TIMELINE\n----------------------\n");
	// sort by arrival time
	process temp;
	for(int i=1;i<=arr_c;++i)
	{
		//store current struct in temp
		temp = arr_p[i];
		tot_btime+=arr_p[i].bt;
			
			for(int j=1;j<=(arr_c -i);++j)
			{
				//sort array by at
				if(arr_p[j].at>arr_p[j+1].at )
				{
				temp = arr_p[j];
				arr_p[j] = arr_p[j+1];
				arr_p[j+1]=temp;
				}
			}
					
	}

	printf("\nTime Quantum = %d\n",time_q);

	int count =1;
	while(tot_btime>=0)
	{
		if(count==1)
		{
			printf("\nT = %d  P%d\n", timeline,arr_p[count].id);
		}

	    if(arr_p[count].bt<5)
		{
			//printf("\ntotal burst time = %d\n",tot_btime);
			timeline+=arr_p[count].bt;
			tot_btime-=arr_p[count].bt;
			count++;
			printf("\nT = %d  P%d\n", timeline,arr_p[count].id);
		}
		else
		{
			timeline+=5;
			tot_btime-=5;
			arr_p[count].bt = arr_p[count].bt-5;
			printf("\nT = %d  P%d\n", timeline,arr_p[count].id);
	 		tot_btime-=5;
			timeline+=5;
			printf("\nT = %d  P%d\n", timeline,arr_p[count+1].id);

		}

	}
}

void compare_sch(process arr_p[],int argc)
{
	//intialize for average turnaround
	double avgturn=0;
	//intialize average response time
	double avgresp=0;



	printf("\n--\nFIFO\n--\n Average Turnaround = %f\nAverage Reponse Time = %f\n",avgturn,avgresp);

	printf("\n--\nSJF\n--\nAverage Turnaround = %f\nAverage Reponse Time = %f\n",avgturn,avgresp);
	

}
