/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/05/08 14:15:39 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_is_death(t_table *t, t_philos *p, int i, int since_last)
{
	pthread_mutex_lock(&t->meal_lock);
	since_last = get_the_current(MAIL) - p[i].last_meal;
	pthread_mutex_unlock(&t->meal_lock);
	pthread_mutex_lock(&t->check_death);
	if (since_last >= t->time_of_die)
	{
		print("died", &p[i], t->sesstion_start);
		pthread_mutex_lock(&t->print);
		t->death = 1;
		pthread_mutex_unlock(&t->print);
	}
	pthread_mutex_unlock(&t->check_death);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print(char *s, t_philos *p, long long start)
{
	long long	current_time;

	pthread_mutex_lock(&p->table->print);
	if (!p->table->full && !p->table->death)
	{
		current_time = (get_the_current(MAIL) - start);
		printf("%lld [%d] %s\n", current_time, p->philo_id, s);
	}
	pthread_mutex_unlock(&p->table->print);
}
