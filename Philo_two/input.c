/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:04:04 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 10:05:49 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_params g_params;

void	*death_check(void)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < g_params.philos_n)
		{
			if (partial_time(g_params.philos[i].time_since_eat)
					>= g_params.die_time)
			{
				if (g_params.philos[i].eat_counter == 0)
				{
					return (NULL);
				}
				print_action(0, partial_time(g_params.start_time), i);
				free_mem();
			}
		}
	}
	return (NULL);
}

int		check_argv(char **argv)
{
	int i;
	int c;

	i = 1;
	while (argv[i] != NULL)
	{
		c = 0;
		while (argv[i][c] != '\0')
		{
			if (argv[i][c] < '0' || argv[i][c] > '9')
				return (0);
			c++;
		}
		++i;
	}
	return (1);
}

void	check_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		putstr("Wrong number of arguments!\n");
		exit(0);
	}
	else if (check_argv(argv) == 0 || ft_atoi(argv[1]) < 2 ||
		(argv[5] && ft_atoi(argv[5]) < 1))
	{
		putstr("Invalid parameters!\n");
		exit(0);
	}
}

int		ft_atoi(char *str)
{
	int				i;
	long long int	result;
	long long int	neg;

	i = 0;
	neg = 1;
	result = 0;
	while (str[i] < 33)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < 48 || 57 < str[i])
			return (result * neg);
		else
			result = (result * 10) + (long long int)(str[i] - '0');
		i++;
	}
	return (result * neg);
}
