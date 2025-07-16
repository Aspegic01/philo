/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <mlabrirh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:43 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/07/12 16:29:30 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettime_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_meals_complete(t_philo *philos, t_rules *rules)
{
	unsigned int	i;
	int				all_done;

	if (rules->nb_limit_meals == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(philos[i].meals);
		if (philos[i].meals_eaten < rules->nb_limit_meals)
			all_done = 0;
		pthread_mutex_unlock(philos[i].meals);
		if (!all_done)
			break ;
		i++;
	}
	if (all_done)
	{
		pthread_mutex_lock(&rules->death_mutex);
		rules->death_flag = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philos, t_rules *rules)
{
	unsigned int	i;
	unsigned long	now;

	i = 0;
	now = gettime_now();
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(philos[i].meals);
		if ((now - philos[i].last_meal_time) > rules->time_to_die)
		{
			pthread_mutex_unlock(philos[i].meals);
			pthread_mutex_lock(&rules->print_mutex);
			pthread_mutex_lock(&rules->death_mutex);
			rules->death_flag = 1;
			pthread_mutex_unlock(&rules->death_mutex);
			printf("%lu %d %s\n", now - rules->start_time, \
			philos[i].id, DEAD);
			pthread_mutex_unlock(&rules->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(philos[i].meals);
		i++;
	}
	return (0);
}

int	ft_setup(t_rules *a)
{
	t_philo	*p;

	if (!philo_init_data(a, &p) || !philo_setup_philosophers(a, p))
		return (0);
	philo_simul_des(a, p);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	*data;

	if (ac != 5 && ac != 6)
	{
		write(2, "[number_of_philo]: [time_to_die]:", 34);
		write(2, "[time_to_eat]: [time_to_sleep]", 29);
		write(2, " [number_of_times_each_philosopher_must_eat]\n", 45);
		return (1);
	}
	data = malloc(sizeof(t_rules));
	if (!data)
		return (write(2, "Rules malloc failed\n", 21), 1);
	if (parse_args(ac, av, data))
		return (free(data), 1);
	if (!ft_setup(data))
		return (free(data), 1);
	return (free(data), 0);
}
