/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <mlabrirh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:03:58 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/07/12 16:04:10 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	ft_isdigit(int s)
{
	return (s >= '0' && s <= '9');
}

int	ft_isspace(int s)
{
	return (s == ' ' || (s >= 9 && s <= 13));
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	res;
	int		digit;

	i = 0;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		return (LONG_MAX);
	if (nptr[i] == '+')
		i++;
	if (!ft_isdigit(nptr[i]))
		return (LONG_MAX);
	while (nptr[i])
	{
		digit = nptr[i] - '0';
		res = res * 10 + digit;
		i++;
	}
	if (res <= 0)
		return (LONG_MAX);
	return (res);
}
