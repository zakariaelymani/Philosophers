/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:59 by zel-yama          #+#    #+#             */
/*   Updated: 2025/05/08 14:15:43 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philos *p, t_table *t)
{
	pthread_mutex_lock(&t->array_of_f[p->right_f]);
	print("has taken a fork", p, t->sesstion_start);
	if (t->number_of_philos == 1)
	{
		prcise_usleep(t->time_of_die * 1000 + 2000, p);
		pthread_mutex_unlock(&t->array_of_f[p->right_f]);
		return ;
	}
	pthread_mutex_lock(&t->array_of_f[p->left_f]);
	print("has taken a fork", p, t->sesstion_start);
	pthread_mutex_lock(&t->meal_lock);
	p->last_meal = get_the_current(MAIL);
	pthread_mutex_unlock(&t->meal_lock);
	pthread_mutex_lock(&t->countr);
	p->counter++;
	pthread_mutex_unlock(&t->countr);
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
	while (!is_maat(t))
	{
		eating(p, t);
		seelping(p, t);
	}
	return (NULL);
}

void	check_is_full(t_table *t, t_philos *p, int *falg)
{
	int	i;
	int	counter;
	int	x;

	x = 0;
	i = 0;
	while (i < t->number_of_philos && !is_maat(t))
	{
		pthread_mutex_lock(&t->countr);
		counter = p[i].counter;
		pthread_mutex_unlock(&t->countr);
		if (t->number_meals != 0 && counter >= t->number_meals)
			x++;
		i++;
	}
	pthread_mutex_lock(&t->print);
	pthread_mutex_lock(&t->is_full);
	if (x == t->number_of_philos && t->number_meals != 0)
		*falg = 1;
	pthread_mutex_unlock(&t->is_full);
	pthread_mutex_unlock(&t->print);
}

void	*monitor(void *arg)
{
	int			i;
	long long	since_last;
	t_table		*t;
	t_philos	*p;

	t = (t_table *)arg;
	p = t->philos;
	since_last = 0;
	while (!is_maat(t))
	{
		i = 0;
		while (i < t->number_of_philos && !is_maat(t))
		{
			check_is_death(t, p, i, since_last);
			usleep(1000);
			i++;
		}
		(check_is_full(t, p, &t->full), usleep(1000));
	}
	return (NULL);
}
