#include <philo.h>


static void	eat(t_philosopher *philo)
{
	print(philo, "is eating");
	philo->last_eat = get_time();
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->eat_count > 0 && philo->eaten < philo->data->eat_count)
		philo->eaten++;
}

static void	forks_action(t_philosopher *philo)
{
	if (philo->name % 2)
	{
		pthread_mutex_lock(&philo->right_fork);
		print(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken left fork");
		pthread_mutex_lock(&philo->right_fork);
		print(philo, "has taken right fork");
	}
}

static void	*philosophy(void *args)
{
	t_philosopher	*philo;
	pthread_t		watcher;

	philo = (t_philosopher *)args;
	if (!(philo->name % 2))
		ft_usleep(philo->data->time_to_eat);
	pthread_create(&watcher, NULL, watch, philo);
	pthread_detach(watcher);
	while (1)
	{
		forks_action(philo);
		eat(philo);
		print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print(philo, "is thinking");
		if (!philo->data->life_status)
			break ;
	}
	return (NULL);
}

void	create_threads(pthread_t *threads, t_philosopher *philo[])
{
	int	index;

	index = 0;
	philo[0]->data->start_time = get_time();
	while (index < 4)
	{
		pthread_create(&threads[index], NULL, philosophy, philo[index]);
		index++;
	}
}

