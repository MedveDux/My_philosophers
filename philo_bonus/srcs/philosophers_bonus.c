/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:12:36 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/11 16:59:11 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	long	tmp_time;

	tmp_time = ft_time();
	while (ft_time() < time + tmp_time)
		usleep (100);
}

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

void	printf_error_arguments(void)
{
	printf(RED"_____________________________\n"NC);
	printf(RED"Please enter 4 or 5 arguments\n"NC);
	printf(RED"_____________________________\n"NC);
	printf(RED"[1][Number of philosophers]\n"NC);
	printf(RED"[2][Time to die]\n"NC);
	printf(RED"[3][Time to eat]\n"NC);
	printf(RED"[4][Time to sleep]\n"NC);
	printf(RED"[5][Number of must eat]\n"NC);
	printf(RED"_____________________________\n"NC);
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

void	init_sems(t_cp *cp)
{
	sem_close(cp->died);
	sem_close(cp->my_printf);
	sem_close(cp->forks);
	sem_unlink("died");
	sem_unlink("my_printf");
	sem_unlink("fork");
	cp->died = sem_open("died", O_CREAT, 0777, 1);
	cp->my_printf = sem_open("my_printf", O_CREAT, 0777, 1);
	cp->forks = sem_open("my_printf", O_CREAT, 0777, cp->num_philo);
}

int init_philosophers(t_cp *cp)
{
	int	i;

	i = 0;
	cp->all_philo = malloc(sizeof(t_philo) * cp->num_philo);
	if (!cp->all_philo)
		return (EXIT_FAILURE);
	while (i++ < cp->num_philo)
	{
		cp->all_philo[i].all = cp;
		cp->all_philo[i].id = i;
		cp->all_philo[i].last_eat = 0;
	}
	return (0);
}

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

void	printing(t_cp *cp, char *s, int id)
{
	sem_wait(cp->my_printf);
	printf("%lld %d %s\n", ft_time() - cp->start_time, id, s);
	sem_post(cp->my_printf);
}

void	eat(t_philo *philo, t_cp *cp)
{
	sem_wait(cp->forks);
	printing(cp, "has taken a fork", philo->id);
	sew_wait(cp->forks);
	printing(cp, "has taken a fork", philo->id);
	sem_wait(philo->all->died);
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
		printing(cp, "is sleeping", philo->id);
		ft_usleep(cp->time_sleep);
		printing(cp, "is thinking", philo->id);
		if (cp->must_eat > 0)
			cp->must_eat--;
	}
	return (0);
}

int create_process(t_cp *cp)
{
	int	i;

	cp->start_time = ft_time();
	i = -1;
	while (++i < cp->num_philo)
	{
		cp->all_philo[i].pid = fork();
		if (cp->all_philo[i].pid == 0)
		{
			if (cp->all_philo[i].pid %2 == 0)
				ft_usleep(10);
			if (pthread_create(&cp->all_philo[i].pthread, NULL, \
			routine, &cp->all_philo[i]))
				return(EXIT_FAILURE);
			pthread_detach(cp->all_philo[i].pthread);
			ft_usleep(10);
			check(&cp->all_philo[i]);
		}
	}
	return (0);
}
void ft_kill(t_cp *cp)
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
			{
				kill(cp->all_philo[i].pid, 9);
				break ;
			}
		}
	}
	free(cp->all_philo);
	printf("Error: pid");
	
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
		return (EXIT_FAILURE);
	}

	ft_kill(&cp);
	return (0);
}
