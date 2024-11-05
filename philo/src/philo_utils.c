#include "../philo.h"

t_philo	*philo_get_data(t_philo_data *d, int i)
{
	t_philo	*node;

	node = malloc(sizeof(struct s_philo));
	if (!node)
		return (philo_exit(NULL, NULL, THREAD_FAILED));
	node->id = i + 1;
	node->thread_id = 0;
	pthread_mutex_init(&node->fork_lock, NULL);
	pthread_mutex_init(&node->last_meal_lock, NULL);
	node->data = d;
	node->last_meal = 0;
	return (node);
}

t_list	*philo_lst(t_philo_data *d)
{
	int		i;
	t_list	*philos;

	i = -1;
	philos = NULL;
	while (++i < d->philo_count)
		ft_lstadd_back(&philos, ft_lstnew(philo_get_data(d, i)));
	return (philos);
}

int	philo_perror(char *param, t_philo_err err_code)
{
	printf("philo: ");
	if (err_code == INV_ARGS)
		printf("invalid number of arguments");
	if (err_code == NO_MEMORY)
		printf("no memory left on device");
	if (err_code == THREAD_FAILED)
		printf("failed to create a thread");
	if (err_code == INV_PHILO_COUNT)
		printf("invalid philosopher_count: ");
	if (err_code == INV_DIE_TIME)
		printf("invalid time_to_die: ");
	if (err_code == INV_EAT_TIME)
		printf("invalid time_to_eat: ");
	if (err_code == INV_SLEEP_TIME)
		printf("invalid time_to_sleep: ");
	if (err_code == INV_REPEAT_COUNT)
		printf("invalid repeat_times: ");
	if (err_code == TOO_MANY_PHILO)
		printf("system may not be able to handle that many threads: ");
	if (param && err_code != INV_ARGS && err_code != NO_MEMORY && \
			err_code != THREAD_FAILED)
		printf("%s", param);
	printf("\n");
	return (1);
}

void	philo_timestamp(t_list *philos, char *action, unsigned int t)
{
	unsigned int	time;
	t_philo		*philo;
	int			died;
	int			eat_count;

	philo = philos->content;
	pthread_mutex_lock(&philo->data->died_lock);
	died = philo->data->died;
	pthread_mutex_lock(&philo->data->eat_count_lock);
	eat_count = philo->data->eat_count;
	time = philo_get_time() - philo->data->init_time;
	if (philo->data->repeat_count * philo->data->philo_count != \
			eat_count && (!died || action[7] == 'd'))
	{
		printf("[\033[1;39m%06u\033[0;39m]  \033[1;96m%03d  \033[0;39m%s\n", \
			time, philo->id, action);
	}
	if (action[10] == 'e')
		philo->data->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_count_lock);
	pthread_mutex_unlock(&philo->data->died_lock);
	if (philo->data->repeat_count * philo->data->philo_count != \
			eat_count && (!died || action[7] == 'd'))
		ft_usleep(t);
}

void	*philo_exit(t_list *philos, char *param, t_philo_err err_code)
{
	t_philo	*philo;
	t_list	*temp;

	temp = philos;
	if (err_code != END)
		philo_perror(param, err_code);
	while (philos)
	{
		philo = philos->content;
		if (philo->id == philo->data->philo_count)
			philos->next = NULL;
		philos = philos->next;
	}
	ft_lstclear(&temp, free);
	return (NULL);
}
