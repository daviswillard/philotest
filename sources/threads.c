/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:59:45 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/08 19:59:52 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	eat(t_philosopher *philo)
{
	if (philo->last_eat + philo->data->time_to_die > get_time())
		philo->data->is_dead = philo->name;
	philo->last_eat = get_time();
	print(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->eaten++;
}

static void	forks_action(t_philosopher *philo)
{
	if (philo->name % 2)
	{
		pthread_mutex_lock(&philo->right_fork);
		print(philo, "has taken a fork");
		if (&philo->right_fork == philo->left_fork)
		{
			ft_usleep(philo->data->time_to_die + 20);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print(philo, "has taken a fork");
	}
}

static void	*philosophy(void *args)
{
	t_philosopher	*philo;
	pthread_t		watcher;

	philo = (t_philosopher *)args;
	if ((philo->name % 2))
		ft_usleep(philo->data->time_to_eat);
	pthread_create(&watcher, NULL, watch, philo);
	pthread_detach(watcher);
	while (1)
	{
		forks_action(philo);
		eat(philo);
		if ((philo->data->eat_count >= 0 && philo->eaten
				>= philo->data->eat_count))
			break ;
		print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print(philo, "is thinking");
		if (!philo->data->life_status)
			break ;
	}
	return (NULL);
}

void	create_threads(pthread_t *threads, t_philosopher **philo)
{
	int			index;
	pthread_t	announcer;

	index = 0;
	pthread_create(&announcer, NULL, dead_announcer, philo[0]->data);
	pthread_detach(announcer);
	philo[0]->data->start_time = get_time();
	while (index < philo[0]->data->philo_count)
	{
		pthread_create(&threads[index], NULL, philosophy, philo[index]);
		index++;
		ft_usleep(1);
	}
}
