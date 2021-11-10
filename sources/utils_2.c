/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:42:00 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/10 18:42:03 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	free_philo(t_philosopher ***philo)
{
	int		index;
	t_data	*data;

	data = (*philo)[0]->data;
	index = 0;
	if (*philo)
	{
		while (index < data->philo_count)
		{
			free((*philo)[index]);
			index++;
		}
		free(*philo);
	}
	return (-1);
}

int	mutex_destroyer(int index, t_philosopher **philo)
{
	int	counter;

	counter = 0;
	if (!index)
	{
		while (index < philo[0]->data->philo_count)
		{
			pthread_mutex_destroy(&philo[index]->right_fork);
			index++;
		}
		pthread_mutex_destroy(philo[0]->left_fork);
	}
	else
	{
		while (counter < index)
			pthread_mutex_destroy(&philo[counter++]->right_fork);
		free_philo(&philo);
		return (-1);
	}
	free_philo(&philo);
	return (0);
}
