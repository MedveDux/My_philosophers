/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:50:13 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/10 15:00:31 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutex(t_cp *cp)
{
	int	i;

	i = cp->num_philo;
	cp->forks = malloc (sizeof(pthread_mutex_t) * cp->num_philo);
	while (i--)
	{
		if (pthread_mutex_init(&cp->forks[i], NULL))
		{
			free(cp->forks);
			printf("Error: mutex_init did not work\n");
			return (1);
		}
	}
	pthread_mutex_init(&cp->printf, NULL);
	pthread_mutex_init(&cp->check, NULL);
	pthread_mutex_init(&cp->mutex_dead, NULL);
	return (0);
}

int	init_philosophers(t_cp *cp)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * cp->num_philo);
	if (!philo)
	{
		printf("Error: malloc error");
		return (1);
	}
	i = 0;
	cp->eat = 0;
	while (i < cp->num_philo)
	{
		philo[i].n_p = cp->must_eat;
		philo[i].id = i;
		philo[i].right = &cp->forks[philo[i].id];
		philo[i].left = &cp->forks[(philo[i].id + 1) % cp->num_philo];
		philo[i].all = cp;
		i++;
	}
	cp->all_philo = philo;
	return (0);
}

int	insert_value(char *argv, int *philo)
{
	int	error;

	error = 0;
	if (!argv || !*argv)
		return (EXIT_FAILURE);
	else
	{
		if (ft_my_atoi(argv, philo) == 1)
		{
			printf(RED"Error: value must be >= 0\n"NC);
			return (EXIT_FAILURE);
		}
		if (*philo >= 0)
			return (EXIT_SUCCESS);
		printf(RED"value must be >= 0\n"NC);
	}
	return (EXIT_FAILURE);
}
