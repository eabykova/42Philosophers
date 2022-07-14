/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:31:20 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/13 19:47:09 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

static int	check(t_data *data, char **args)
{
	data->phil_num = ft_atoi(args[1]);
	data->die_time = ft_atoi(args[2]);
	data->eat_time = ft_atoi(args[3]);
	data->sleep_time = ft_atoi(args[4]);
	if (args[5])
		data->dinner_num = ft_atoi(args[5]);
	else
		data->dinner_num = 0;
	if (data->phil_num < 1 || data->die_time == -1 || data->eat_time == -1 \
		|| data->sleep_time == -1 || data->dinner_num == -1)
		return (0);
	return (1);
}

//void	bad_args()

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (check(&data, argv))
		{
			if (!initialisation(&data))
			{
				//clear all
			}
			sleep(5);

//pthread_//			t_phil *tmp = data.phil_list;
//			int i = -1;
//			while (tmp && ++i < data.phil_num)
//			{
//				printf("phil id: %d, my_fork: %p, left_fork: %p\n",
//					   tmp->phil_id, &tmp->my_fork, &tmp->next->my_fork);
//				tmp = tmp->next;
//			}
//			daily(&data);
		}
		else
			printf(ARGS_ERROR);
	}
	else
	{
		if (argc < 5)
			printf(FEW_ARGS);
		else
			printf(MUCH_ARGS);
	}
	return (0);
}
