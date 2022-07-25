/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:29:31 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/18 10:24:41 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_init(t_data *data)
{
	int		i;
	t_phil	*buf;

	i = -1;
	buf = data->phil_list;
	while (++i < data->phil_num)
	{
		if (!ft_lstadd_back(&buf, new_phil(data, i)))
		{
			printf(MALLOC_ERROR);
			return (0);
		}
	}
	data->phil_list = buf;
	buf = phil_last(data->phil_list);
	buf->next = data->phil_list;
	return (1);
}

static int	threads_init(t_data *data)
{
	int		i;
	t_phil	*buf;

	i = -1;
	buf = data->phil_list;
	while (++i < data->phil_num)
	{
		if (pthread_create(&data->th[i], NULL, daily, buf))
		{
			printf(CREATE_ERROR);
			return (0);
		}
		buf->start_time = data->start_time;
		buf->last_eating = cur_t();
		buf = buf->next;
	}
	return (1);
}

int	initialisation(t_data *data)
{
	int	i;

	data->start_time = cur_t();
	if (pthread_mutex_init(&data->micro, NULL) != 0)
		return (0);
	if (!philo_init(data))
		return (0);
	if (!threads_init(data))
		return (0);
	if (pthread_create(&data->check, NULL, inspection, data->phil_list))
		return (0);
	i = -1;
	while (++i < data->phil_num)
	{
		if (pthread_detach(data->th[i]))
			return (0);
	}
	if (pthread_join(data->check, NULL))
		return (0);
	pthread_mutex_destroy(&data->micro);
	return (1);
}
