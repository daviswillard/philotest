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

uint64_t	get_time(void)
{
	struct timeval	s_tv;

	gettimeofday(&s_tv, NULL);
	return (s_tv.tv_sec * 1000 + s_tv.tv_usec / 1000);
}

void	ft_usleep(uint64_t delta_t)
{
	unsigned long long	result;

	result = get_time() + delta_t;
	while (get_time() < result)
		usleep(1);
}

void	print(t_philosopher *philo, char *message)
{
	static int		dying_message = 0;
	pthread_mutex_t	*writer;
	int				name;

	if (philo->is_dead && !dying_message)
	{
		printf("philosopher %d is dead\n", philo->name);
		dying_message = 1;
	}
	writer = philo->data->writer;
	name = philo->name;
	if (philo->data->life_status)
		return ;
	pthread_mutex_lock(writer);
	printf("philosopher %d %s\n", name, message);
	pthread_mutex_unlock(writer);
}
