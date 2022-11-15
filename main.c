/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:06:31 by niespana          #+#    #+#             */
/*   Updated: 2022/09/01 13:06:36 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	conform_input(char **av, int i, int j)
{
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
	}
	return (1);
}

static void	check_end_flags(int i, int max, t_philosopher *p, pthread_t *thread)
{
	int	j;

	while (1)
	{
		j = 0;
		usleep(69);
		while (++i < max)
		{
			if (current_time() - p[i].last_meal > p[0].time_to_die)
			{
				print_action("died", &p[i], "\033[0;31m", 1);
				break ;
			}
			if (p[i].nb_time_must_eat == 0)
				j++;
		}
		if (j >= max)
			break ;
		if (i < max && *p[i].death)
			break ;
		i = -1;
	}
	while (++i < max)
		pthread_join(thread[i], NULL);
}

void	ccleaner(int max, t_philosopher *p, pthread_t *t)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		pthread_mutex_destroy(p[i].right);
		pthread_detach(t[i]);
	}
}

static void	initialize(t_philosopher *p, char **av,
	struct timeval *t, pthread_mutex_t *forks)
{
	int				i;
	int				max;
	int				ac;

	max = ft_atoi(av[1]);
	ac = 0;
	while (av[ac])
		ac++;
	i = -1;
	while (++i < max)
		p[i] = new_philo(i, ac, av);
	add_time(p, t, max);
	put_forks(p, forks);
}

int	main(int ac, char **av)
{
	t_var	vars;

	vars.death = 0;
	pthread_mutex_init(&vars.lock, NULL);
	if ((ac != 5 && ac != 6) || !conform_input(av, 0, -1))
		return (0);
	vars.max = ft_atoi(av[1]);
	gettimeofday(&vars.time, NULL);
	initialize(vars.philosophers, av, &vars.time, vars.forks);
	vars.i = -1;
	while (++vars.i < vars.max)
	{
		vars.philosophers[vars.i].death = &vars.death;
		vars.philosophers[vars.i].display_lock = &vars.lock;
	}
	vars.i = -1;
	while (++vars.i < vars.max)
		pthread_create(&(vars.philo_thread[vars.i]),
			NULL, taphilochi, &(vars.philosophers[vars.i]));
	check_end_flags(-1, vars.max, vars.philosophers, vars.philo_thread);
	ccleaner(vars.max, vars.philosophers, vars.philo_thread);
	return (0);
}
