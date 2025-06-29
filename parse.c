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
	long	temp_values[5];
	
	if (ac != 5 && ac != 6)
		return (write(2, "Invalid number of argument\n", 28));
	
	temp_values[0] = ft_atol(av[1]);
	temp_values[1] = ft_atol(av[2]);
	temp_values[2] = ft_atol(av[3]);
	temp_values[3] = ft_atol(av[4]);
	if (ac == 6)
		temp_values[4] = ft_atol(av[5]);
	else
		temp_values[4] = -1; // -1 means unlimited meals
	
	// Check for invalid values (LONG_MAX indicates error in ft_atol)
	if (temp_values[0] == LONG_MAX || temp_values[1] == LONG_MAX || 
		temp_values[2] == LONG_MAX || temp_values[3] == LONG_MAX)
		return (write(2, "Invalid value\n", 14));
	if (ac == 6 && temp_values[4] == LONG_MAX)
		return (write(2, "Invalid value\n", 14));
	
	data->nb_philo = temp_values[0];
	data->time_to_die = temp_values[1];
	data->time_to_eat = temp_values[2];
	data->time_to_sleep = temp_values[3];
	data->nb_times_to_eat = temp_values[4];
	
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (write(2, "Invalid value\n", 14));
	if (ac == 6 && data->nb_times_to_eat <= 0)
		return (write(2, "Invalid value\n", 14));
	return 0;
}
