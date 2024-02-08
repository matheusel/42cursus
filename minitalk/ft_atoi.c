#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	int	signal;
	int	res;

	signal = 1;
	res = 0;
	while (*nptr == ' ' || (*nptr >= 7 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * signal);
}
