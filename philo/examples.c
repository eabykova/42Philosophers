/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examples.c                                             :+:      :+:    :+:
 * */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:31:20 by mmicheli          #+#    #+#           /*   Updated: 2022/06/30 19:51:03 by mmicheli         ###   ########.fr       */
  */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	g_fuel = 0;
pthread_mutex_t	g_mutex_fuel;
pthread_cond_t	g_cond_fuel;

void	*fuel_filling(void *arg)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		pthread_mutex_lock(&g_mutex_fuel);
		g_fuel += 15;
		printf("Filled fuel: %d\n", g_fuel);
		pthread_mutex_unlock(&g_mutex_fuel);
		pthread_cond_signal(&g_cond_fuel);
		sleep(1);
	}
}

void	*car(void *arg)
{
	pthread_mutex_lock(&g_mutex_fuel);
	while (g_fuel < 40)
	{
		printf("No fuel. Waiting...\n");
		pthread_cond_wait(&g_cond_fuel, &g_mutex_fuel);
	}
	g_fuel -= 40;
	printf("Got fuel. Now left: %d\n", g_fuel);
	pthread_mutex_unlock(&g_mutex_fuel);
}

int	main(int argc, char **argv)
{
	pthread_t	th[2];
	int			i;

	pthread_mutex_init(&g_mutex_fuel, NULL);
	pthread_cond_init(&g_cond_fuel, NULL);
	i = -1;
	while (++i < 2)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL))
				ft_kraft_error(CREATE_ERROR, 1);
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL))
				ft_kraft_error(CREATE_ERROR, 1);
		}
	}
	i = -1;
	while (++i < 2)
	{
		if (pthread_join(th[i], NULL))
			ft_kraft_error(JOIN_ERROR, 1);
	}
	pthread_mutex_destroy(&g_mutex_fuel);
	pthread_cond_destroy(&g_cond_fuel);
	return (0);
}

pthread_mutex_t	g_mutex;

void	*routine(void *arg)
{
	if (pthread_mutex_trylock(&g_mutex) == 0)
	{
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&g_mutex);
	}
	else
		printf("Did not get lock\n");
}

int	main(int argc, char **argv)
{
	pthread_t	th[4];
	int			i;

	pthread_mutex_init(&g_mutex, NULL);
	i = -1;
	while (++i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL))
			ft_kraft_error(CREATE_ERROR, 1);
	}
	i = -1;
	while (++i < 4)
	{
		if (pthread_join(th[i], NULL))
			ft_kraft_error(JOIN_ERROR, 1);
	}
	pthread_mutex_destroy(&g_mutex);
}

int	g_primes[10] = {2, 1, 45, 83, 3, 58, 0, 10, 78, 8};

void	*routine(void *arg)
{
	int	index;
	int	i;
	int	sum;

	index = *(int *)arg;
	sum = 0;
	i = -1;
	while (++i < 5)
		sum += g_primes[index + i];
	*(int *)arg = sum;
	printf("Local sum: %d\n", sum);
	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t	th[2];
	int			i;
	int			*a;
	int			*r;
	int			glob_sum;

	i = -1;
	while (++i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a))
			ft_kraft_error(CREATE_ERROR, 1);
	}
	i = -1;
	glob_sum = 0;
	while (++i < 2)
	{
		if (pthread_join(th[i], &r))
			ft_kraft_error(JOIN_ERROR, 1);
		glob_sum += *r;
		free(r);
	}
	printf("Global sum: %d\n", glob_sum);
	return (0);
}

long long		g_mails = 0;
pthread_mutex_t	g_mutex;

void	*roll_dice(void)
{
	int	value;
	int	*result;

	result = malloc(sizeof(int));
	value = (rand() % 6) + 1;
	*result = value;
	printf("Thread result: %p\n", result);
	return ((void *)result);
}

int	main(void)
{
	pthread_t	th;
	int			*res;

	srand(time(NULL));
	if (pthread_create(&th, NULL, &roll_dice, NULL))
		ft_kraft_error(CREATE_ERROR, 1);
	if (pthread_join(th, (void **)&res))
		ft_kraft_error(JOIN_ERROR, 1);
	printf("Main result: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
}

void	*routine(void)
{
	long long	count;

	count = -1;
	while (++count < 1000000)
	{
		pthread_mutex_lock(&g_mutex);
		g_mails++;
		pthread_mutex_unlock(&g_mutex);
	}
}

int	main(void)
{
	pthread_t	th[8];
	int			i;

	pthread_mutex_init(&g_mutex, NULL);
	i = -1;
	while (++i < 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL))
			ft_kraft_error(CREATE_ERROR, 1);
		printf("Thread %d is started\n", i);
	}
	i = -1;
	while (++i < 8)
	{
		if (pthread_join(th[i], NULL))
			ft_kraft_error(JOIN_ERROR, 1);
		printf("Thread %d finish the execution\n", i);
	}
	pthread_mutex_destroy(&g_mutex);
	printf("Number of mails is %lld\n", g_mails);
	return (0);
}
