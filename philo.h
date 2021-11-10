/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:01:34 by dwillard          #+#    #+#             */
/*   Updated: 2021/11/08 20:01:36 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_data
{
	int				philo_count;
	int				eat_count;
	int				life_status;
	int				is_dead;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		start_time;
	pthread_mutex_t	writer;
}t_data;

typedef struct s_philosopher
{
	int				name;
	int				eaten;
	uint64_t		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	t_data			*data;
}t_philosopher;

int				ft_atoi(const char *str);

uint64_t		get_time(void);

int				free_that(void *this, void *that);

int				free_philo(t_philosopher ***philo);

int				mutex_destroyer(int index, t_philosopher **philo);

void			create_threads(pthread_t *threads, t_philosopher **philo);

void			print(t_philosopher *philo, char *message);

void			ft_usleep(uint64_t delta_t);

void			*watch(void *args);

void			*dead_announcer(void *args);

t_data			*data_init(int argc, char **argv, t_philosopher **philo);

t_philosopher	*philo_init(int index, t_data *data);

int				threads_init(t_data *data, t_philosopher **philo);

#endif
