#include <philo.h>

pthread_mutex_t writer = PTHREAD_MUTEX_INITIALIZER;

void	eat(t_philosopher *philo)
{
	printf("philosopher %d is eating\n", philo->name);
}

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&writer);
	printf("philosopher %d has taken right fork\n", philo->name);
	pthread_mutex_unlock(&writer);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&writer);
	printf("philosopher %d has taken left fork\n", philo->name);
	eat(philo);
	pthread_mutex_unlock(&writer);
	usleep(200 * 1000);
}

void	*philosophy(void *args)
{
	t_philosopher *philo;

	philo = (t_philosopher *)args;
	take_forks(philo);
}

void	create_threads(pthread_t *threads, t_philosopher *philo)
{
	int	index;

	index = 0;
	while (index < 4)
	{
		if (!(index % 2))
			;
		else
			usleep(400 * 1000);
		pthread_create(&threads[index], NULL, philosophy, &philo[index]);
		index++;
	}
}

int main(void)
{
	t_philosopher	philo[4];
	int				index;
	pthread_t		threads[4];

	index = 0;
	while (index < 4)
	{
		pthread_mutex_init(philo[index].right_fork, NULL);
		index++;
	}
	index = 0;
	while (index < 4)
	{
		if (index == 0)
			philo[index].left_fork = philo[3].right_fork;
		else
			philo[index].left_fork = philo[index - 1].right_fork;
		index++;
	}
	create_threads(threads, philo);
	index = 0;
	while (index < 4)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
	return 0;
}
