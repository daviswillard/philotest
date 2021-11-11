/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:59:18 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/08 20:02:51 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philosopher	*philo_init(int index, t_data *data)
{
	t_philosopher	*ret;

	if (!data)
		return (NULL);
	ret = malloc(sizeof(t_philosopher));
	if (!ret)
		return (NULL);
	ret->eaten = 0;
	ret->name = index;
	ret->data = data;
	ret->last_eat = 0;
	return (ret);
}

t_data	*data_init(int argc, char **argv, t_philosopher **philo)
{
	t_data	*ret;

	ret = malloc(sizeof(t_data));
	if (!ret)
		return (NULL);
	ret->life_status = 1;
	ret->philo_count = ft_atoi(argv[1]);
	ret->time_to_die = ft_atoi(argv[2]);
	ret->time_to_eat = ft_atoi(argv[3]);
	ret->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ret->eat_count = ft_atoi(argv[5]);
	else
		ret->eat_count = -1;
	ret->meal_done = 0;
	ret->philo = philo;
	pthread_mutex_init(&ret->writer, NULL);
	ret->is_dead = 0;
	return (ret);
}

int	threads_init(t_data *data, t_philosopher **philo)
{
	int	index;

	index = -1;
	while (++index < data->philo_count)
	{
		philo[index] = philo_init(index, data);
		if (!philo[index])
			return (free_philo(&philo));
	}
	index = -1;
	while (++index < data->philo_count)
	{
		if (pthread_mutex_init(&philo[index]->right_fork, NULL))
			return (mutex_destroyer(index, philo));
	}
	index = -1;
	while (++index < data->philo_count)
	{
		if (index == 0)
			philo[index]->left_fork = &philo[data->philo_count - 1]->right_fork;
		else
			philo[index]->left_fork = &philo[index - 1]->right_fork;
	}
	return (0);
}
