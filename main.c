/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:43 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/06/30 14:12:08 by mlabrirh         ###   ########.fr       */
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

	if (rules->nb_times_to_eat == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(philos[i].meals);
		if (philos[i].meals_eaten < rules->nb_times_to_eat)
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
			philos[i].id + 1, DEAD);
			pthread_mutex_unlock(&rules->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(philos[i].meals);
		i++;
	}
	return (0);
}

void	*handle_philo(void *arg)
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
	a->start_time = gettime_now();
	a->death_flag = 0;
	*p = malloc(sizeof(t_philo) * a->nb_philo);
	if (!(*p))
		exit_error("Philosopher malloc failed\n");
	a->forks = malloc(sizeof(pthread_mutex_t) * a->nb_philo);
	a->meal = malloc(sizeof(pthread_mutex_t) * a->nb_philo);
	if (!a->forks || !a->meal)
		exit_error("Mutex malloc failed\n");
}

void	philo_init_mutexes(t_rules *a)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_init(&a->death_mutex, NULL);
	pthread_mutex_init(&a->print_mutex, NULL);
	while (i < a->nb_philo)
	{
		pthread_mutex_init(&a->forks[i], NULL);
		pthread_mutex_init(&a->meal[i], NULL);
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
		p[i].meals = &a->meal[i];
		p[i].left_fork = &a->forks[i];
		p[i].right_fork = &a->forks[(i + 1) % a->nb_philo];
		p[i].last_meal_time = gettime_now();
		i++;
	}
}

void	philo_start_threads(t_rules *a, t_philo *p)
{
	unsigned int	i;

	i = 0;
	while (i < a->nb_philo)
	{
		if (pthread_create(&p[i].thread, NULL,
				handle_philo, (void *)&p[i]) != 0)
			exit_error("Thread creation failed\n");
		i++;
	}
}

void	philo_monitor_simulation(t_rules *a, t_philo *p)
{
	while (!check_death(p, a) && !check_meals_complete(p, a))
		philo_sleep(p);
}

void	philo_join_threads(t_rules *a, t_philo *p)
{
	unsigned int	i;

	i = 0;
	while (i < a->nb_philo)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
}

void	philo_destroy_mutexes_and_free(t_rules *a, t_philo *p)
{
	unsigned int	i;

	i = 0;
	while (i < a->nb_philo)
	{
		pthread_mutex_destroy(&a->forks[i]);
		pthread_mutex_destroy(&a->meal[i]);
		i++;
	}
	pthread_mutex_destroy(&a->death_mutex);
	pthread_mutex_destroy(&a->print_mutex);
	free(p);
	free(a->forks);
	free(a->meal);
}

void	ft_setup(t_rules *a)
{
	t_philo	*p;

	philo_init_data(a, &p);
	philo_init_mutexes(a);
	philo_setup_philosophers(a, p);
	philo_start_threads(a, p);
	philo_monitor_simulation(a, p);
	philo_join_threads(a, p);
	philo_destroy_mutexes_and_free(a, p);
}

int	main(int ac, char **av)
{
	t_rules	*data;

	data = malloc(sizeof(t_rules));
	if (!data)
		exit_error("Rules malloc failed\n");
	if (parse_args(ac, av, data))
		return (free(data), 1);
	ft_setup(data);
	return (free(data), 0);
}
