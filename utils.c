/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <mlabrirh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:26:31 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/07/12 15:46:09 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->rules->nb_philo == 1)
		return (print_status(p, FORK),
			philo_sleep(p), NULL);
	if (p->id % 2 == 1)
	{
		philo_think(p);
		if (is_dead(p))
			return (NULL);
	}
	while (!is_dead(p))
	{
		philo_eat(p);
		if (is_dead(p))
			break ;
		philo_sleep(p);
		if (is_dead(p))
			break ;
		philo_think(p);
	}
	return (NULL);
}

void	philo_init_data(t_rules *a, t_philo **p)
{
	unsigned int	i;

	a->start_time = gettime_now();
	a->death_flag = 0;
	*p = malloc(sizeof(t_philo) * a->nb_philo);
	if (!(*p))
		exit_error("Philosopher malloc failed\n");
	a->forks = malloc(sizeof(pthread_mutex_t) * a->nb_philo);
	a->meals = malloc(sizeof(pthread_mutex_t) * a->nb_philo);
	if (!a->forks || !a->meals)
		exit_error("Mutex malloc failed\n");
	i = 0;
	pthread_mutex_init(&a->death_mutex, NULL);
	pthread_mutex_init(&a->print_mutex, NULL);
	while (i < a->nb_philo)
	{
		pthread_mutex_init(&a->forks[i], NULL);
		pthread_mutex_init(&a->meals[i], NULL);
		i++;
	}
}

void	philo_setup_philosophers(t_rules *a, t_philo *p)
{
	unsigned int	i;

	i = 0;
	while (i < a->nb_philo)
	{
		p[i].id = i;
		p[i].dead = 0;
		p[i].meals_eaten = 0;
		p[i].rules = a;
		p[i].meals = &a->meals[i];
		p[i].left_fork = &a->forks[i];
		p[i].right_fork = &a->forks[(i + 1) % a->nb_philo];
		p[i].last_meal_time = gettime_now();
		i++;
	}
	i = 0;
	while (i < a->nb_philo)
	{
		if (pthread_create(&p[i].thread, NULL,
				routine, (void *)&p[i]) != 0)
			exit_error("Thread creation failed\n");
		i++;
	}
}

void	philo_simul_des(t_rules *a, t_philo *p)
{
	unsigned int	i;

	while (!check_death(p, a) && !check_meals_complete(p, a))
		usleep(100);
	i = 0;
	while (i < a->nb_philo)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < a->nb_philo)
	{
		pthread_mutex_destroy(&a->forks[i]);
		pthread_mutex_destroy(&a->meals[i]);
		i++;
	}
	pthread_mutex_destroy(&a->death_mutex);
	pthread_mutex_destroy(&a->print_mutex);
	free(p);
	free(a->forks);
	free(a->meals);
}
