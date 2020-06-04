#ifndef PHILO_TWO_H
# define PHILO_TWO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>

typedef struct	s_philosopher
{
	int					n;
	int					eat_counter;
	unsigned long		time_since_eat;

}				t_philo;

typedef struct	s_params
{
	int					philos_n;
	unsigned long		eat_time;
	unsigned long		sleep_time;
	unsigned long		die_time;
	int					eat_counter;
	unsigned long		start_time;

	pthread_t*			threads;
	t_philo*			philos;

}				t_params;

int					min(int a, int b);
int					max(int a, int b);
void				putstr(char* str);
void				putnbr(unsigned long nb);
int					ft_atoi(char* str);
void				init_params(char** argv);
void				init_philos(void);
void				init_threads(void);
void*				phil(void* arg);
void				*death_check();
void				free_mem(void);
void				check_input(int argc, char** argv);
int					check_argv(char **argv);
unsigned long		get_time(void);
unsigned long		partial_time(suseconds_t start);
pthread_mutex_t*	init_forks(int n);
void				print_action(int n, unsigned long int time, int name);

#endif
