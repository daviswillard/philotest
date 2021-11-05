#include <philo.h>

int	main(int argc, char **argv)
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
	return (0);
}
