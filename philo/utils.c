/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 09:01:53 by zel-yama          #+#    #+#             */
/*   Updated: 2025/05/08 14:14:28 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prcise_usleep(long time_wait, t_philos *p)
{
	long long	start;

	start = get_the_current(MICRO);
	while ((get_the_current(MICRO) - start) < time_wait)
	{
		if (is_maat(p->table))
			break ;
		usleep(333);
	}
}

long long	get_the_current(t_time time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time == MAIL)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time == MICRO)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (tv.tv_sec + (tv.tv_usec / 1e6));
}

void	destroy_mutex(t_table *t)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&t->meal_lock);
	while (i < t->number_of_philos)
	{
		pthread_mutex_destroy(&t->array_of_f[i]);
		i++;
	}
	pthread_mutex_destroy(&t->check_death);
	pthread_mutex_destroy(&t->print);
	pthread_mutex_destroy(&t->start);
}

void	joined_thread(t_table *t, t_philos *p)
{
	int	i;

	i = 0;
	while (i < t->number_of_philos)
	{
		if (pthread_join(p[i].threads, NULL))
			break ;
		i++;
	}
	pthread_join(t->tabel_thread, NULL);
	destroy_mutex(t);
}

int	is_maat(t_table *t)
{
	pthread_mutex_lock(&t->check_death);
	if (t->death)
	{
		pthread_mutex_unlock(&t->check_death);
		return (1);
	}
	pthread_mutex_unlock(&t->check_death);
	pthread_mutex_lock(&t->is_full);
	if (t->full)
	{
		pthread_mutex_unlock(&t->is_full);
		return (1);
	}
	pthread_mutex_unlock(&t->is_full);
	return (0);
}
