/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:59 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/09 13:06:11 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philos *p, t_table *t)
{
	pthread_mutex_lock(&t->array_of_f[p->right_f]);
	print("has taken a fork", p, t->sesstion_start);
	if (t->number_of_philos == 1)
	{
		prcise_usleep(t->time_of_die * 1000, p);
		pthread_mutex_unlock(&t->array_of_f[p->right_f]);
		t->death = 1;
		return ;
	}
	pthread_mutex_lock(&t->array_of_f[p->left_f]);
	print("has taken a fork", p, t->sesstion_start);
	pthread_mutex_lock(&t->meal_lock);
	p->last_meal = get_the_current(MAIL);
	p->counter++;
	pthread_mutex_unlock(&t->meal_lock);
	print("is eating", p, t->sesstion_start);
	prcise_usleep(t->time_of_eat * 1000, p);
	pthread_mutex_unlock(&t->array_of_f[p->left_f]);
	pthread_mutex_unlock(&t->array_of_f[p->right_f]);
}

void	seelping(t_philos *p, t_table *t)
{
	print("is sleeping", p, t->sesstion_start);
	prcise_usleep(t->time_of_sleep * 1000, p);
	print("is thinking", p, t->sesstion_start);
}

void	*routine(void *philos)
{
	t_philos	*p;
	t_table		*t;

	p = (t_philos *)philos;
	t = p->table;
	if (p->philo_id % 2 == 0)
		usleep(1000);
	while (!t->death && !t->full)
	{
		eating(p, t);
		seelping(p, t);
	}
	return (NULL);
}

void	monitor(t_philos *p, t_table *t)
{
	int			i;
	long long	since_last;

	while (!t->death && !t->full)
	{
		i = 0;
		while (i < t->number_of_philos && !t->death)
		{
			pthread_mutex_lock(&t->check_death);
			since_last = get_the_current(MAIL) - p[i].last_meal;
			if (since_last >= t->time_of_die)
			{
				print("died", &p[i], t->sesstion_start);
				t->death = 1;
			}
			pthread_mutex_unlock(&t->check_death);
			(1) && (usleep(1000), i++);
		}
		i = 0;
		while (t->number_meals != 0 && i < t->number_of_philos
			&& t->number_meals <= t->philos[i].counter)
			i++;
		if (i == t->number_of_philos)
			t->full = 1;
	}
}
