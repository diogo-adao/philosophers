#include "../philo.h"

unsigned int	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_usleep(unsigned int usec)
{
	unsigned int	before;
	unsigned int	after;

	before = get_current_time();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = get_current_time();
	}
	return (0);
}
