/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelena <cyelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:57:57 by cyelena           #+#    #+#             */
/*   Updated: 2022/07/10 14:46:12 by cyelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
