#include<stdio.h>
#define TIME_SLICE 1

struct Process
	{
		int id;
		int arrival_time;
		int burst_time;
		int priority;
		int remaining_burst_time;
		int completed_time;
		int waiting_time;
		int turn_around_time;
};

int compare_int (const void *a, const void *b)
{
  struct Process *p1 = (struct Process *)a;
  struct Process *p2 = (struct Process *)b;
  if(p1->arrival_time - p2->arrival_time == 0)
  {

  	return(p2->priority - p1->priority);

  } else {
  	 return(p1->arrival_time - p2->arrival_time);
  }

}



int prioritized_job(int process_count, struct Process processes[50], int current_time)
{
	int i, highest = 9999, highest_process_id;

	for(i=0;i<process_count;i++)
	{
		if(processes[i].arrival_time <= current_time)
		{
			if(processes[i].priority < highest && processes[i].remaining_burst_time != 0)
			{
				highest = processes[i].priority;
				highest_process_id = i;
			}
		}
	}

	return highest	_process_id;
}




main(int argc, char *argv[])
{
	

	struct Process processes[50];

  	char buff[255];

	int i;


	float avg_tat = 0.0, avg_wt = 0.0;

   FILE *fp; 
   fp = fopen(argv[1], "r");
   int process_count = 0;

   fscanf(fp,"%s",buff);

    
   while(fscanf(fp, "%d,%d,%d,%d", &processes[process_count].id,
   				&processes[process_count].arrival_time, &processes[process_count].burst_time, &processes[process_count].priority)!=EOF)
   {  
   		processes[process_count].remaining_burst_time = processes[process_count].burst_time;
   		process_count++;
   }  

  	
   qsort(processes, process_count, sizeof(struct Process), compare_int);

   printf(" Order of Execution of Process :\n");

   int current_time = processes[0].arrival_time;
   int completed=1;


   while(completed)
   {


   			i = prioritized_job(process_count,processes,current_time);

   			printf(" %d",processes[i].id);

   	
   			if(processes[i].remaining_burst_time >= TIME_SLICE)
   			{	
   				current_time = current_time + TIME_SLICE;

   				if(processes[i].remaining_burst_time == TIME_SLICE)
   					processes[i].completed_time = current_time;

   				processes[i].remaining_burst_time = processes[i].remaining_burst_time - TIME_SLICE;
   				
   			}	
   			else{

   				current_time = current_time + processes[i].remaining_burst_time;
   				processes[i].remaining_burst_time=0;
   				processes[i].completed_time = current_time;
   			}

   		



   			completed = 0;


    		for(i=0;i < process_count;i++)
   			{
   				if(processes[i].remaining_burst_time != 0)
   				{
   					completed = 1;
   					break;
   				}
   			}


   }




   	for(i=0;i < process_count;i++)
   	{

   		processes[i].turn_around_time = processes[i].completed_time - processes[i].arrival_time;
   		processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;

   	}	

  

   
   printf("\n\n");

    for(i=0;i<process_count;i++)
    {
    	avg_tat = avg_tat + processes[i].turn_around_time;
    	avg_wt = avg_wt + processes[i].waiting_time;
    }


    avg_tat = avg_tat / process_count;
    avg_wt = avg_wt / process_count;

    

   for(i=0;i<process_count;i++)
    {
    	printf(" Turn around time for Process:%d is %d\n",processes[i].id,processes[i].turn_around_time);
   		printf(" Waiting time for Process:%d is %d\n\n",processes[i].id,processes[i].waiting_time);
    }

   	printf(" Average Turn around time is %.3f\n",avg_tat);
    printf(" Average Waiting time is %.3f\n\n",avg_wt);

   	fclose(fp);   
}
