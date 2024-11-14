/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:09:15 by diolivei          #+#    #+#             */
/*   Updated: 2024/11/13 16:42:00 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	invalid_args(int argc, char **argv)
{
	int		i;
	long	num;

	i = 0;
	while (++i < argc)
	{
		num = ft_atoi(argv[i]);
		if (i == 1 && (num < 1 || num > 200))
		{
			printf("The number of philos must be between 1 and 200\n");
			return (true);
		}
		else if (i == 5 && (num < 0 || num > INT_MAX))
		{
			printf("<repeat_times> must be between 0 and INT_MAX\n");
			return (true);
		}
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
		{
			printf("Time to die, eat or sleep must be between 1 and INT_MAX\n");
			return (true);
		}
	}
	return (false);
}

static void	init_data(t_philo_data *d, char **argv)
{
	d->philo_count = ft_atoi(argv[1]);
	d->die_time = ft_atoi(argv[2]);
	d->eat_time = ft_atoi(argv[3]);
	d->sleep_time = ft_atoi(argv[4]);
	d->repeat_count = -2;
	if (argv[5])
		d->repeat_count = ft_atoi(argv[5]);
	d->init_time = get_current_time();
	d->died = 0;
	d->eat_count = 0;
	pthread_mutex_init(&d->died_lock, NULL);
	pthread_mutex_init(&d->eat_count_lock, NULL);
}

int	main(int argc, char **argv)
{
	t_philo_data	d;
	t_list			*philos;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo <philo_count> <time_to_die>");
		printf(" <time_to_eat> <time_to_sleep> [<repeat_times>]\n");
		return (1);
	}
	if (invalid_args(argc, argv)) // Check for invalid args
		return (1);
	init_data(&d, argv); // Initialize data
	philos = philo_lst(&d); // Create a list of philos
	ft_lstlast(philos)->next = philos; // Make it a circular list
	philo_init(d.philo_count, philos); // Initialize simulation
	free_philos(philos); // Free all memory
	return (0);
}
