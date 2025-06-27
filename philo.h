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

# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_times_to_eat;
    long start_time;
    pthread_mutex_t lock;
    pthread_mutex_t *forks;
    int		    death_flag;
}   t_rules;

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    long long       last_meal_time;
    int             meals_eaten;
    pthread_t       thread;

    struct s_rules  *rules;
}               t_philo;



long	ft_atol(const char *nptr);
void	exit_error(char *error);
int	parse_args(int ac, char *av[], t_rules *data);

#endif
