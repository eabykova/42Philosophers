/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:23:45 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/25 16:31:42 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*inspection(void *phil)
{
	t_phil	*p_phil;

	p_phil = (t_phil *)phil;
	while (1)
	{
		if (cur_t() > (p_phil->last_eating + p_phil->die_time))
		{
			sem_wait(p_phil->data_ptr->micro);
			printf("%ld %s_%d %s", cur_t() - p_phil->start_time, PH, \
				p_phil->phil_id, DIE);
			exit (0);
		}
		my_usleep(5);
	}
	return (0);
}
