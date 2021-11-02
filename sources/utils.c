#include <philo.h>

int	ft_atoi(const char *str)
{
	int	ind;
	int	sgn;
	int	value;

	sgn = 1;
	ind = 0;
	value = 0;
	while (str[ind] == ' ' || (str[ind] >= '\t' && str[ind] <= '\r'))
		ind++;
	if (str[ind] == '-' || str[ind] == '+')
		if (str[ind++] == '-')
			sgn = -1;
	while (str[ind] >= 48 && str[ind] <= 57)
	{
		value *= 10;
		value += (str[ind++] - 48);
	}
	if (sgn == -1)
		value = -value;
	return (value);
}

unsigned	get_time(void)
{
	struct timeval	s_tv;

	gettimeofday(&s_tv, NULL);
	return (s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000);
}

void	print(pthread_mutex_t *writer, int name, char *message)
{
	pthread_mutex_lock(writer);
	printf("philosopher %d %s\n", name, message);
	pthread_mutex_unlock(writer);
}
