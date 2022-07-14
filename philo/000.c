/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:43:25 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/04 18:45:20 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (check(&data, argv))
		{
			printf("All is good\n");
			if (!init(&data))
				printf(MALLOC_ERROR);
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
