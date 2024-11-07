/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:44:35 by diolivei          #+#    #+#             */
/*   Updated: 2024/11/07 18:01:05 by diolivei         ###   ########.fr       */
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
	int				philo_count;
	unsigned int	init_time;
	long			repeat_count;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long			eat_count;
	pthread_mutex_t	eat_count_lock;
	int				died;
	pthread_mutex_t	died_lock;
}					t_philo_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		fork_lock;
	unsigned int		last_meal;
	pthread_mutex_t		last_meal_lock;
	struct s_philo_data	*data;
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
