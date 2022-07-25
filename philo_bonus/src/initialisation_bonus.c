/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:31:28 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/25 16:16:58 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	sems_init(t_data *data, int flag)
{
	if (flag == OPEN)
	{
		sem_unlink("fork");
		sem_unlink("micro");
		data->fork = sem_open("fork", O_CREAT, 666, data->phil_num);
		data->micro = sem_open("micro", O_CREAT, 666, 1);
	}
	if (flag == DESTROY)
	{
		sem_close(data->fork);
		sem_close(data->micro);
		sem_unlink("fork");
		sem_unlink("micro");
	}
}

static void	process_init(t_data *data, int i)
{
	data->ph[i].phil_id = i;
	data->ph[i].eat_time = data->eat_time;
	data->ph[i].sleep_time = data->sleep_time;
	data->ph[i].die_time = data->die_time;
	data->ph[i].start_time = data->start_time;
	data->ph[i].last_eating = data->start_time;
	data->ph[i].data_ptr = data;
	data->ph[i].times_to_eat = data->dinner_num;
}

void	initialisation(t_data *data)
{
	int	i;

	sems_init(data, OPEN);
	data->ph = (t_phil *)malloc(sizeof(t_phil) * data->phil_num);
	if (!data->ph)
		ft_craft_error(MALLOC_ERROR, 1);
	data->start_time = cur_t();
	i = -1;
	while (++i < data->phil_num)
		process_init(data, i);
	i = -1;
	while (++i < data->phil_num)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			daily(&data->ph[i]);
	}
	wait(0);
	i = -1;
	while (++i < data->phil_num)
		kill(data->pid[i], SIGTERM);
	sems_init(data, DESTROY);
}
