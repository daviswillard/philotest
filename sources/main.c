/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:59:39 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/08 20:00:13 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_philosopher	**philo;
	pthread_t		*threads;
	t_data			*data;
	int				index;

	philo = malloc(sizeof(t_philosopher **) * ft_atoi(argv[1]));
	threads = malloc(sizeof(pthread_t *) * ft_atoi(argv[1]));
	if (!philo | !threads)
		return (1);
	data = data_init(argc, argv, philo);
	for (index = 0; index < data->philo_count; index++)
		philo[index] = philo_init(index, data);
	for (index = 0; index < data->philo_count; index++)
		pthread_mutex_init(&philo[index]->right_fork, NULL);
	for (index = 0; index < data->philo_count; index++)
		if (index == 0)
			philo[index]->left_fork = &philo[data->philo_count - 1]->right_fork;
		else
			philo[index]->left_fork = &philo[index - 1]->right_fork;
	create_threads(threads, philo);
	for (index = 0; index < data->philo_count; index++)
		pthread_join(threads[index], NULL);
	return (0);
}
