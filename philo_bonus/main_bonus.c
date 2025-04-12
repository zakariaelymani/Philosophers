/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/10 16:21:52 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start(t_table *t)
{
	int	i;

	i = -1;
	t->start = get_the_current(MAIL);
	while (++i < t->num_ph)
	{
		t->philos[i].pid = fork();
		if (t->philos[i].pid == -1)
			(write(2, "fork failed \n", 14), exit(1));
		else if (t->philos[i].pid == 0)
			routine(&t->philos[i]);
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	philo[200];
	int		i;

	i = 0;
	fill_that(argc, argv, &table, philo);
	start(&table);
	exit_function(&table);
}
