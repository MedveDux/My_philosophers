/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:47:27 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/11 18:48:23 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

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

void	init_sems(t_cp *cp)
{
	sem_close(cp->died);
	sem_close(cp->my_printf);
	sem_close(cp->forks);
	sem_unlink("died");
	sem_unlink("my_printf");
	sem_unlink("forks");
	cp->died = sem_open("died", O_CREAT, 0777, 1);
	cp->my_printf = sem_open("my_printf", O_CREAT, 0777, 1);
	cp->forks = sem_open("forks", O_CREAT, 0777, cp->num_philo);
}

int	init_philosophers(t_cp *cp)
{
	int	i;

	i = -1;
	cp->all_philo = malloc(sizeof(t_philo) * cp->num_philo);
	if (!cp->all_philo)
		return (EXIT_FAILURE);
	while (++i < cp->num_philo)
	{
		cp->all_philo[i].all = cp;
		cp->all_philo[i].id = i + 1;
		cp->all_philo[i].last_eat = 0;
	}
	return (0);
}
