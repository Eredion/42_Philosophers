/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 11:34:45 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 11:36:46 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_params g_params;

int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int64_t)1000) + (time.tv_usec / 1000));
}

int64_t	partial_time(int64_t start)
{
	return (get_time() - start);
}

void	free_mem(void)
{
	sem_unlink("/write_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/exit_sem");
	sem_unlink("/killer_sem");
	free(g_params.philos);
	free(g_params.threads);
	exit(0);
}

void	print_action(int n, int64_t time, int name)
{
	sem_wait(g_params.write_sem);
	putnbr(time);
	putstr("\t ");
	putnbr(name + 1);
	if (n == 1)
		putstr(" has taken a fork\n");
	else if (n == 2)
		putstr(" is eating\n");
	else if (n == 3)
		putstr(" is sleeping\n");
	else if (n == 4)
		putstr(" is thinking\n");
	else if (n == 5)
		putstr(" has eaten enough\n");
	else
	{
		putstr(" died\n");
		return ;
	}
	sem_post(g_params.write_sem);
}

int		main(int argc, char **argv)
{
	check_input(argc, argv);
	init_params(argv);
	init_philos();
	init_process();
	free_mem();
}
