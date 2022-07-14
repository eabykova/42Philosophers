/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:40:33 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/13 20:11:55 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	message(const char *type, t_phil *p_phil, long time)
{
	pthread_mutex_lock(p_phil->micro);
	printf("%ld %s_%d %s", time, PH, p_phil->phil_id, type);
	pthread_mutex_unlock(p_phil->micro);
}

void	*daily(void *phil)
{
	t_phil	*p_phil;

	p_phil = (t_phil *)phil;
	while (1)
	{
//		sleep(1);
		printf("%ld philo_%d into daily\n", cur_t() - p_phil->start_time,
			   p_phil->phil_id);
		pthread_mutex_lock(&p_phil->my_fork);
		message(R_FORK, p_phil, cur_t() - p_phil->start_time);
		pthread_mutex_lock(&p_phil->next->my_fork);
		message(L_FORK, p_phil, cur_t() - p_phil->start_time);
		message(EAT, p_phil, cur_t() - p_phil->start_time);
		p_phil->eat_time = cur_t();
		my_usleep(p_phil->eat_time);
		pthread_mutex_unlock(&p_phil->my_fork);
		pthread_mutex_unlock(&p_phil->next->my_fork);
		message(SLEEP, p_phil, cur_t() - p_phil->start_time);
		my_usleep(p_phil->sleep_time);
		message(THINK, p_phil, cur_t() - p_phil->start_time);
		if (cur_t() - p_phil->eat_time > p_phil->die_t)
		{
			message(DIE, p_phil, cur_t() - p_phil->start_time);
			pthread_mutex_lock(p_phil->micro);
			break ;
		}
	}
	return (0);
}
