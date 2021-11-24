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

int	parse_args(int argc, char **argv)
{
	int	philo_count;

	if (argc > 6 || argc < 5)
		return (-1);
	philo_count = ft_atoi(argv[1]);
	if (philo_count < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (-1);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (-1);
	return (0);
}

void	start(int argc, char **argv)
{
	t_philosopher	**philo;
	pthread_t		*threads;
	t_data			*data;
	int				index;

	philo = malloc(sizeof(t_philosopher **) * ft_atoi(argv[1]));
	threads = malloc(sizeof(pthread_t *) * ft_atoi(argv[1]));
	if (!philo || !threads)
	{
		free_that(philo, threads);
		return ;
	}
	data = data_init(argc, argv, philo);
	index = threads_init(data, philo);
	if (!index && data)
		create_threads(threads, philo);
	index = 0;
	while (data && index < data->philo_count)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
	mutex_destroyer(0, philo);
	free_that(NULL, threads);
}

int	main(int argc, char **argv)
{
	if (parse_args(argc, argv))
		return (write(2, "Param error\n", 12));
	start(argc, argv);
	return (0);
}
