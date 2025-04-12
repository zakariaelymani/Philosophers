/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:00:48 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/11 15:50:38 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_philo(t_philo *p, t_table *t)
{
	int	i;

	i = 0;
	while (i < t->num_ph)
	{
		p[i].count = 0;
		p[i].philo_id = i + 1;
		p[i].t = t;
		i++;
	}
}

void	fill_that(int argc, char **argv, t_table *t, t_philo *p)
{
	if (argc != 5 && argc != 6)
		(write(2, "invalid arguments\n", 19), exit(2));
	t->flag_d = 0;
	t->num_ph = ft_atoi(argv[1]);
	t->time_d = ft_atoi(argv[2]);
	t->time_e = ft_atoi(argv[3]);
	t->time_s = ft_atoi(argv[4]);
	if (argc == 6)
		t->num_me = ft_atoi(argv[5]);
	else
		t->num_me = 0;
	t->semaph = sem_open("/semaphore", O_CREAT, 0644, t->num_ph);
	t->eating = sem_open("/eating", O_CREAT, 0644, 1);
	t->death = sem_open("/death", O_CREAT, 0644, 1);
	t->meal = sem_open("/meal", O_CREAT, 0644, 1);
	if (t->death == SEM_FAILED || t->meal == SEM_FAILED
		|| t->eating == SEM_FAILED || t->semaph == SEM_FAILED)
		(write(2, "error in semphore create \n", 27), exit(1));
	if (t->time_d < 60 || t->time_e < 60 || t->time_s < 60
		|| (argc == 6 && t->num_me <= 0) || t->num_ph <= 0 || t->num_ph > 200)
		(write(2, "invalid arguments\n", 19), exit(2));
	fill_philo(p, t);
	t->philos = p;
}
