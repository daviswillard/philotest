/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:00:01 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/08 20:00:03 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (arg->data->eat_count >= 0 && arg->eaten >= arg->data->eat_count)
			return (NULL);
		if (get_time() > arg->last_eat + arg->data->time_to_die)
		{
			arg->data->life_status = 0;
			arg->data->is_dead = arg->name;
			return (NULL);
		}
		ft_usleep(5);
	}
}

static int	check_end(t_data *data)
{
	int				index;
	int				counter;
	t_philosopher	**philos;

	index = 0;
	counter = 0;
	philos = (t_philosopher **)data->philo;
	while (index < data->philo_count)
	{
		if (philos[index]->eaten >= data->eat_count)
			counter++;
		index++;
	}
	if (counter == index)
	{
		data->meal_done = 1;
		pthread_mutex_lock(&data->writer);
		return (1);
	}
	return (0);
}

void	*dead_announcer(void *args)
{
	u_int64_t		time;
	t_data			*data;

	data = (t_data *)args;
	while (1)
	{
		if (data->eat_count >= 0)
			if (check_end(data))
				return (NULL);
		if (!data->life_status)
		{
			time = get_time() - data->start_time;
			ft_usleep(4);
			printf("%6llu philosopher %d is dead\n", time, data->is_dead);
			break ;
		}
		ft_usleep(2);
	}
	return (NULL);
}
