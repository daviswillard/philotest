#include <philo.h>

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->data->writer);
	printf("philosopher %d has taken left fork\n", philo->name);
	printf("philosopher %d is eating\n", philo->name);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->data->writer);
	philo->last_eat = get_time() - philo->data->start_time;
	if (philo->data->eat_count > 0 && philo->eaten < philo->data->eat_count)
		philo->eaten++;
}

_Noreturn void	forks_action(t_philosopher *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->right_fork);
		print(philo->data->writer, philo->name, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		eat(philo);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print(philo->data->writer, philo->name, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print(philo->data->writer, philo->name, "is thinking");
	}
}

void	*philosophy(void *args)
{
	t_philosopher *philo;

	philo = (t_philosopher *)args;
	if (!(philo->name % 2))
		usleep(philo->data->time_to_eat * 1000);
	forks_action(philo);
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

int main(int argc, char **argv)
{
	t_philosopher	*philo[4];
	pthread_t		threads[4];
	t_data			*data;
	int				index;

	data = data_init(argc, argv);
	for (index = 0; index < 4; index++)
		philo[index] = philo_init(index, data);
	for (index = 0; index < 4; index++)
		pthread_mutex_init(&philo[index]->right_fork, NULL);
	for (index = 0; index < 4; index++)
		if (index == 0)
			philo[index]->left_fork = &philo[3]->right_fork;
		else
			philo[index]->left_fork = &philo[index - 1]->right_fork;
	create_threads(threads, philo);
	for (index = 0; index < 4; index++)
		pthread_join(threads[index], NULL);
	return 0;
}
