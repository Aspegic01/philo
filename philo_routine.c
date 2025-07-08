/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <mlabrirh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:42:16 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/06/30 10:47:25 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *p, const char *status)
{
	unsigned long	current_time;
	unsigned long	elapsed_time;

	pthread_mutex_lock(&p->rules->print_mutex);
	pthread_mutex_lock(&p->rules->death_mutex);
	if (p->rules->death_flag)
	{
		pthread_mutex_unlock(&p->rules->death_mutex);
		pthread_mutex_unlock(&p->rules->print_mutex);
		return;
	}
	pthread_mutex_unlock(&p->rules->death_mutex);
	
	current_time = gettime_now();
	elapsed_time = current_time - p->rules->start_time;
	printf("%lu %d %s\n", elapsed_time, p->id + 1, status);
	pthread_mutex_unlock(&p->rules->print_mutex);
}

void	philo_eat(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		print_status(p, FORK);
		pthread_mutex_lock(p->right_fork);
		print_status(p, FORK);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		print_status(p, FORK);
		pthread_mutex_lock(p->left_fork);
		print_status(p, FORK);
	}
	print_status(p, EAT);
	pthread_mutex_lock(p->meals);
	p->last_meal_time = gettime_now();
	p->meals_eaten++;
	pthread_mutex_unlock(p->meals);
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	philo_think(t_philo *p)
{
	unsigned long	think_time;
	
	print_status(p, THINK);
	if (p->rules->nb_philo % 2 == 1)
	{
		think_time = p->rules->time_to_eat;
		if (think_time > 0 && think_time < 400)
			usleep((think_time / 2) * 1000);
	}
}

void	philo_sleep(t_philo *p)
{
	unsigned long	start;
	unsigned long	elapsed;
	unsigned long	sleep_time;

	start = gettime_now();
	elapsed = 0;
	sleep_time = p->rules->time_to_sleep;
	print_status(p, SLEEP);
	while (elapsed < sleep_time)
	{
		if (is_dead(p))
			return ;
		usleep(100);
		elapsed = gettime_now() - start;
	}
}

int	is_dead(t_philo *p)
{
	int	dead;

	pthread_mutex_lock(&p->rules->death_mutex);
	dead = p->rules->death_flag;
	pthread_mutex_unlock(&p->rules->death_mutex);
	return (dead);
}
