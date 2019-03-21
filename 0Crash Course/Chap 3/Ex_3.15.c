#include <stdio.h>

int main(void)
{
	int count, n;
	int candidate, max = 0;
	
	printf("How many INTEGERS do you wish to enter? ");
	scanf("%d", &n);
	
	printf("Enter %d positive integers:", n);
	while(count < n)
	{
		scanf("%d", &candidate);
		if(candidate%2 != 0)
		{
		  if(candidate > max)
		  {
			  max = candidate;
			  count++;
		  }
		  else
		  {
		    count++;
		  }
		}
		else
		{
		  printf("I hate even numbers! Enter an ODD integer instead!");
		}
	}
	printf("Maximum value: %d", max);

	return(0);
}
