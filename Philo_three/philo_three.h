/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 11:31:36 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 11:34:15 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_philosopher
{
	int			n;
	int			eat_counter;
	int64_t		time_since_eat;
	int			pid;
	pthread_t	death;

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
	sem_t		*exit_sem;
	sem_t		*killer_sem;
	pthread_t	*threads;
	t_philo		*philos;

}				t_params;

int				eat_action(t_philo *phil);
int				min(int a, int b);
int				max(int a, int b);
void			putstr(char *str);
void			putnbr(unsigned long nb);
int				ft_atoi(char *str);
void			init_params(char **argv);
void			init_philos(void);
void			init_process(void);
void			*phil(void *arg);
void			*death_check();
void			free_mem(void);
void			check_input(int argc, char **argv);
int				check_argv(char **argv);
int64_t			get_time(void);
int64_t			partial_time(int64_t start);
void			print_action(int n, int64_t time, int name);

#endif
