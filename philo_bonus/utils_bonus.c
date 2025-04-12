/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:26 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/12 19:29:29 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_the_current(t_time time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time == MAIL)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time == MICRO)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (tv.tv_sec + (tv.tv_usec / 1e6));
}

void	prcise_usleep(long time_wait, t_table *t)
{
	long long	start;

	start = get_the_current(MICRO);
	while ((get_the_current(MICRO) - start) < time_wait)
	{
		if (t->flag_d)
			break ;
		usleep(333);
	}
}

void	print(char *s, int id, long start, t_table *t)
{
	long	current_time;

	my_sem_wait(t->meal);
	if (!t->flag_d)
	{
		current_time = (get_the_current(MAIL) - start);
		printf("%ld [%d] %s\n", current_time, id, s);
	}
	my_sem_post(t->meal);
}
void destroy_all(t_table *t)
{
	int i;

	i = 0;
	while (i < t->num_ph)
	{
		kill(t->philos[i].pid, SIGTERM);
		i++;
	}
	sem_close(t->full);
	sem_close(t->eating);
	sem_close(t->death);
	sem_close(t->meal);
	sem_close(t->semaph);
	sem_unlink("/full");
	sem_unlink("/eating");
	sem_unlink("/semaphore");
	sem_unlink("/death");
	sem_unlink("/meal");
}

void	exit_function(t_table *t)
{
	
	 waitpid(-1, NULL, 0);
	my_sem_wait(t->meal);
	destroy_all(t);

	
}
void my_sem_wait(sem_t *se)
{
	if (sem_wait(se) == -1)
	{
		write(2, "sem_wiat failed \n", 18);
		exit(1);
	}
}