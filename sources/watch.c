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
		if (get_time() > arg->last_eat + arg->data->time_to_die)
		{
			arg->data->is_dead = arg->name;
			arg->data->life_status = 0;
			ft_usleep(5);
			printf("%6llu time he ate last\n", arg->last_eat
				- arg->data->start_time);
			return (NULL);
		}
		ft_usleep(5);
	}
}

void	*dead_announcer(void *args)
{
	u_int64_t		time;
	t_data			*data;

	data = (t_data *)args;
	while (1)
	{
		if (!data->life_status)
		{
			time = get_time() - data->start_time;
			printf("%6llu philosopher %d is dead\n", time, data->is_dead);
			break ;
		}
		ft_usleep(2);
	}
	return (NULL);
}
