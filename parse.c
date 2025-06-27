/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:57 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/04/02 16:14:03 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *error)
{
	printf("%s", error);
	exit(EXIT_FAILURE);
}

int	parse_args(int ac, char *av[], t_rules *data)
{
	if (ac != 5 && ac != 6)
		return (write(2, "Invalid number of argument\n", 28));
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nb_times_to_eat = ft_atol(av[5]);
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (write(2, "Invalid value\n", 14));
	return 0;
}
