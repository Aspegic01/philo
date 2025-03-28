#include "philo.h"

int	main(int ac, char **av)
{
	if (ac != 5)
		return (write(1, "Wrong argument count\n", 21), 1);
	if (check_arg(ac, av) != 1)
		exit_error("arg is not correct\n");
}
