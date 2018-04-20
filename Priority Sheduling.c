/* wap to implement priority scheduling algo with context switching time. prompt to the user to enter the no.of proccesses
and then enter their priority,burst time and arrival time  also .now whenever OS preempts a process and cpu's control
to some another process of higher priority.Assumes that it takes 2 sec for context switching (dispatcher latency) .form a 
scenario , when we can give the processess are assigned with priority where the lower integer number is higher priority....
and then context switch .. as the process waits of the process increase at rate of one per 2 time units of wait */

#include<iostream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
int main()
{
    int bt[20],p[20],wt[20],tat[20],pr[20],ar[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
    int flag=0;
    cout<<"Enter Total Number of Process:";
    cin>>n;
 
 	if(n<=0)
 	{
 		cout<<"\n\n<<<<<<<<<<<<<<<<<  Invalid Process Number Entered  >>>>>>>>>>>>";
 		exit(0);
	 }
    cout<<"\nEnter Burst Time and Priority and Arrival Time\n";
    for(i=0;i<n;i++)
    {
        cout<<"\nP["<<i+1<<"]\n";
        cout<<"Arrival Time:";
        cin>>ar[i];
		cout<<"Burst Time:";
        cin>>bt[i];
        cout<<"Priority:";
        cin>>pr[i];
        p[i]=i+1;           
        
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
        
		
		temp=ar[i];
        ar[i]=ar[pos];
        ar[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
        
        if(bt[i]<0 || ar[i]<0)
		{
			flag = 1;
		}
        
    }
    
    if(flag==1)
    {
    	printf("\n\n:::  Invalid Time Entered ::: \n");
    	exit(0);
	}
 
    wt[0]=0;            //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;
 
    cout<<"\nProcess\t    Burst Time  \t Arrival Time  \tWaiting Time\tTurnaround Time";
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<ar[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
    }
 
    avg_tat=total/n;     //average turnaround time
    cout<<"\n\nAverage Waiting Time="<<avg_wt;
    cout<<"\nAverage Turnaround Time="<<avg_tat;
 
    return 0; 
}
