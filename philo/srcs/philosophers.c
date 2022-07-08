/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:07:45 by marvin            #+#    #+#             */
/*   Updated: 2022/07/08 19:47:53 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_my_atoi(const char *str, int *number)
{
	unsigned long	res;
	int				negative;

	negative = 1;
	res = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		++str;
	}
	if (!*str)
		return (EXIT_FAILURE);
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((res > (unsigned int)(-1) / 2 && negative == 1)
			|| (res > ((unsigned int)(-1) / 2 + 1) && negative == -1))
			return (-1);
		++str;
	}
	if (*str)
		return (EXIT_FAILURE);
	*number = ((int)res) * negative;
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
		ft_my_atoi(argv, philo);
		if (*philo >= 0)
			return (EXIT_SUCCESS);
		printf("value must be >= 0\n");
	}
	return (EXIT_FAILURE);
}

void	printf_error_arguments(void)
{
	printf("_____________________________\n");
	printf("Please enter 4 or 5 arguments\n");
	printf("_____________________________\n");
	printf("[1][Number of philosophers]\n");
	printf("[2][Time to die]\n");
	printf("[3][Time to eat]\n");
	printf("[4][Time to sleep]\n");
	printf("[5][Number of must eat]\n");
	printf("_____________________________\n");
}

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

int	init_mutex(t_cp *cp)
{
	// pthread_mutex_t	*mutex;
	int				i;

	i = cp->num_philo;
	cp->forks = malloc (sizeof(pthread_mutex_t) * cp->num_philo);
	// if (!mutex)
	// {
	// 	printf("Error: mutex_init did not work\n");
	// 	return (1);
	// }
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
	// cp->forks = mutex;
	return (0);
}

int	init_philosophers(t_cp *cp)
{
	int		i;
	t_philo	*philo;

	// write(1, "55", 2);
	philo = malloc(sizeof(t_philo) * cp->num_philo);
	if (!philo)
		return (1);//
	// write(1, "55", 2);
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
void unluck_mutex(t_cp *cp)
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

void detach_threads(t_cp *cp)
{
	int	i;

	i = cp->num_philo;
	while (i--)
		pthread_join(cp->all_philo[i].pthread, NULL);
}

void my_printf(t_philo *philo, char *s, int id)
{
	pthread_mutex_lock(&philo->all->printf);
	pthread_mutex_lock(&philo->all->mutex_dead);
	if (!(philo->all->dead))
		printf("%lld %d %s\n", ft_time() - philo->all->start_time, id + 1, s);
	pthread_mutex_unlock(&philo->all->mutex_dead);
	pthread_mutex_unlock(&philo->all->printf);
}

void my_time(long long time, t_philo *philo)
{
	long long	buf;

	buf = ft_time();
	while (ft_time() - buf < time)
		usleep (1);
}
 
void eat_time(t_philo *philo)
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

void	*routine(void *all_philo)
{
	t_philo	*philo;

	philo = (t_philo *)all_philo;
	pthread_mutex_lock(&philo->all->mutex_dead);
	while (philo->n_p && philo->all->dead != 1)//
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
		// {
		// 	unluck_mutex (cp);
		// 	end_threads(cp);
		// 	printf("Error: A stream was not created");
		// 	return (EXIT_FAILURE);
		// }
		i += 2;
	}
	return (0);
}

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
void	free_all(t_cp *cp)
{
	free(cp->all_philo);
	free(cp->forks);
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
		printf("%d 1 diad", cp.time_die + 1);//
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








