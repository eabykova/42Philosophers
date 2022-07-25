/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:47:48 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/25 16:16:30 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define ARGS_ERROR "Error in args. You must use positive digit only. Stop\n"
# define FEW_ARGS "Too few arguments. I need more. Stop.\n"
# define MUCH_ARGS "Too much arguments. I need less. Stop.\n"
# define MALLOC_ERROR "Error in malloc. Stop.\n"
# define FORK_ERROR "Error in fork. Stop.\n"
# define CREATE_ERROR "Error in thread creation. Stop.\n"
# define DETACH_ERROR "Error in thread joining. Stop.\n"
# define R_FORK "has taken right fork\n"
# define L_FORK "has taken left fork\n"
# define EAT "is eating\n"
# define PH "philo"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "is died\n"
# define OPEN 202
# define DESTROY 201

typedef struct s_data	t_data;

typedef struct s_phil
{
	int			phil_id;
	int			times_to_eat;
	long		start_time;
	long		eat_time;
	long		sleep_time;
	long		last_eating;
	int			die_time;
	pthread_t	*thread;
	t_data		*data_ptr;
}				t_phil;

typedef struct s_data
{
	int			phil_num;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			dinner_num;
	long		start_time;
	t_phil		*ph;
	int			pid[250];
	sem_t		*fork;
	sem_t		*micro;
}				t_data;

////*		 --the main functions--		*////
void	initialisation(t_data *data);
void	*inspection(void *data);
void	daily(t_phil *p_phil);
void	message(const char *type, t_phil *p_phil, long time);
void	wait_end(t_data *data);

////*		 --utils--		*////
int		ft_atoi(const char *str);
long	cur_t(void);
void	my_usleep(int ms_time);
void	ft_craft_error(char *message, int exit_code);

////*		--newphil--		*////
t_phil	*phil_last(t_phil *lst);
t_phil	*new_phil(t_data *data, int id);
int		ft_lstadd_back(t_phil **lst, t_phil *new);
void	ft_lstclear(t_phil **lst);

#endif