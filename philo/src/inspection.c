/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:36:37 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/16 17:26:26 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*inspection(void *phil_list)
{
	t_phil	*p_phil;

	p_phil = (t_phil *)phil_list;
	while (1)
	{
		if (cur_t() > (p_phil->last_eating + p_phil->die_t))
		{
			pthread_mutex_lock(p_phil->micro);
			printf("%ld %s_%d %s", cur_t() - p_phil->start_time, PH, \
				p_phil->phil_id, DIE);
			p_phil->is_dead = 1;
			break ;
		}
		if (p_phil->is_dead == 1)
			break ;
		if (p_phil->has_eat == -1)
			break ;
		p_phil = p_phil->next;
	}
	return (0);
}
