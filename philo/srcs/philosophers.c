/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:07:45 by marvin            #+#    #+#             */
/*   Updated: 2022/06/30 20:09:39 by cyelena          ###   ########.fr       */
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
}
void	init_mutex(t_cp *cp)
{
	pthread_mutex_t *mutex;
	int				i;

	i = cp->num_philo;
	mutex = malloc (sizeof(mutex) * cp->num_philo);
	while(i--)
		pthread_mutex_init(&mutex[i], NULL);
	pthread_mutex_init(&cp->printf, NULL)
	cp->forks = mutex;
}

void	init_philosophers(t_cp *cp)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * cp->num_philo);
	i = 0;
	while (i < cp->num_philo)
	{
		philo[i].id = i;
		philo[i].right = &cp->forks[philo[i].id];
		philo[i].left = &cp->forks[(philo[i].id + 1) % cp->num_philo];
		i++;
	}
	cp->all_philo = philo;
}

void	*routine(void *all_philo)
{
	t_philo	*philo;
	
	philo = (t_philo *)all_philo;
	philo->start_time = ft_time();
}

void	init_pthreads(t_cp *cp)
{
	pthread_t	*threads;
	int			i;

	i = cp->num_philo;
	threads = malloc(sizeof(pthread_t) * cp->num_philo);
	while (i--)
		pthread_create(&treads[i], NULL, routine, (void *)&cp->all_philo[i]);
}

int	main(int argc, char **argv)
{
	t_cp	cp;

	if (parser(&cp, argc, argv))
		return (EXIT_FAILURE);
	printf("%d", cp.time_sleep);
	printf("%d", cp.must_eat);
	if (cp.must_eat == 0 || cp.num_philo == 0)
	{
		printf("eat and philo value must be >=1\n");
		return (EXIT_FAILURE);
	}
	init_mutex(&cp);
	init_philosophers(&cp);
	init_pthreads(&cp);
}








long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	long	tmp_time;

	tmp_time = ft_time();
	usleep(time * 920);
	while (ft_time() < time + tmp_time)
		usleep (time * 3);
}