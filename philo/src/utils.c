/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:45:32 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/04 17:16:15 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_pos_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);//if threre is no digit
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	val;
	unsigned long	i;

	if (!ft_pos_num((char *)str))
		return (-1);
	val = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		val *= 10;
		val += (str[i] - '0');
		i++;
	}
	return ((int)val);
}

long	cur_t(void)
{
	long			ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	my_usleep(int ms_time)
{
	long	start;

	start = cur_t();
	usleep(ms_time * 900);
	while ((ms_time + start) > cur_t())
		usleep(250);
}
