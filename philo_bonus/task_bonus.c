/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:31 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/29 11:41:43 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *p, t_table *t)
{
	sem_wait(p->t->semaph);
	print("has taken a fork", p->philo_id, t->start, t);
	if (t->num_ph == 1)
	{
		prcise_usleep(p->t->time_d * 1000, t);
		t->flag_d = 1;
		sem_post(p->t->semaph);
		return ;
	}
	sem_wait(p->t->semaph);
	print("has taken a fork", p->philo_id, t->start, t);
	sem_wait(p->t->death);
	p->last_meal = get_the_current(MAIL);
	p->count++;
	sem_post(p->t->death);
	print("is eating", p->philo_id, t->start, t);
	prcise_usleep(t->time_e * 1000, t);
	sem_post(p->t->semaph);
	sem_post(p->t->semaph);
}

void	sleeping(t_philo *p, t_table *t)
{
	print("is sleeping", p->philo_id, t->start, t);
	prcise_usleep(t->time_s * 1000, t);
	print("is thinking", p->philo_id, t->start, t);
}

void	*monitor(void *philo)
{
	t_table	*t;
	t_philo	*p;
	long	time;

	p = (t_philo *)philo;
	t = (t_table *)p->t;
	while (1)
	{
		sem_wait(t->death);
		time = get_the_current(MAIL) - p->last_meal;
		if (time >= t->time_d)
		{
			print("died ", p->philo_id, t->start, t);
			t->flag_d = 1;
			sem_wait(t->meal);
			exit(1);
		}
		sem_post(t->death);
		usleep(100);
	}
	return (NULL);
}

void	routine(t_philo *p)
{
	t_table	*t;

	t = p->t;
	p->last_meal = t->start;
	if (pthread_create(&p->monitor, NULL, monitor, (void *)p))
		exit(1);
	if (p->philo_id % 2 == 0)
		usleep(1000);
	while (!t->flag_d)
	{
		eating(p, t);
		if (t->num_me != 0 && p->count >= t->num_me)
		{
			t->flag_d = 1;
			break ;
		}
		sleeping(p, t);
	}
	if (pthread_join(p->monitor, NULL))
		exit(1);
	exit(0);
}
