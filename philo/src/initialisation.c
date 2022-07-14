/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:29:31 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/13 20:22:45 by mmicheli         ###   ########.fr       */
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

static int	odd_init(t_data *data)
{
	int		i;
	t_phil	*buf;

	i = 1;
	buf = data->phil_list->next;
	printf("odd\n");
	while (i < data->phil_num)
	{
		printf("philo_%d is alive\n", buf->phil_id);
		if (pthread_create(&data->th[i], NULL, daily, buf))
		{
			printf(CREATE_ERROR);
			return (0);
		}
		i += 2;
		buf->start_time = cur_t();
		buf = buf->next->next;
	}
//	i = 1;
//	while (i < data->phil_num)
//	{
//		pthread_detach(data->th[i]);
//		i += 2;
//	}
	return (1);
}

static int	even_init(t_data *data)
{
	int		i;
	t_phil	*buf;

	i = 0;
	buf = data->phil_list;
	printf("even\n");
	while (i < data->phil_num)
	{
		printf("philo_%d is alive\n", buf->phil_id);
		if (pthread_create(&data->th[i], NULL, daily, buf))
		{
			printf(CREATE_ERROR);
			return (0);
		}
		i += 2;
		buf->start_time = cur_t();
		buf = buf->next->next;
	}
//	i = 0;
//	while (i < data->phil_num)
//	{
//		pthread_detach(data->th[i]);
//		i += 2;
//	}
	return (1);
}

int	initialisation(t_data *data)
{
//	if (pthread_create(&data->check, NULL, inspection, data))
//		return (0);
	if (!philo_init(data))
		return (0);
	if (pthread_mutex_init(&data->micro, NULL) != 0)
		return (0);
	odd_init(data);
	my_usleep(100);
	even_init(data);
//	sleep(5);
	return (1);
}
