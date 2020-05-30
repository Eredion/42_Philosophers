#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct	s_philosopher
{
	int					n;
	int					eat_counter;
	unsigned long int	time_since_eat;
	char*				n_str;
	int					r_fork;
	int					l_fork;
}				t_philo;

typedef struct	s_params
{
	int					philos_n;
	int					eat_time;
	int					sleep_time;
	int					die_time;
	int					eat_counter;
	unsigned long int	start_time;
	pthread_mutex_t*	forks;
	pthread_mutex_t		write_lock;
	pthread_t*			threads;
	t_philo*			philos;

}				t_params;

char	*ft_itoa(int n);
int		min(int a, int b);
int		max(int a, int b);
void	putstr(char* str);
void	putnbr(unsigned long nb);

#endif
