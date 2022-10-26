/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:07:01 by niespana          #+#    #+#             */
/*   Updated: 2022/09/01 13:07:03 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			signe;
	long		res;

	res = 0;
	signe = 1;
	while (*str != '\0')
	{
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		if (*str == '-')
			signe = -1;
		if (*str == '+' || *str == '-')
			str++;
		while (*str >= '0' && *str <= '9')
		{
			res = (10 * res) + ((*str++) - 48);
			if (signe == 1 && res > 2147483647)
				return (-1);
			if (signe == -1 && res > 2147483648)
				return (0);
		}
		while (*str != '\0')
			str++;
	}
	return ((int)(res * signe));
}

long int	current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
