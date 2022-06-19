/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:07:45 by marvin            #+#    #+#             */
/*   Updated: 2022/06/18 15:07:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	insert_value(char *args, int *philo)
{
	int	error;

	error = 0;
	if (!args || !*args)
		return (EXIT_FAILURE);
	else
		return(ft_my_atoi(args, &philo));
}

int parser(t_philo *philo, int argc, char *aargv)
{
	if (argc == 5)
	{
		(*philo).must_eat = -1;
		return (insert_value(args[1], &((*philo).num_philo)) &&\
				insert_value(args[2], &((*philo).time_die)) &&\
				insert_value(args[3], &((*philo).time_eat)) &&\
				insert_value(args[4], &((*philo).time_sleep)));
	}
	else if (argc == 6)
	{
		return (insert_value(args[1], &((*philo).num_philo)) &&\
				insert_value(args[2], &((*philo).time_die)) &&\
				insert_value(args[3], &((*philo).time_eat)) &&\
				insert_value(args[3], &((*philo).must_eat)) &&\
				insert_value(args[4], &((*philo).time_sleep)));
	}
	else
	{
		ft_putstr_fd("wrong number of arguments\n", 2);
		return (EXIT_FAILURE)
	}

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

int main(int argc, char *argv)
{
	t_philo philo;
	if (!parser(&philo, argc, argv))
		return (EXIT_FAILURE);
	if (philo.must_eat == 0 || philo.num_philo == 0)
	{
		ft_putstr_fd("eat and philo value must be >=1\n", 2);
		return(EXIT_FAILURE);
	}
		
}