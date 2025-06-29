/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:14:10 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/04/02 16:14:13 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>

#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DEAD "died"

typedef struct s_rules
{
	unsigned long	nb_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	long			nb_times_to_eat;
	unsigned long	start_time;
	int				death_flag;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
}	t_rules;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				dead;
	pthread_t		thread;
	t_rules			*rules;
}	t_philo;


long	ft_atol(const char *nptr);
void	exit_error(char *error);
int	parse_args(int ac, char *av[], t_rules *data);

#endif
