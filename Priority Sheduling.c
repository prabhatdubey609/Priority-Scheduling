#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int pr[1000],bt[1000],wt[1000],tt[1000],at[1000],start[1000];
float pri[1000];

void getValue(int n)
{
	int i;
	for (i=0;i<n;i++)
	{
		pr[i]=i+1;
		printf("burst time of process %d : ",i+1);
		scanf("%d",&bt[i]);
		printf("priority of process %d : ",i+1);
		scanf("%g",&pri[i]);
		printf("arrival time of process %d : ",i+1);
		scanf("%d",&at[i]);
		printf("\n");
	}

}


void sortValue(int n)
{
	int i,p,j,g,b=0,m,k=1,count=0,s;
	float t;
	start[0]=0;
	for (i=0;i<n;i++)
	{
		p=i;
		for (j=i+1;j<n;j++)
		{
			if(at[j]==at[p])
			{
				if(pri[j]<pri[p])
				p=j;
			}
			else if(at[j]<at[p])
			{
				p=j;
			}
		}
	t=bt[i];
	bt[i]=bt[p];
	bt[p]=(int)t;

	t=pr[i];
	pr[i]=pr[p];
	pr[p]=(int)t;
	t=pri[i];
	pri[i]=pri[p];
	pri[p]=t;
	t=at[i];
	at[i]=at[p];
	at[p]=(int)t;
	count=count+1;
	for(g=1;g<n;g++) //increase the priority
	{
		int newbt=0;
		for(s=0;s<count;s++)
		{
			newbt = newbt + bt[s];
		}
		pri[g]=( 1+(float)(newbt/bt[g]) );
	}
	}
}


void calcWT(int n)
{
	int i,j,add=0;
	wt[0]=0;
	for (i=1;i<n;i++)
	{
		add=add+bt[i-1];
		wt[i]=add-at[i];
	}
}


void calcTT(int n)
{
	int i,tat=0;
	for(i=0;i<n;i++)
	{
	tat=tat+bt[i];
	tt[i]=tat-at[i];
	}
}


float calcAWT(int n)
{

	int i,sum=0;
	for(i=0;i<n;i++) //average waiting time
	{
	sum=sum+wt[i];
	}
	float avgwt=(float)sum/n;
	return avgwt;
}


float calcATT(int n)
{
	int i,sum=0;
	for(i=1;i<n;i++) //average turn around time
	{
	sum=sum+tt[i];
	}
	float avgtt=(float)sum/n;
	return avgtt;
}


void display(float awt,float att,int n)
{
	int i;
	printf("\nGantt Chart : \n\n");
	for(i=0;i<n;i++)
	{
		printf("| P %d ",pr[i]);
	}
	printf("|\n");
	printf("\nProcess\t\t Priority\t\t Burst Time\t\tArrival Time\t\tWaiting Time\t\tTurnaroundTime\n");
	for(i=0;i<n;i++)
	{
		printf("\nProcess %d\t\t%g\t\t\t%d\t\t\t%d\t\t\t%d\t\t%d",pr[i],pri[i],bt[i],at[i],wt[i],tt[i]);
	}
	printf("\n\nAverage waiting time : %g",awt);
	printf("\nAverage turn around time : %g",att);
	printf("\n\n");
}

void descp()
{
	printf("\nThis program is a scheduling approach which is non pre-emptive priority scheduling.\n");
	printf("The priority of each job is dependent on its estimated run time and amount of time it has spent waiting.");
	printf("\nJobs gain higher priority the longer they wait, which prevents indefinite postponement.\n");
	printf("The jobs that have spent a long time waiting compete against those estimated to have short run times.");
	printf("\nThe priority can be computed as : \n\n");

	printf("Priority = 1+ Waiting time / Estimated run time\n\n");
}


void guide()
{
	printf("\n");
	printf("1. Select 1 in menu for process scheduling.\n");
	printf("2. Enter total number of process.\n");
	printf("3. Enter the respective details related to process.\n");
	printf("4. Get the complete scheduled list of processes.\n\n");
}

int main()
{
	int x,y,n;
	printf("\n\t\t\t\t\t\t-------------SHORTEST JOB FIRST (NON PREEMPTIVE)-------------\n\n");
	printf("\n\t\t\t\t\t\t\t-------------With Process Priorities-------------\n\n");
	do{
		printf("\t*****MENU*****\n");
		printf("\nSelect any one : \n\n");
		printf("1. Process Scheduling \n\n");
		printf("2. Description \n\n");-
		printf("3. User Guide \n\n");
		printf("4. Exit \n\n");
		scanf("%d",&y);
	
		switch(y)
		{
			case 1 : printf("enter the total number of processes : ");
				scanf("%d",&n);
				printf("\nenter the burst time, priorities and arrival time of processes : \n\n");
				getValue(n);
				sortValue(n);
				calcWT(n);
				calcTT(n);
				float awt=calcAWT(n);
				float att=calcATT(n);
				display(awt,att,n);
				break;

			case 2 : descp();
				break;


			case 3 : guide();
				break;

			case 4 : exit(0);
				break;

			default : printf("Sorry... Invalid Choice \n");
		}
		printf("\nPress 1 to repeat : ");
		scanf("%d",&x);
		printf("\n\n");
	}while (x==1);
}
