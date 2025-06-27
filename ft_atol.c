/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:26 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/04/02 16:13:33 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int s)
{
	if (s >= '0' && s <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int s)
{
	if (s == ' ' || (s >= 9 && s <= 13))
		return (1);
	return (0);
}

int	ft_isascii(int s)
{
	if (s >= 0 && s <= 127)
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		return (LONG_MAX);
	i += (nptr[i] == '+');
	if (ft_isdigit(nptr[i]) == 0)
		return (LONG_MAX);
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] && ft_isascii(nptr[i]))
		return (LONG_MAX);
	return (res);
}
