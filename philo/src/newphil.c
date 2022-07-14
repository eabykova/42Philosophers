/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newphil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:06:14 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/10 19:29:46 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_phil	*phil_last(t_phil *lst)
{
	t_phil	*buf;

	buf = lst;
	if (buf)
		while (buf->next)
			buf = buf->next;
	return (buf);
}

t_phil	*new_phil(t_data *data, int id)
{
	t_phil	*new;

	new = malloc(sizeof(t_phil));
	if (new)
	{
		new->phil_id = id;
		new->times_to_eat = data->dinner_num;
		new->last_eating = 0;
		new->eat_time = data->eat_time;
		new->sleep_time = data->sleep_time;
		new->die_t = data->die_time;
		new->micro = &data->micro;
		new->next = NULL;
		if (pthread_mutex_init(&new->my_fork, NULL))
		{
			printf(MUTEX_ERROR);
			return (0);
		}
	}
	return (new);
}

int	ft_lstadd_back(t_phil **lst, t_phil *new)
{
	t_phil	*buf;

	if (new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			buf = phil_last(*(lst));
			buf->next = new;
		}
		if (!*lst)
			return (0);
	}
	return (1);
}
