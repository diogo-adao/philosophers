/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:44:35 by diolivei          #+#    #+#             */
/*   Updated: 2024/11/13 16:41:32 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_EAT "\033[1;96mis eating\033[0;39m"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_TAKE_FORK "has taken a fork"
# define PHILO_DIE "\033[1;91mdied 💀\033[0;39m"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_philo_data
{
	int				philo_count; // Number of philosophers
	unsigned int	init_time; // Initial time of program execution
	long			repeat_count; // Number of times each philosopher must eat
	long long		die_time; // Max time a philosopher can live without eating
	long long		eat_time; // Time a philosopher takes to eat
	long long		sleep_time; // Time a philosopher takes to sleep
	long			eat_count; // Number of times a philosopher has eaten
	pthread_mutex_t	eat_count_lock; // Controls access to eat_count variable
	int				died; // Shared death flag
	pthread_mutex_t	died_lock; // Controls access to died variable
}					t_philo_data;

typedef struct s_philo
{
	int					id; // Philosopher identifier
	pthread_t			thread_id; // Thread identifier
	pthread_mutex_t		fork_lock; // Controls access to forks
	unsigned int		last_meal; // Holds the last time a philosopher ate
	pthread_mutex_t		last_meal_lock; // Controls access to last_meal variable
	struct s_philo_data	*data; // Gives access to the data struct
}						t_philo;

// PHILO
unsigned int	get_current_time(void);
int				ft_usleep(unsigned int usec);
void			*philo_init(int philo_count, t_list *philos);
void			*free_philos(t_list *philos);
void			philo_timestamp(t_list *philos, char *action, unsigned int t);
t_list			*philo_lst(t_philo_data *d);

// UTILS
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void 			ft_lstadd_back(t_list **lst, t_list *newnode);
long			ft_atoi(const char *str);

#endif
