#include "philo_three.h"

t_params g_params;

void* phil(void* arg)
{
	t_philo* phil;

	phil = (t_philo*)arg;
	g_params.philos[phil->n].time_since_eat = get_time();
	pthread_create(&phil->death, NULL, death_check, &phil->n);
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
			break;
		print_action(3, partial_time(g_params.start_time), phil->n);
		usleep(g_params.sleep_time);
		print_action(4, partial_time(g_params.start_time), phil->n);
	}
	print_action(5, partial_time(g_params.start_time), phil->n);
	return (NULL);
}

void	init_params(char** argv)
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
	g_params.threads = (pthread_t*)malloc
		(sizeof(pthread_t) * g_params.philos_n);
	g_params.write_sem = sem_open("/write_sem", O_CREAT | O_EXCL, 0660, 1);
	g_params.exit_sem = sem_open("/exit_sem", O_CREAT | O_EXCL, 0660, 0);
	g_params.killer_sem = sem_open("/killer_sem", O_CREAT | O_EXCL, 0660, 0);
	g_params.forks = sem_open("/forks_sem",	O_CREAT | O_EXCL, 0660,
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
	}
}

void *end()
{
	int	i;

	sem_wait(g_params.exit_sem);
	i = -1;
	while(++i < g_params.philos_n)
		sem_post(g_params.killer_sem);
	free_mem();
	exit(0);
}

void	init_process(void)
{
	int i;
	pthread_t	exit_thread;

	i = -1;
	while (++i < g_params.philos_n)
	{
		if ((g_params.philos[i].pid = fork()) == 0)
		{
			phil((void*)&g_params.philos[i]);
			exit(0);
		}
	}
	pthread_create(&exit_thread, NULL, end, NULL);
	i = -1;
	while (++i < g_params.philos_n)
		waitpid(g_params.philos[i].pid, 0, 0);
}
