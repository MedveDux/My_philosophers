/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:52:18 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/10 15:06:08 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	my_time(long long time, t_philo *philo)
{
	long long	buf;

	(void)philo;
	buf = ft_time();
	while (ft_time() - buf < time)
		usleep (1);
}

void	eat_time(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	my_printf(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->left);
	my_printf(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(&philo->all->check);
	philo->last_eat = ft_time() - philo->all->start_time;
	pthread_mutex_unlock(&philo->all->check);
	my_printf(philo, "is eating", philo->id);
	my_time(philo->all->time_eat, philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}
