/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:50:00 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/25 16:21:22 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	message(const char *type, t_phil *p_phil, long time)
{
	sem_wait(p_phil->data_ptr->micro);
	printf("%ld %s_%d %s", time, PH, p_phil->phil_id, type);
	sem_post(p_phil->data_ptr->micro);
}

void	eating(t_phil *p_phil)
{
	sem_wait(p_phil->data_ptr->fork);
	message(R_FORK, p_phil, cur_t() - p_phil->start_time);
	sem_wait(p_phil->data_ptr->fork);
	message(L_FORK, p_phil, cur_t() - p_phil->start_time);
	p_phil->last_eating = cur_t();
	message(EAT, p_phil, cur_t() - p_phil->start_time);
	my_usleep(p_phil->eat_time);
	sem_post(p_phil->data_ptr->fork);
	sem_post(p_phil->data_ptr->fork);
}

void	sleeping(t_phil *p_phil)
{
	message(SLEEP, p_phil, cur_t() - p_phil->start_time);
	my_usleep(p_phil->sleep_time);
}

int	dying(t_phil *p_phil)
{
	if (cur_t() - p_phil->last_eating > p_phil->die_time)
	{
		sem_wait(p_phil->data_ptr->micro);
		printf("%ld %s_%d %s", cur_t() - p_phil->start_time, PH, \
				p_phil->phil_id, DIE);
		return (1);
	}
	return (0);
}

void	daily(t_phil *p_phil)
{
	pthread_t	inspect;

	pthread_create(&inspect, NULL, inspection, p_phil);
	pthread_detach(inspect);
	if (p_phil->phil_id % 2 == 0)
		my_usleep(200);
	while (p_phil->times_to_eat)
	{
		message(THINK, p_phil, cur_t() - p_phil->start_time);
		eating(p_phil);
		sleeping(p_phil);
		if (p_phil->times_to_eat != -1)
			p_phil->times_to_eat -= 1;
	}
	exit(0);
}
