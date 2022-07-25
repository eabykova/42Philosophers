/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:28:48 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/18 10:29:01 by mmicheli         ###   ########.fr       */
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
	if (args[5])
		data->dinner_num = (ft_atoi(args[5]) + 1);
	else
		data->dinner_num = -1;
	return (1);
}

static void	bad_args(int argc)
{
	if (argc < 5)
		printf(FEW_ARGS);
	else
		printf(MUCH_ARGS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (check(&data, argv))
		{
			if (!initialisation(&data))
				ft_lstclear(&data.phil_list);
		}
		else
			printf(ARGS_ERROR);
	}
	else
		bad_args(argc);
	return (0);
}
