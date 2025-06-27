/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:43 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/04/02 16:13:46 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules *data = malloc(sizeof(t_rules));
	if (pthread_mutex_init(&data->lock, NULL))
	{
		printf("mutex init feiled");
		return 1;
	}
	parse_args(ac, av, data);
	pthread_mutex_destroy(&data->lock);
}
