/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:09:08 by diolivei          #+#    #+#             */
/*   Updated: 2024/11/18 16:10:54 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*philo_data(t_philo_data *d, int i)
{
	t_philo	*node;

	node = malloc(sizeof(struct s_philo));
	if (!node)
		return (NULL);
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
		ft_lstadd_back(&philos, ft_lstnew(philo_data(d, i)));
	return (philos);
}

void	print_actions(t_list *philos, char *action, unsigned int t)
{
	unsigned int	time;
	t_philo			*philo;
	int				ended;

	philo = philos->content;
	pthread_mutex_lock(&philo->data->end_lock);
	ended = philo->data->end;
	time = get_current_time() - philo->data->init_time;
	if (!ended || action[7] == 'd')
	{
		printf("\033[1;90m[%05u]  \033[1;92m%03d  \033[1;97m%s\n",
			time, philo->id, action);
	}
	if (action[10] == 'e')
	{
		pthread_mutex_lock(&philo->data->eat_count_lock);
		philo->data->eat_count++;
		pthread_mutex_unlock(&philo->data->eat_count_lock);
	}
	pthread_mutex_unlock(&philo->data->end_lock);
	if (!ended)
		ft_usleep(t);
}

void	*free_philos(t_list *philos)
{
	t_philo	*philo;
	t_list	*temp;

	temp = philos;
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
