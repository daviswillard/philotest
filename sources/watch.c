#include <philo.h>

void	*watch(void *args)
{
	t_philosopher	*arg;

	arg = (t_philosopher *)args;
	arg->last_eat = arg->data->start_time;
	while (1)
	{
		if (!arg->data->life_status)
			return (NULL);
		if (get_time() > arg->last_eat + arg->data->time_to_die)
		{
			arg->is_dead = 1;
			arg->data->life_status = 0;
			printf("%6d\n", arg->name);
			printf("%6llu time he ate last\n", arg->last_eat -
			arg->data->start_time);
			return (NULL);
		}
	}
}

void	*dead_announcer(void *args)
{
	t_philosopher	**philos;
	u_int64_t		time;
	t_data			*data;
	int				name;

	data = (t_data *)args;
	philos = (t_philosopher **)data->philos;
	name = 0;
	while (1)
	{
		if (!data->life_status)
		{
			while (!philos[name]->is_dead)
				name++;
			time = get_time() - data->start_time;
			printf("%6llu philosopher %d is dead\n", time, philos[name]->name);
			break ;
		}
	}
	return (NULL);
}