/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:31 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/12 19:25:35 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void my_sem_post(sem_t *sem)
{
	if (sem_post(sem) == -1)
	{
		write(2, "sem_post failed \n", 18);
		exit(1);
	}
}

void	eating(t_philo *p)
{
	t_table *t;

	t = p->t;
	my_sem_wait(p->t->semaph);
	print("has taken a fork", p->philo_id, t->start, t);
	if (t->num_ph == 1)
	{
		prcise_usleep(p->t->time_d * 1000, t);
		t->flag_d = 1;
		return ;
	}
	my_sem_wait(p->t->semaph);
	print("has taken a fork", p->philo_id, t->start, t);
	my_sem_wait(p->t->death);
	p->last_meal = get_the_current(MAIL);
	p->count++;
	my_sem_post(p->t->death);
	print("is eating", p->philo_id, t->start, t);
	prcise_usleep(t->time_e * 1000, t);
	my_sem_post(p->t->semaph);
	my_sem_post(p->t->semaph);
}

void	sleeping(t_philo *p, t_table *t)
{
	print("is sleeping", p->philo_id, t->start, t);
	prcise_usleep(t->time_s * 1000, t);
	print("is thinking", p->philo_id, t->start, t);
}
int is_full(int number_meal, int count, t_table *t)
{
	my_sem_wait(t->full);
	if(number_meal != 0 && count >= number_meal)
	{
		my_sem_post(t->full);
		return (1);
	}
	my_sem_post(t->full);
	return (0);
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
		my_sem_wait(t->death);
		time = get_the_current(MAIL) - p->last_meal;
		if (time >= t->time_d)
		{
			print("died ", p->philo_id, t->start, t);
			t->flag_d = 1;
			my_sem_post(t->eating);
			exit(1);
		}
		my_sem_post(t->death);
		if (is_full(t->num_me, p->count, t) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	routine(t_philo *p)
{
	t_table	*t;

	t = p->t;
	p->last_meal = t->start;
	pthread_create(&p->monitor, NULL, monitor, (void *)p);
	if (p->philo_id % 2 == 0)
		usleep(1000);
	while (!t->flag_d)
	{
		eating(p);
		if (is_full(t->num_me, p->count, t) == 1)
			break ;
		sleeping(p, t);
	}
	pthread_join(p->monitor, NULL);
	exit(0);
}
