/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:12:36 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/11 18:52:08 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	parser(t_cp *cp, int argc, char **argv)
{
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

void	ft_kill(t_cp *cp)
{
	int	pid;
	int	i;

	i = -1;
	while (++i < cp->num_philo)
	{
		waitpid(-1, &pid, 0);
		if (pid)
		{
			i = -1;
			while (++i < cp->num_philo)
				kill(cp->all_philo[i].pid, 9);
			break ;
		}
	}
	free(cp->all_philo);
	sem_close(cp->died);
	sem_close(cp->my_printf);
	sem_close(cp->forks);
	sem_unlink("died");
	sem_unlink("my_printf");
	sem_unlink("fork");
}

void	sem_cl(t_cp *cp)
{
	sem_close(cp->died);
	sem_close(cp->my_printf);
	sem_close(cp->forks);
	sem_unlink("died");
	sem_unlink("my_printf");
	sem_unlink("fork");
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
	init_sems(&cp);
	if (init_philosophers(&cp))
		return (EXIT_FAILURE);
	if (create_process(&cp))
	{
		free(cp.all_philo);
		printf(RED"Error"NC);
		sem_cl(&cp);
		return (EXIT_FAILURE);
	}
	ft_kill(&cp);
	return (0);
}
