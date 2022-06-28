/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:07:45 by marvin            #+#    #+#             */
/*   Updated: 2022/06/28 19:59:20 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	insert_value(char *argv, int *philo)
{
	int	error;

	error = 0;
	if (!argv || !*argv)
		return (EXIT_FAILURE);
	else
		if (ft_my_atoi(argv, &philo) >= 0)
			return(ft_my_atoi(argv, &philo));
	return (EXIT_FAILURE);	
}

int parser(t_philo *philo, int argc, char **argv)
{
	if (argc == 5)
	{
		(*philo).must_eat = -1;
		return (insert_value(argv[1], &((*philo).num_philo)) &&\
				insert_value(argv[2], &((*philo).time_die)) &&\
				insert_value(argv[3], &((*philo).time_eat)) &&\
				insert_value(argv[4], &((*philo).time_sleep)));
	}
	else if (argc == 6)
	{
		return (insert_value(argv[1], &((*philo).num_philo)) &&\
				insert_value(argv[2], &((*philo).time_die)) &&\
				insert_value(argv[3], &((*philo).time_eat)) &&\
				insert_value(argv[3], &((*philo).must_eat)) &&\
				insert_value(argv[4], &((*philo).time_sleep)));
	}
	else
	{
		printf_error_arguments();
		return (EXIT_FAILURE)
	}

}

void printf_error_arguments(void)
{
	printf("_____________________________");
	printf("Please enter 4 or 5 arguments");
	printf("_____________________________");
	printf("[1][Number of philosophers]");
	printf("[2][Time to die]");
	printf("[3][Time to eat]");
	printf("[4][Time to sleep]");
	printf("[5][Number of must eat]");
	printf("_____________________________");	
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

int main(int argc, char **argv)
{
	t_const philo;
	
	if (!parser(&philo, argc, argv))
		return (EXIT_FAILURE);
		
	if (philo.must_eat == 0 || philo.num_philo == 0)
	{
		ft_putstr_fd("eat and philo value must be >=1\n", 2);
		return(EXIT_FAILURE);
	}
		
}

long	ft_time(void)
{
	struct timeval	time;
	long			res;
	
	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);	
}

void ft_usleep(int time)
{
	long tmp_time;
	tmp_time = ft_time();
	while (ft_time() < time + tmp_time)
	{
		usleep (1);
	}
}