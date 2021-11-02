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
	unsigned		time_to_sleep;
	unsigned		time_to_die;
	unsigned		time_to_eat;
	unsigned		start_time;
	pthread_mutex_t	*writer;
}t_data;

typedef struct s_philosopher
{
	int				name;
	int				eaten;
	unsigned		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	t_data			*data;
}t_philosopher;

int				ft_atoi(const char *str);

unsigned		get_time(void);

void			print(pthread_mutex_t *writer, int name, char *message);

t_data			*data_init(int argc, char **argv);

t_philosopher	*philo_init(int index, t_data *data);

#endif
