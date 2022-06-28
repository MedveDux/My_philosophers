/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:36:27 by marvin            #+#    #+#             */
/*   Updated: 2022/06/28 19:56:03 by cyelena          ###   ########.fr       */
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
# include "../libft/libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_const
{
	int			num_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;
	long long	begin_time;
}	t_const;

typedef struct s_philosophers
{
	t_const	*philo;
	pthread_mutex_t printf;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

#endif
