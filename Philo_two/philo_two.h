/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:02:49 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 10:07:37 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct	s_philosopher
{
	int			n;
	int			eat_counter;
	int64_t		time_since_eat;
	int			full;
	pthread_t	death_thread;

}				t_philo;

typedef struct	s_params
{
	int			philos_n;
	int64_t		eat_time;
	int64_t		sleep_time;
	int64_t		die_time;
	int			eat_counter;
	int64_t		start_time;
	sem_t		*write_sem;
	sem_t		*forks;
	pthread_t	*threads;
	t_philo		*philos;
}				t_params;

int				min(int a, int b);
int				max(int a, int b);
void			putstr(char *str);
void			putnbr(unsigned long nb);
int				ft_atoi(char *str);
void			init_params(char **argv);
void			init_philos(void);
void			init_threads(void);
void			*phil(void *arg);
void			*death_check();
void			free_mem(void);
void			check_input(int argc, char **argv);
int				check_argv(char **argv);
int64_t			get_time(void);
int64_t			partial_time(int64_t start);
void			print_action(int n, unsigned long int time, int name);

#endif
