/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:59:57 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/08 19:59:58 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *str)
{
	int	ind;
	int	value;

	ind = 0;
	value = 0;
	if ((str[ind] > '9' || str[ind] < '0') && str[ind] != '\0')
		return (-1);
	while (str[ind] >= '0' && str[ind] <= '9')
	{
		value *= 10;
		value += (str[ind++] - '0');
	}
	if ((str[ind] > '9' || str[ind] < '0') && str[ind] != '\0')
		return (-1);
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
		usleep(100);
}

void	print(t_philosopher *philo, char *message)
{
	int				name;
	pthread_mutex_t	*writer;
	uint64_t		time;

	time = get_time() - philo->data->start_time;
	writer = &philo->data->writer;
	name = philo->name;
	if (!philo->data->life_status)
		return ;
	pthread_mutex_lock(writer);
	printf("%6lu philosopher %d %s\n", time, name, message);
	pthread_mutex_unlock(writer);
}

int	free_that(void *this, void *that)
{
	if (!this)
		;
	else
		free(this);
	if (!that)
		;
	else
		free(that);
	return (0);
}
