/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:36:02 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/27 12:14:48 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_params g_params;

void				*phil(void *arg)
{
	t_philo *phil;

	phil = (t_philo*)arg;
	while (1)
	{
		pthread_mutex_lock(&g_params.forks[phil->l_fork]);
		print_action(1, partial_time(g_params.start_time), phil->n);
		pthread_mutex_lock(&g_params.forks[phil->r_fork]);
		print_action(1, partial_time(g_params.start_time), phil->n);
		g_params.philos[phil->n].time_since_eat = get_time();
		print_action(2, partial_time(g_params.start_time), phil->n);
		usleep(g_params.eat_time);
		pthread_mutex_unlock(&g_params.forks[phil->l_fork]);
		pthread_mutex_unlock(&g_params.forks[phil->r_fork]);
		if (phil->eat_counter > 0)
			--phil->eat_counter;
		if (phil->eat_counter == 0)
			break ;
		print_action(3, partial_time(g_params.start_time), phil->n);
		usleep(g_params.sleep_time);
		print_action(4, partial_time(g_params.start_time), phil->n);
	}
	phil->full = 1;
	print_action(5, partial_time(g_params.start_time), phil->n);
	return (NULL);
}

void				init_params(char **argv)
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
	g_params.forks = init_forks(g_params.philos_n);
	g_params.threads = (pthread_t*)malloc(sizeof(pthread_t)
						* g_params.philos_n);
	pthread_mutex_init(&g_params.write_lock, NULL);
}

void				init_philos(void)
{
	int i;

	g_params.philos = (t_philo*)malloc(sizeof(t_philo) * g_params.philos_n);
	i = -1;
	while (++i < g_params.philos_n)
	{
		g_params.philos[i].full = 0;
		g_params.philos[i].n = i;
		g_params.philos[i].eat_counter = g_params.eat_counter;
		g_params.philos[i].time_since_eat = g_params.start_time;
		g_params.philos[i].r_fork = min(i, (i + 1) % g_params.philos_n);
		g_params.philos[i].l_fork = max(i, (i + 1) % g_params.philos_n);
	}
}

void				init_threads(void)
{
	int			i;
	pthread_t	death_thread;

	i = -1;
	while (++i < g_params.philos_n)
		pthread_create(&g_params.threads[i], NULL, phil,
						(void *)&g_params.philos[i]);
	pthread_create(&death_thread, NULL, death_check, NULL);
	i = -1;
	while (++i < g_params.philos_n)
		pthread_join(g_params.threads[i], NULL);
}

pthread_mutex_t		*init_forks(int n)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * n);
	i = -1;
	while (++i > n)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}
