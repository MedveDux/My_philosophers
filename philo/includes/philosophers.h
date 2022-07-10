/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:36:27 by marvin            #+#    #+#             */
/*   Updated: 2022/07/10 15:05:44 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define NC			"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_const_philosophers	t_cp;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_cp			*all;
	pthread_t		pthread;
	long long		last_eat;
	int				n_p;
}	t_philo;

typedef struct s_const_philosophers
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				dead;
	long long int	start_time;
	int				eat;
	t_philo			*all_philo;
	pthread_mutex_t	printf;
	pthread_mutex_t	check;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	*forks;
}	t_cp;

long long	ft_time(void);
void		ft_usleep(int time);
int			ft_my_atoi(const char *str, int *number);
void		printf_error_arguments(void);
int			active(t_cp *cp);
void		*routine(void *all_philo);
int			active2(t_cp *cp);
void		my_printf(t_philo *philo, char *s, int id);
int			init_mutex(t_cp *cp);
int			init_philosophers(t_cp *cp);
void		check(t_cp *cp);
int			insert_value(char *argv, int *philo);
void		my_time(long long time, t_philo *philo);
void		eat_time(t_philo *philo);
int			parser(t_cp *cp, int argc, char **argv);
void		unluck_mutex(t_cp *cp);
void		detach_threads(t_cp *cp);
void		free_all(t_cp *cp);
#endif
