/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:25 by zel-yama          #+#    #+#             */
/*   Updated: 2025/05/08 14:17:48 by zel-yama         ###   ########.fr       */
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
	if (fill_philos(philo, &table) == 1)
		return (1);
	i = 0;
	table.sesstion_start = get_the_current(MAIL);
	while (i < table.number_of_philos)
	{
		if (pthread_create(&philo[i].threads, NULL, routine, &philo[i]))
		{
			(ft_putstr_fd("error in creating\n", 2), destroy_mutex(&table));
			return (1);
		}
		pthread_mutex_lock(&table.start);
		philo[i].last_meal = table.sesstion_start;
		pthread_mutex_unlock(&table.start);
		i++;
	}
	pthread_create(&table.tabel_thread, NULL, monitor, &table);
	joined_thread(&table, philo);
	return (0);
}
