#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include "philo_two.h"

#define SEMAFORO "/sem"

sem_t *semaf;

void	*funcion(void *letra)
{
	char *a;
	a = (char*)letra;
	for (int i = 0; i<5; i++)
	{
		//printf("wait %i\n", semaf = sem_wait(semaf));
		sem_wait(semaf);
		putstr(a);
		//sleep(1);
		sleep(1);
		//printf("post %i\n", sem_post(semaf));
		sem_post(semaf);
	}
}

int main()
{
	pthread_t t1, t2, t3;
	char *a = " Buenos días mi sargento hoy la tengo como el cemento \0";
	char *b = " ni mal \0";
	char *c = " puta mierda \0";

	sem_unlink("/sem");
	if ((semaf = sem_open(SEMAFORO, O_CREAT|O_EXCL , 0660, 1)) == SEM_FAILED)
	{
    	perror ("sem_open");
		exit (1);
	}
	//semaf = sem_open("/sem", O_CREAT, 0660, 1);
	pthread_create(&t1, NULL, funcion, a);
	pthread_create(&t2, NULL, funcion, b);
	pthread_create(&t3, NULL, funcion, c);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	return (0);
}
