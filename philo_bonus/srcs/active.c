/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:45:22 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/11 18:49:27 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	check(t_philo *philo)
{
	while (philo->all->must_eat)
	{
		sem_wait(philo->all->died);
		if ((ft_time() - philo->last_eat - philo->all->start_time) \
		> philo->all->time_die)
		{
			sem_wait(philo->all->my_printf);
			printf("%lld %d died\n", ft_time() - philo->all->start_time, \
			philo->id);
			exit (1);
		}
		sem_post(philo->all->died);
	}
	exit (0);
}

void	ft_printing(t_cp *cp, char *s, int id)
{
	sem_wait(cp->my_printf);
	printf("%lld %d %s\n", ft_time() - cp->start_time, id, s);
	sem_post(cp->my_printf);
}

void	eat(t_philo *philo, t_cp *cp)
{
	sem_wait(cp->forks);
	ft_printing(cp, "has taken a fork", philo->id);
	sem_wait(cp->forks);
	ft_printing(cp, "has taken a fork", philo->id);
	sem_wait(cp->died);
	ft_printing(cp, "is eating", philo->id);
	philo->last_eat = ft_time() - cp->start_time;
	sem_post(cp->died);
	ft_usleep(cp->time_eat);
	sem_post(cp->forks);
	sem_post(cp->forks);
}

void	*routine(void *one)
{
	t_cp	*cp;
	t_philo	*philo;

	philo = (t_philo *)one;
	cp = philo->all;
	while (cp->must_eat)
	{
		eat(philo, cp);
		ft_printing(cp, "is sleeping", philo->id);
		ft_usleep(cp->time_sleep);
		ft_printing(cp, "is thinking", philo->id);
		if (cp->must_eat > 0)
			cp->must_eat--;
	}
	return (0);
}

int	create_process(t_cp *cp)
{
	int	i;

	cp->start_time = ft_time();
	i = -1;
	while (++i < cp->num_philo)
	{
		cp->all_philo[i].pid = fork();
		if (cp->all_philo[i].pid == 0)
		{
			if (cp->all_philo[i].id % 2 == 0)
				ft_usleep(200);
			if (pthread_create(&cp->all_philo[i].pthread, NULL, \
			routine, &cp->all_philo[i]))
				return (EXIT_FAILURE);
			pthread_detach(cp->all_philo[i].pthread);
			ft_usleep(200);
			check(&cp->all_philo[i]);
		}
	}
	return (0);
}
