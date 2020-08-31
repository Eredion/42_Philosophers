/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:47:45 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 10:00:22 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_params g_params;

void	*phil(void *arg)
{
	t_philo	*phil;

	phil = (t_philo*)arg;
	g_params.philos[phil->n].time_since_eat = get_time();
	while (1)
	{
		sem_wait(g_params.forks);
		print_action(1, partial_time(g_params.start_time), phil->n);
		sem_wait(g_params.forks);
		print_action(1, partial_time(g_params.start_time), phil->n);
		g_params.philos[phil->n].time_since_eat = get_time();
		print_action(2, partial_time(g_params.start_time), phil->n);
		usleep(g_params.eat_time);
		sem_post(g_params.forks);
		sem_post(g_params.forks);
		if (phil->eat_counter > 0)
			--phil->eat_counter;
		if (phil->eat_counter == 0)
			break ;
		print_action(3, partial_time(g_params.start_time), phil->n);
		usleep(g_params.sleep_time);
		print_action(4, partial_time(g_params.start_time), phil->n);
	}
	print_action(5, partial_time(g_params.start_time), phil->n);
	return (NULL);
}

void	init_params(char **argv)
{
	g_params.start_time = get_time();
	g_params.philos_n = ft_atoi(argv[1]);
	g_params.die_time = ft_atoi(argv[2]);
	g_params.eat_time = 1000 * ft_atoi(argv[3]);
	g_params.sleep_time = 1000 * ft_atoi(argv[4]);
	if (argv[5])
		g_params.eat_counter = ft_atoi(argv[5]);
	else
		g_params.eat_counter = -1;
	g_params.threads = (pthread_t*)malloc(sizeof(pthread_t)
						* g_params.philos_n);
	g_params.write_sem = sem_open("/write_sem", O_CREAT | O_EXCL, 0660, 1);
	g_params.forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0660,
		g_params.philos_n);
}

void	init_philos(void)
{
	int i;

	g_params.philos = (t_philo*)malloc(sizeof(t_philo) * g_params.philos_n);
	i = -1;
	while (++i < g_params.philos_n)
	{
		g_params.philos[i].n = i;
		g_params.philos[i].eat_counter = g_params.eat_counter;
		g_params.philos[i].time_since_eat = g_params.start_time;
		g_params.philos[i].full = 0;
	}
}

void	init_threads(void)
{
	int			i;
	pthread_t	death_thread;

	i = -1;
	while (++i < g_params.philos_n)
	{
		pthread_create(&g_params.threads[i], NULL, phil,
			(void *)&g_params.philos[i]);
		usleep(10);
	}
	pthread_create(&death_thread, NULL, death_check, NULL);
	i = -1;
	while (++i < g_params.philos_n)
	{
		pthread_join(g_params.threads[i], NULL);
		g_params.philos[i].full = 1;
	}
}
