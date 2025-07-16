/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <mlabrirh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:57 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/07/12 15:55:33 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int ac, char *av[], t_rules *data)
{
	long	temp_values[5];

	temp_values[0] = ft_atol(av[1]);
	temp_values[1] = ft_atol(av[2]);
	temp_values[2] = ft_atol(av[3]);
	temp_values[3] = ft_atol(av[4]);
	if (ac == 6)
		temp_values[4] = ft_atol(av[5]);
	else
		temp_values[4] = -1;
	if (temp_values[0] == LONG_MAX || temp_values[1] == LONG_MAX || \
		temp_values[2] == LONG_MAX || temp_values[3] == LONG_MAX || \
		(ac == 6 && temp_values[4] == LONG_MAX))
		return (write(2, "Invalid value\n", 14), 1);
	data->nb_philo = temp_values[0];
	data->time_to_die = temp_values[1];
	data->time_to_eat = temp_values[2];
	data->time_to_sleep = temp_values[3];
	data->nb_limit_meals = temp_values[4];
	return (0);
}
