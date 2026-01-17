#include <limits.h>
#include <stdio.h>

int	main(void)
{
	long	number;

	number = INT_MAX;
	while (number >= INT_MIN)
	{
		printf("%li ", number);
		number--;
	}
	return (0);
}
