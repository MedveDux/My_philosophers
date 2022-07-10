/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:47:42 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/10 15:03:25 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	active(t_cp *cp)
{
	int	i;

	i = 0;
	cp->start_time = ft_time();
	while (i < cp->num_philo)
	{
		pthread_create(&cp->all_philo[i].pthread, NULL, \
			routine, (void *)&cp->all_philo[i]);
		i += 2;
	}
	usleep(300);
	return (active2(cp));
}

void	*routine(void *all_philo)
{
	t_philo	*philo;

	philo = (t_philo *)all_philo;
	pthread_mutex_lock(&philo->all->mutex_dead);
	while (philo->n_p && philo->all->dead != 1)
	{
		pthread_mutex_unlock(&philo->all->mutex_dead);
		eat_time(philo);
		my_printf(philo, "is sleeping", philo->id);
		my_time(philo->all->time_sleep, philo);
		my_printf(philo, "is thinking", philo->id);
		pthread_mutex_lock(&philo->all->check);
		if (philo->n_p > 0)
			philo->n_p--;
		if (philo->n_p == 0)
			philo->all->eat++;
		pthread_mutex_unlock(&philo->all->check);
		pthread_mutex_lock(&philo->all->mutex_dead);
	}
	pthread_mutex_unlock(&philo->all->mutex_dead);
	return (0);
}

int	active2(t_cp *cp)
{
	int	i;

	i = 1;
	while (i < cp->num_philo)
	{
		pthread_create(&cp->all_philo[i].pthread, NULL, \
			routine, (void *)&cp->all_philo[i]);
		i += 2;
	}
	return (0);
}

void	my_printf(t_philo *philo, char *s, int id)
{
	pthread_mutex_lock(&philo->all->printf);
	pthread_mutex_lock(&philo->all->mutex_dead);
	if (!(philo->all->dead))
		printf("%lld %d %s\n", ft_time() - philo->all->start_time, id + 1, s);
	pthread_mutex_unlock(&philo->all->mutex_dead);
	pthread_mutex_unlock(&philo->all->printf);
}

void	check(t_cp *cp)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == cp->num_philo)
			i = 0;
		pthread_mutex_lock(&cp->check);
		if ((ft_time() - cp->all_philo[i].last_eat - cp->start_time) \
		> cp->time_die && (cp->all_philo[i].n_p != 0))
		{
			pthread_mutex_lock(&cp->mutex_dead);
			cp->dead = 1;
			pthread_mutex_unlock(&cp->mutex_dead);
			printf("%lli %i died", ft_time() - cp->start_time, \
			cp->all_philo->id + 1);
			pthread_mutex_unlock(&cp->check);
			break ;
		}
		if (cp->eat == cp->num_philo)
			break ;
		pthread_mutex_unlock(&cp->check);
		i++;
	}
}
