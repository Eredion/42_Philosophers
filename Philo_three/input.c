/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 11:43:32 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 11:59:06 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_params g_params;

void	*kill_prcs(void *ptr)
{
	(void)ptr;
	sem_wait(g_params.killer_sem);
	exit(0);
}

void	*death_check(void *n)
{
	int			*i;
	pthread_t	killer;

	pthread_create(&killer, NULL, kill_prcs, NULL);
	i = (int*)n;
	while (1)
	{
		if (partial_time(g_params.philos[*i].time_since_eat)
					>= g_params.die_time)
		{
			print_action(0, partial_time(g_params.start_time), *i);
			sem_post(g_params.exit_sem);
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
	sem_unlink("/write_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/exit_sem");
	sem_unlink("/killer_sem");
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
