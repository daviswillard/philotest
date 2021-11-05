#include <philo.h>

void	*watch(void *args)
{
	t_philosopher	*arg;
	uint64_t		start;

	arg = (t_philosopher *)args;
	start = arg->data->start_time;
	if (!arg->last_eat)
		while (!arg->last_eat || arg->data->life_status)
			if (get_time() + start > start + arg->data->time_to_die)
			{
				arg->is_dead = 1;
				arg->data->life_status = 0;
				return (NULL);
			}
	while (arg->data->life_status)
	{
		if (arg->last_eat + arg->data->time_to_die < get_time())
		{
			arg->is_dead = 1;
			arg->data->life_status = 0;
			return (NULL);
		}
	}
	return ((void*)1);
}
