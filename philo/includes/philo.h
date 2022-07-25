/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicheli <mmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:28:25 by mmicheli          #+#    #+#             */
/*   Updated: 2022/07/25 15:52:51 by mmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define ARGS_ERROR "Error in args. You must use positive digit only. Stop\n"
# define FEW_ARGS "Too few arguments. I need more. Stop.\n"
# define MUCH_ARGS "Too much arguments. I need less. Stop.\n"
# define MALLOC_ERROR "Error in malloc. Stop.\n"
# define MUTEX_ERROR "Error in mutex. Stop.\n"
# define CREATE_ERROR "Error in thread creation. Stop.\n"
# define JOIN_ERROR "Error in thread joining. Stop.\n"
# define R_FORK "has taken right fork\n"
# define L_FORK "has taken left fork\n"
# define EAT "is eating\n"
# define PH "philo"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "is died\n"

typedef struct s_phil
{
	pthread_t			*phil;
	int					phil_id;
	int					times_to_eat;
	long				start_time;
	long				eat_time;
	long				sleep_time;
	long				last_eating;
	int					die_t;
	int					is_dead;
	int					has_eat;
	struct s_phil		*next;
	pthread_mutex_t		*micro;
	pthread_mutex_t		my_fork;
}				t_phil;

typedef struct s_data
{
	int				phil_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				dinner_num;
	long			start_time;
	pthread_mutex_t	micro;
	pthread_t		check;
	pthread_t		th[250];
	struct s_phil	*phil_list;
}				t_data;

////*		 --the main functions--		*////
int		initialisation(t_data *data);
void	*inspection(void *data);
void	*daily(void *phil);
void	message(const char *type, t_phil *p_phil, long time);

////*		 --utils--		*////
int		ft_atoi(const char *str);
long	cur_t(void);
void	my_usleep(int ms_time);

////*		--newphil--		*////
t_phil	*phil_last(t_phil *lst);
t_phil	*new_phil(t_data *data, int id);
int		ft_lstadd_back(t_phil **lst, t_phil *new);
void	ft_lstclear(t_phil **lst);

#endif