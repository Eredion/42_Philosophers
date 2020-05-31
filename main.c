#include "philo_one.h"

t_params g_params;

long unsigned int timestamp(long unsigned int start)
{
	struct timeval end;
	gettimeofday(&end, NULL);
	return ((end.tv_usec - start));
}

long unsigned int get_time()
{
	struct timeval end;
	gettimeofday(&end, NULL);
	return (end.tv_usec);
}

void print_action(int n, unsigned long int time, int name)
{
	pthread_mutex_lock(&g_params.write_lock);
	putnbr(time);
	putstr(" ");
	putnbr(name);
	if (n == 1)
		putstr(" has taken a fork\n");
	else if (n == 2)
		putstr(" is eating\n");
	else if (n == 3)
		putstr(" is sleeping\n");
	else if (n == 4)
		putstr(" is thinking\n");
	else
		putstr(" died\n");
	pthread_mutex_unlock(&g_params.write_lock);
}

void* phil(void* arg)
{
	t_philo* filo;
	filo = (t_philo*)arg;
	int i = -1;
//	while (1)
//		printf("tiempo de vida dentro %lu\t life time %i\n", timestamp(filo->time_since_eat), filo->die_time);

	while (++i < filo->eat_counter)
	{
		pthread_mutex_lock(&g_params.forks[filo->l_fork]);
		print_action(1, timestamp(g_params.start_time), filo->n);
		pthread_mutex_lock(&g_params.forks[filo->r_fork]);
		print_action(1, timestamp(g_params.start_time), filo->n);
	/*	if ((int)timestamp(filo->time_since_eat) >= filo->die_time)
		{
			printf("%lu %s died\n", timestamp(g_params.start_time), filo->n_str);
			exit(0);
		}
	*/	//printf("tiempo de vida %lu\t life time %i\n", timestamp(filo->time_since_eat), filo->die_time);
		filo->time_since_eat = get_time();
		print_action(2, timestamp(g_params.start_time), filo->n);
		usleep(g_params.eat_time);
		pthread_mutex_unlock(&g_params.forks[filo->l_fork]);
		pthread_mutex_unlock(&g_params.forks[filo->r_fork]);
		print_action(3, timestamp(g_params.start_time), filo->n);
		usleep(g_params.sleep_time);
		print_action(4, timestamp(g_params.start_time), filo->n);
	}
	return (NULL);
}

pthread_mutex_t* init_forks(int n)
{
	pthread_mutex_t* forks;
	int 				i;

	forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * n);
	i = -1;
	while (++i > n)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}


void	init_params(t_params *g_params) //Modificar con args
{

	g_params->start_time = get_time();
	g_params->philos_n = 5;
	g_params->eat_counter = 10;
	g_params->eat_time = 5000 * 1000;
	g_params->sleep_time = 6000 * 1000;
	g_params->die_time = 400 * 1000;
	g_params->forks = init_forks(g_params->philos_n);
	g_params->threads = (pthread_t*)malloc(sizeof(pthread_t) * g_params->philos_n);
	pthread_mutex_init(&g_params->write_lock, NULL);
}

void	init_philos(t_params *g_params)
{
	int i;

	g_params->philos = (t_philo*)malloc(sizeof(t_philo) * g_params->philos_n);
	i = -1;
	while (++i < g_params->philos_n)
	{
		g_params->philos[i].n = i;
		g_params->philos[i].eat_counter = g_params->eat_counter;
		g_params->philos[i].time_since_eat = g_params->start_time;
		g_params->philos[i].r_fork = min(i, (i + 1) % g_params->philos_n);
		g_params->philos[i].l_fork = max(i, (i + 1) % g_params->philos_n);
	}
}

void	*death_check()
{
	int i;

	while(1)
	{
		i = -1;
		while(i++ < g_params.philos_n)
		{
			if (g_params.philos[i].time_since_eat >= (unsigned long int)g_params.die_time)
			{
				printf("caca\n");
				exit(0);
			}
		} 
	}
	return NULL;
}

void	init_threads(t_params *g_params)
{
	int i;
	pthread_t	death_thread;

	i = -1;
	while (++i < g_params->philos_n)
		pthread_create(&g_params->threads[i], NULL, phil, (void *)&g_params->philos[i]);
	pthread_create(&death_thread, NULL, death_check, NULL);
//	while (1)

/*	if ((int)timestamp(g_params->philos[0].time_since_eat) >= g_params->die_time)
	{
		printf("tiempo de vida fuera %lu\t life time %i\n", timestamp(g_params->philos[0].time_since_eat),g_params->die_time);
		printf("nooooooooooooo\n");
		exit(0);
	}*/

	i = -1;
	while (++i < g_params->philos_n)
	{
		pthread_join(g_params->threads[i], NULL);
	}

	printf("tiempo de vida %lu\t life time %i\n", timestamp(g_params->philos[0].time_since_eat),g_params->die_time);
	sleep(1);
}

int	main()
{
	init_params(&g_params); //Esto debería pillar argv
	init_philos(&g_params);
	init_threads(&g_params);
    exit(0);
}

