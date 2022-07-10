/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:07:45 by marvin            #+#    #+#             */
/*   Updated: 2022/07/10 15:03:01 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	parser(t_cp *cp, int argc, char **argv)
{
	cp->dead = 0;
	if (argc == 5)
	{
		(*cp).must_eat = -1;
		if (insert_value(argv[1], &(cp->num_philo)) || \
				insert_value(argv[2], &(cp->time_die)) || \
				insert_value(argv[3], &(cp->time_eat)) || \
				insert_value(argv[4], &(cp->time_sleep)))
			return (EXIT_FAILURE);
	}
	else if (argc == 6)
	{
		if (insert_value(argv[1], &(cp->num_philo)) || \
				insert_value(argv[2], &(cp->time_die)) || \
				insert_value(argv[3], &(cp->time_eat)) || \
				insert_value(argv[4], &(cp->time_sleep)) || \
				insert_value(argv[5], &(cp->must_eat)))
			return (EXIT_FAILURE);
	}
	else
	{
		printf_error_arguments();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	unluck_mutex(t_cp *cp)
{
	int	i;

	i = cp->num_philo;
	while (i--)
	{
		pthread_mutex_unlock(&cp->forks[i]);
		pthread_mutex_destroy(&cp->forks[i]);
	}
	pthread_mutex_unlock(&cp->printf);
	pthread_mutex_destroy(&cp->printf);
	pthread_mutex_unlock(&cp->check);
	pthread_mutex_destroy(&cp->check);
}

void	detach_threads(t_cp *cp)
{
	int	i;

	i = cp->num_philo;
	while (i--)
		pthread_join(cp->all_philo[i].pthread, NULL);
}

void	free_all(t_cp *cp)
{
	free(cp->all_philo);
	free(cp->forks);
}

int	main(int argc, char **argv)
{
	t_cp	cp;

	if (parser(&cp, argc, argv))
		return (EXIT_FAILURE);
	if (cp.must_eat == 0 || cp.num_philo == 0)
	{
		printf("eat and philo value must be >=1\n");
		return (EXIT_FAILURE);
	}
	if (cp.num_philo == 1)
	{
		printf("%d 1 has taken a fork\n", 0);
		usleep(cp.time_die);
		printf("%d 1 diad", cp.time_die + 1);
		exit(0);
	}
	if (init_mutex(&cp) || init_philosophers(&cp))
		return (EXIT_FAILURE);
	active(&cp);
	check(&cp);
	detach_threads(&cp);
	unluck_mutex(&cp);
	free_all(&cp);
	return (0);
}
