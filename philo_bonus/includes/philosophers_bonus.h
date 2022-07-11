/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:14:20 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/11 18:52:43 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

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
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_const_philosophers	t_cp;

typedef struct s_philo
{
	int				id;
	long long		last_eat;
	pid_t			pid;
	pthread_t		pthread;
	t_cp			*all;
}	t_philo;

typedef struct s_const_philosophers
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long int	start_time;
	t_philo			*all_philo;
	sem_t			*forks;
	sem_t			*my_printf;
	sem_t			*died;
}	t_cp;

long long	ft_time(void);
void		ft_usleep(int time);
int			ft_my_atoi(const char *str, int *number);
void		printf_error_arguments(void);
int			insert_value(char *argv, int *philo);
void		init_sems(t_cp *cp);
int			init_philosophers(t_cp *cp);
int			create_process(t_cp *cp);
void		*routine(void *one);
void		eat(t_philo *philo, t_cp *cp);
void		ft_printing(t_cp *cp, char *s, int id);
void		check(t_philo *philo);
void		sem_cl(t_cp *cp);
void		ft_kill(t_cp *cp);
int			parser(t_cp *cp, int argc, char **argv);
#endif