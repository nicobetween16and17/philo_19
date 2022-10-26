/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:06:44 by niespana          #+#    #+#             */
/*   Updated: 2022/09/01 13:06:48 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_philosopher *philo)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * philo[0].n_max);
	if (!forks)
		return ;
	while (++i < philo[0].n_max)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < philo[0].n_max)
	{
		if (i == philo->n_max - 1)
		{
			philo[i].right = &forks[i];
			philo[i].left = &forks[0];
		}
		else
		{
			philo[i].right = &forks[i];
			philo[i].left = &forks[i + 1];
		}
	}
	free(forks);
}

t_philosopher	new_philo(int i, int ac, char **av)
{
	t_philosopher	new;

	if (ac == 6)
		new.nb_time_must_eat = ft_atoi(av[5]);
	else
		new.nb_time_must_eat = -1;
	new.n = i + 1;
	new.n_max = ft_atoi(av[1]);
	new.time_to_die = ft_atoi(av[2]);
	new.time_to_eat = ft_atoi(av[3]);
	new.time_to_sleep = ft_atoi(av[4]);
	return (new);
}

void	add_time(t_philosopher *p, struct timeval *time, int max)
{
	int				i;

	i = -1;
	while (++i < max)
	{
		p[i].last_meal = current_time();
		p[i].time = *time;
		p[i].start_ms = time->tv_usec;
		p[i].start_s = time->tv_sec;
		p[i].start_time = (p[i].start_s * 1000) + (p[i].start_ms / 1000);
	}
}
