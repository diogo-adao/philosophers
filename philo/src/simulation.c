/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:09:00 by diolivei          #+#    #+#             */
/*   Updated: 2024/11/18 16:10:04 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	send_actions(t_list *node, t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&philo->fork_lock);
	print_actions(node, PHILO_TAKE_FORK, 0);
	pthread_mutex_lock(&next->fork_lock);
	print_actions(node, PHILO_TAKE_FORK, 0);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_current_time() - philo->data->init_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	print_actions(node, PHILO_EAT, philo->data->eat_time);
	print_actions(node, PHILO_SLEEP, 0);
	pthread_mutex_unlock(&next->fork_lock);
	pthread_mutex_unlock(&philo->fork_lock);
	ft_usleep(philo->data->sleep_time);
	print_actions(node, PHILO_THINK, 0);
}

void	*init_thread(void *node)
{
	t_philo		*philo;
	t_philo		*next;
	int			i;

	i = -1;
	philo = ((struct s_list *)node)->content;
	next = ((struct s_list *)node)->next->content;
	ft_usleep(!(philo->id % 2) * 2);
	pthread_mutex_lock(&philo->data->end_lock);
	while (philo->id != next->id && !philo->data->end && \
		(philo->data->repeat_count == -1 || ++i < philo->data->repeat_count))
	{
		pthread_mutex_unlock(&philo->data->end_lock);
		send_actions(node, philo, next);
		pthread_mutex_lock(&philo->data->end_lock);
	}
	pthread_mutex_unlock(&philo->data->end_lock);
	return (NULL);
}

void	*watch_philos(t_list *start, t_philo *philo)
{
	long	eat_c;
	long	last_meal;

	while (1)
	{
		philo = start->content;
		pthread_mutex_lock(&philo->data->eat_count_lock);
		eat_c = philo->data->eat_count;
		pthread_mutex_unlock(&philo->data->eat_count_lock);
		pthread_mutex_lock(&philo->last_meal_lock);
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->last_meal_lock);
		if (get_current_time() - philo->data->init_time - last_meal >= \
			philo->data->die_time || eat_c == \
			philo->data->philo_count * philo->data->repeat_count)
		{
			pthread_mutex_lock(&philo->data->end_lock);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->end_lock);
			if (eat_c != philo->data->philo_count * philo->data->repeat_count)
				print_actions(start, PHILO_DIE, 0);
			return (NULL);
		}
		start = start->next;
	}
}

void	*init_simulation(int philo_count, t_list *philos)
{
	int		i;
	t_list	*start;
	t_philo	*philo;

	i = -1;
	start = philos;
	while (++i < philo_count)
	{
		philo = start->content;
		if (pthread_create(&philo->thread_id, NULL, init_thread, start) != 0)
			return (free_philos(philos));
		start = start->next;
	}
	watch_philos(start, NULL);
	i = -1;
	while (++i < philo_count)
	{
		philo = start->content;
		pthread_join(philo->thread_id, NULL);
		start = start->next;
	}
	return (NULL);
}
