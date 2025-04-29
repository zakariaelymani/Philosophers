/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 07:18:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/29 11:26:16 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_table(t_table *table, char **args, int argc)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("invalid arguments \n", 2);
		return (1);
	}
	table->number_of_philos = ft_atoi(args[1]);
	table->time_of_die = ft_atoi(args[2]);
	table->time_of_eat = ft_atoi(args[3]);
	table->time_of_sleep = ft_atoi(args[4]);
	if (argc == 6)
		table->number_meals = ft_atoi(args[5]);
	else
		table->number_meals = 0 ;
	if (table->number_of_philos <= 0 || table->time_of_die < 60
		|| table->time_of_sleep < 60 || table->time_of_eat < 60
		|| (argc == 6 && table->number_meals <= 0)
		|| table->number_of_philos > 200)
	{
		ft_putstr_fd("this is invalid input\n", 2);
		return (1);
	}
	table->full = 0;
	table->death = 0;
	pthread_mutex_init(&table->meal_lock, NULL);
	return (0);
}

void	fill_philos(t_philos *p, t_table *t)
{
	int	i;

	i = 0;
	while (i < t->number_of_philos)
	{
		p[i].philo_id = i + 1;
		p[i].right_f = i;
		if (i + 1 == t->number_of_philos)
			p[i].left_f = 0;
		else
			p[i].left_f = i + 1;
		pthread_mutex_init(&t->array_of_f[i], NULL);
		p[i].table = t;
		p[i].counter = 0;
		i++;
	}
	t->philos = p;
	pthread_mutex_init(&t->check_death, NULL);
	pthread_mutex_init(&t->print, NULL);
	pthread_mutex_init(&t->start, NULL);
}
