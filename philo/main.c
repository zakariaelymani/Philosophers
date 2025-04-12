/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:25 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/07 12:08:38 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *arg[])
{
	t_table		table;
	t_philos	philo[200];
	int			i;

	if (fill_table(&table, arg, argc) == 1)
		return (1);
	(1) && (fill_philos(philo, &table), i = 0);
	table.sesstion_start = get_the_current(MAIL);
	while (i < table.number_of_philos)
	{
		if (pthread_create(&philo[i].threads, NULL, routine, &philo[i]))
		{
			ft_putstr_fd("error is pthread create\n", 2);
			return (1);
		}
		pthread_mutex_lock(&table.start);
		philo[i].last_meal = table.sesstion_start;
		pthread_mutex_unlock(&table.start);
		i++;
	}
	monitor(philo, &table);
	joined_thread(&table, philo);
	return (0);
}
