/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:40:33 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/18 10:04:33 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	message(const char *type, t_phil *p_phil, long time)
{
	pthread_mutex_lock(p_phil->micro);
	printf("%ld %s_%d %s", time, PH, p_phil->phil_id, type);
	pthread_mutex_unlock(p_phil->micro);
}

static void	eating(t_phil *p_phil)
{
	pthread_mutex_lock(&p_phil->my_fork);
	message(R_FORK, p_phil, cur_t() - p_phil->start_time);
	pthread_mutex_lock(&p_phil->next->my_fork);
	message(L_FORK, p_phil, cur_t() - p_phil->start_time);
	message(EAT, p_phil, cur_t() - p_phil->start_time);
	p_phil->last_eating = cur_t();
	my_usleep(p_phil->eat_time);
	p_phil->has_eat += 1;
	pthread_mutex_unlock(&p_phil->my_fork);
	pthread_mutex_unlock(&p_phil->next->my_fork);
	message(SLEEP, p_phil, cur_t() - p_phil->start_time);
	my_usleep(p_phil->sleep_time);
	message(THINK, p_phil, cur_t() - p_phil->start_time);
}

void	*daily(void *phil)
{
	t_phil	*p_phil;

	p_phil = (t_phil *)phil;
	if (p_phil->phil_id % 2 == 0)
		my_usleep(200);
	while (p_phil->times_to_eat)
	{
		eating(p_phil);
		if (cur_t() - p_phil->last_eating > p_phil->die_t)
		{
			message(DIE, p_phil, cur_t() - p_phil->start_time);
			pthread_mutex_lock(p_phil->micro);
			p_phil->is_dead = 1;
			break ;
		}
		if (p_phil->times_to_eat != -1)
			p_phil->times_to_eat -= 1;
		if (p_phil->times_to_eat == 0)
		{
			pthread_mutex_lock(p_phil->micro);
			p_phil->has_eat = -1;
			break ;
		}
	}
	return (0);
}
