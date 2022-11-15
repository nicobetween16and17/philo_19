/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:06:53 by niespana          #+#    #+#             */
/*   Updated: 2022/09/01 13:06:54 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ms(t_philosopher *crt)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000) - crt->start_time);
}

void	print_action(char *msg, t_philosopher *crt, char *color, int died)
{
	pthread_mutex_lock(crt->display_lock);
	if (!*crt->death)
		printf("%s%ld %d %s\033[0m\n", color, ms(crt), crt->n, msg);
	if (died)
		*crt->death = 1;
	pthread_mutex_unlock(crt->display_lock);
}

static void	action_sleep(t_philosopher *crt, int time)
{
	long int	start;

	start = current_time();
	while (current_time() - start <= time)
	{
		if (*crt->death)
			break ;
		usleep(69);
	}
}

static void	time_to_eat(t_philosopher *crt)
{
	pthread_mutex_lock(crt->left);
	print_action("has taken a fork", crt, "\033[0;37m", 0);
	pthread_mutex_lock(crt->right);
	print_action("has taken a fork", crt, "\033[0;37m", 0);
	if (!*crt->death)
		crt->last_meal = current_time();
	print_action("is eating", crt, "\033[0;32m", 0);
	action_sleep(crt, crt->time_to_eat);
	if (crt->nb_time_must_eat)
		crt->nb_time_must_eat--;
	pthread_mutex_unlock(crt->left);
	pthread_mutex_unlock(crt->right);
}

void	*taphilochi(void *data)
{
	t_philosopher	*crt;

	crt = (t_philosopher *)data;
	if (crt->n % 2)
		usleep(15000);
	while (crt->time_to_die > 0 && !*crt->death && crt->nb_time_must_eat)
	{
		if (crt->n_max == 1)
			action_sleep(crt, crt->time_to_die);
		if (!*crt->death)
			time_to_eat(crt);
		if (!*crt->death && crt->nb_time_must_eat)
		{
			print_action("is sleeping", crt, "\033[0;35m", 0);
			action_sleep(crt, crt->time_to_sleep);
		}
		if (!*crt->death && crt->nb_time_must_eat)
			print_action("is thinking", crt, "\033[0;34m", 0);
	}
	return (NULL);
}
