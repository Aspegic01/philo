#include "philo.h"

void	exit_error(char *error)
{
	printf("%s", error);
	exit(EXIT_FAILURE);
}

long	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[j])
		{
			if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
				return (LONG_MAX);
			j++;
		}
		i++;
	}
	return (1);
}

