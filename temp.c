#include <time.h>
#include<stdio.h>
main(){
     
     clock_t start, end;
     double cpu_time_used;
     
     start = clock();
    // ... /* Do the work. */
	int i=0;
while(i<20200000)
{
i++;
}    
 end = clock();
     cpu_time_used = ((double) (end - start)) ;
printf("%f\n",cpu_time_used);
}
