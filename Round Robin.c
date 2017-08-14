#include<stdio.h>
#define TIME_SLICE 2

struct Process
  {
    int id;
    int arrival_time;
    int burst_time;
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

    return(p1->burst_time - p2->burst_time);

  } else {
     return(p1->arrival_time - p2->arrival_time);
  }

}



main(int argc, char *argv[])
{
  

  struct Process processes[50];

  char buff[255];

  int i,j;


  float avg_tat = 0.0, avg_wt = 0.0;

   FILE *fp; 
   fp = fopen(argv[1], "r");
   int process_count = 0;

   fscanf(fp,"%s",buff);
    
   while(fscanf(fp, "%d,%d,%d", &processes[process_count].id,
          &processes[process_count].arrival_time, &processes[process_count].burst_time)!=EOF)
   {  
      processes[process_count].remaining_burst_time = processes[process_count].burst_time;
      processes[process_count].completed_time=9999;
      process_count++;
   }  

    
   qsort(processes, process_count, sizeof(struct Process), compare_int);

   printf("\n Order of Execution of Process :\n");



   int current_time = processes[0].arrival_time;
   int previous_time_stamp = processes[0].arrival_time;

   int completed  =1;
   int job_queue[100];
   job_queue[0] = 0;
  
   int index= 0;
   int current_item_index=0;


   while(completed)
   {

        previous_time_stamp = current_time;

        i = job_queue[current_item_index];

        printf(" %d",processes[i].id);

    
        if(processes[i].remaining_burst_time >= TIME_SLICE && processes[i].remaining_burst_time != 0)
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

        
        


        for(j=0;j<process_count;j++)
      {
        if(processes[j].arrival_time <= current_time)
        {
          if(processes[j].arrival_time > previous_time_stamp)
          {
            if(processes[j].remaining_burst_time != 0 && processes[j].id != processes[i].id)
            {
              index++;
              job_queue[index]=j;
              
            }
          }
          
        }
      } 

      if(processes[i].completed_time == 9999)
      {
        index++;
        job_queue[index]= i;
        
      }

      current_item_index++;



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

  

    for(i=0;i<process_count;i++)
    {
      avg_tat = avg_tat + processes[i].turn_around_time;
      avg_wt = avg_wt + processes[i].waiting_time;
    }


    avg_tat = avg_tat / process_count;
    avg_wt = avg_wt / process_count;

    printf("\n\n");

   for(i=0;i<process_count;i++)
    {
      printf(" Turn around time for Process:%d is %d\n",processes[i].id,processes[i].turn_around_time);
      printf(" Waiting time for Process:%d is %d\n\n",processes[i].id,processes[i].waiting_time);
    }

    printf(" Average Turn around time is %.3f\n",avg_tat);
    printf(" Average Waiting time is %.3f\n\n",avg_wt);

    fclose(fp);   
}
