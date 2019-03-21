#include <stdio.h>
#include <float.h>

int main(void)
{
	int i, n;
	double candidate, max = -DBL_MAX;
	
	printf("How many numbers do you wish to enter? ");
	scanf("%d", &n);
	
	printf("Enter %d real numbers:", n);
	for(i = 0; i < n; i++)
	{
		scanf("%lf", &candidate);
		if(candidate > max)
		{
			max = candidate;
		}
	}
	printf("Maximum value: %lf", max);

	return(0);
}
