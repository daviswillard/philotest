#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philosopher
{
	int				name;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}t_philosopher;

#endif
