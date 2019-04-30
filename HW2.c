#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(void)
{
	FILE *fp;
	char *line = NULL;
	char *seg;
	size_t len = 0;
	ssize_t read;
	int id[100], arrival[100], duration[100], start[100], remain[100], turnaround[100], service[100], response[100], wait[100];
	int entered[100]={0};
	int seg_counter = 0;
	int job_index = 0;
	int id_holder, arrival_holder, duration_holder, response_holder, turnaround_holder, service_holder;
	fp = fopen("jobs.dat", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	//min character for a job (3 for jobs, 2 for tab or space, 1 for new line character)
	while ((read = getline(&line, &len, fp)) >= 6) 
	{		
		seg = strtok (line," ,.-\t");
		while (seg != NULL)
		{
			if(seg_counter == 0)
				id[job_index] = atoi(seg);
			else if(seg_counter == 1)
				arrival[job_index] = atoi(seg);
			else if(seg_counter == 2)
				duration[job_index] = atoi(seg);
			seg = strtok (NULL, " ,.-\t");		
			seg_counter++;
		}
		seg_counter = 0;
		job_index++;
	}
	printf("Information from jobs.dat\nJOB_ID|ARRIVAL_TIME|DURATION\n");
	for(int i =0; i<job_index; i++)
	{
		printf("%i\t%is\t%is\n",id[i],arrival[i],duration[i]);
	}
	
	//FIFO code begin
	//sort by arrival times for FIFO
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (arrival[j] > arrival[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
			}
                }
        }

	//get wait times for processes
	wait[0]=0;
	service[0]=arrival[0];
	for(int i=1;i<job_index;i++)
	{
		service[i]=service[i-1]+duration[i-1];
		wait[i]=service[i]-arrival[i];
		if(wait[i]<0)
			wait[i]=0;
	}

	for(int i=0;i<job_index;i++)
	{
		turnaround[i]=duration[i]+wait[i];
	}

	for(int i=0;i<job_index;i++)
	{
		response[i]=service[i]-arrival[i];
	}

	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (id[j] > id[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
				service_holder = service[j];
				turnaround_holder = turnaround[j];
				response_holder = response[j];
				service[j] = service[j+1];
                    		turnaround[j] = turnaround[j+1];
				response[j] = response[j+1];
				service[j+1] = service_holder;
				turnaround[j+1] = turnaround_holder;
				response[j+1] = response_holder;
			}
                }
        }

	printf("\nFIFO\nJOB|START TIME|END TIME|TURNAROUND|RESPONSE\n");
	for(int i =0; i<job_index; i++)
	{
		printf("%i\t%is\t%is\t%is\t%is\n",id[i],service[i],turnaround[i]+arrival[i],turnaround[i],response[i]);
	}
	printf("\n");
	//FIFO code end

	//SJF code begin
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if ((arrival[j] == arrival[j+1] && duration [j] > duration[j+1])||arrival[j]>arrival[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
			}
                }
        }

	wait[0]=0;
	service[0]=arrival[0];
	for(int i=1;i<job_index;i++)
	{
		service[i]=service[i-1]+duration[i-1];
		wait[i]=service[i]-arrival[i];
		if(wait[i]<0)
			wait[i]=0;
	}

	for(int i=0;i<job_index;i++)
	{
		turnaround[i]=duration[i]+wait[i];
	}

	for(int i=0;i<job_index;i++)
	{
		response[i]=service[i]-arrival[i];
	}
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (id[j] > id[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
				service_holder = service[j];
				turnaround_holder = turnaround[j];
				response_holder = response[j];
				service[j] = service[j+1];
                    		turnaround[j] = turnaround[j+1];
				response[j] = response[j+1];
				service[j+1] = service_holder;
				turnaround[j+1] = turnaround_holder;
				response[j+1] = response_holder;
			}
                }
        }
	printf("SJF\nJOB|START TIME|END TIME|TURNAROUND|RESPONSE\n");
	for(int i =0; i<job_index; i++)
	{
		printf("%i\t%is\t%is\t%is\t%is\n",id[i],service[i],turnaround[i]+arrival[i],turnaround[i],response[i]);
	}
	printf("\n");
	//end of SJF code

	//BJF code begin
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if ((arrival[j] == arrival[j+1] && duration [j] < duration[j+1])||arrival[j]>arrival[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
			}
                }
        }

	wait[0]=0;
	service[0]=arrival[0];
	for(int i=1;i<job_index;i++)
	{
		service[i]=service[i-1]+duration[i-1];
		wait[i]=service[i]-arrival[i];
		if(wait[i]<0)
			wait[i]=0;
	}

	for(int i=0;i<job_index;i++)
	{
		turnaround[i]=duration[i]+wait[i];
	}

	for(int i=0;i<job_index;i++)
	{
		response[i]=service[i]-arrival[i];
	}
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (id[j] > id[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
				service_holder = service[j];
				turnaround_holder = turnaround[j];
				response_holder = response[j];
				service[j] = service[j+1];
                    		turnaround[j] = turnaround[j+1];
				response[j] = response[j+1];
				service[j+1] = service_holder;
				turnaround[j+1] = turnaround_holder;
				response[j+1] = response_holder;
			}
                }
        }
	printf("BJF\nJOB|START TIME|END TIME|TURNAROUND|RESPONSE\n");
	for(int i =0; i<job_index; i++)
	{
		printf("%i\t%is\t%is\t%is\t%is\n",id[i],service[i],turnaround[i]+arrival[i],turnaround[i],response[i]);
	}
	printf("\n");
	//BJF code end

	//STCF code begin
	int completed = 0;
	int time = 0;
	int shortest_index = 0;
	int minimal = 1000000;
	int index = 0;
	bool isSwitched;
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (arrival[j] == arrival[j+1] && duration [j] > duration[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
			}
                }
        }	
	for(int i =0; i<job_index;i++)
		remain[i] = duration[i];
	
	while(completed!=job_index)
	{
		for(int i=0;i<job_index;i++)
		{
			if(arrival[i] <= time && remain[i] < minimal && remain[i] > 0)
			{
				minimal = remain[i];
				shortest_index = i;
				isSwitched = true;
			}
		}

		if(isSwitched == false)
		{
			time++;
		}
		else
		{
			if(entered[shortest_index]==0)
			{
				response[shortest_index] = time-arrival[shortest_index];
				service[shortest_index] = time;
				entered[shortest_index]=1;
			}	
			remain[shortest_index]--;
			minimal = remain[shortest_index];
			if(minimal == 0)
				minimal = 1000000;
			if(remain[shortest_index] == 0)
			{
				completed++;
				isSwitched = false;
				wait[shortest_index] = time+1-duration[shortest_index]-arrival[shortest_index];
				if(wait[shortest_index]<0)
					wait[shortest_index]=0;
			}
			time++;
		}
	}
	
	for(int i=0;i<job_index;i++)
	{
		turnaround[i]=duration[i]+wait[i];
	}
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (id[j] > id[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
				service_holder = service[j];
				turnaround_holder = turnaround[j];
				response_holder = response[j];
				service[j] = service[j+1];
                    		turnaround[j] = turnaround[j+1];
				response[j] = response[j+1];
				service[j+1] = service_holder;
				turnaround[j+1] = turnaround_holder;
				response[j+1] = response_holder;
			}
                }
        }
	printf("STCF\nJOB|START TIME|END TIME|TURNAROUND|RESPONSE\n");
	for(int i =0; i<job_index; i++)
	{
		printf("%i\t%is\t%is\t%is\t%is\n",id[i],service[i],turnaround[i]+arrival[i],turnaround[i],response[i]);
	}
	printf("\n");
	//STCF code end


	//RR code begin
	time=0;
	isSwitched=false;
	completed=0;
	int shortest=0;
	int slice = 1;
	bool isJobsDone=false;
	bool didRun=false;

	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (arrival[j] == arrival[j+1] && duration [j] > duration[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
			}
                }
        }	
	for(int i =0; i<job_index;i++){
		remain[i] = duration[i];
		entered[i]=0;
	}
	while(1)
	{
		isJobsDone = true;
		for(int i=0;i<job_index;i++)
		{		
			if(arrival[i]<time)
				didRun=true;
			if(remain[i]>0&&arrival[i]<=time)
			{

				if(entered[i]==0)
				{
					response[i] = time-arrival[i];
					service[i] = time;
					entered[i]=1;
				}	
				if(remain[i]>slice)
				{
					time=time+slice;
					remain[i]=remain[i]-slice;
				}
				else if(remain[i]<=slice)
				{
					time=time+remain[i];
					wait[i]=time-duration[i]-arrival[i];
					if(wait[i]<0)
						wait[i]=0;
					remain[i]=0;
					completed++;
				}
			}
			if(completed!=job_index)
			{
				isJobsDone = false;
			}
			else
				isJobsDone = true;
		}
		if(didRun==false)
			time=arrival[0];
		if(isJobsDone==true)
			break;
	}
	for(int i=0;i<job_index;i++)
	{
		turnaround[i]=duration[i]+wait[i];
	}
	
	for (int i=0; i<job_index-1; i++) 
        {
		for (int j=0; j <job_index-i-1; j++)
		{
                	if (id[j] > id[j+1]) 
                	{
				id_holder =  id[j];
				arrival_holder =  arrival[j];
				duration_holder =  duration[j];
                    		id[j] = id[j+1];
                    		arrival[j] = arrival[j+1];
                    		duration[j] = duration[j+1];
				id[j+1] = id_holder;
				arrival[j+1] = arrival_holder;
				duration[j+1] = duration_holder;
				service_holder = service[j];
				turnaround_holder = turnaround[j];
				response_holder = response[j];
				service[j] = service[j+1];
                    		turnaround[j] = turnaround[j+1];
				response[j] = response[j+1];
				service[j+1] = service_holder;
				turnaround[j+1] = turnaround_holder;
				response[j+1] = response_holder;
			}
                }
        }	


	printf("RR\nJOB|START TIME|END TIME|TURNAROUND|RESPONSE\n");
	for(int i =0; i<job_index; i++)
	{	
		printf("%i\t%is\t%is\t%is\t%is\n",id[i],service[i],turnaround[i]+arrival[i],turnaround[i],response[i]);
	}
	//RR code end
	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}


