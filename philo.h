/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:35:49 by niespana          #+#    #+#             */
/*   Updated: 2022/09/01 13:35:50 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdatomic.h>

typedef struct s_philosopher
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	atomic_int		nb_time_must_eat;
	int				n;
	int				n_max;
	int				start_ms;
	atomic_long		last_meal;
	atomic_int		*death;
	long			start_s;
	struct timeval	time;
	long int		start_time;
	pthread_mutex_t	*display_lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philosopher;

typedef struct s_var
{
	pthread_mutex_t	lock;
	t_philosopher	philosophers[210];
	pthread_t		philo_thread[210];
	pthread_mutex_t	forks[210];
	int				i;
	int				max;
	struct timeval	time;
	atomic_int		death;
}	t_var;

int				ft_atoi(const char *str);
t_philosopher	new_philo(int i, int ac, char **av);
void			put_forks(t_philosopher *philo, pthread_mutex_t *forks);
void			add_time(t_philosopher *p, struct timeval *time, int max);
void			*taphilochi(void *data);
long int		ms(t_philosopher *crt);
long int		current_time(void);
void			print_action(char *msg, t_philosopher *crt,
					char *color, int died);

#endif
