/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/05/09 09:30:32 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	remove_orphan(t_table *t, int i)
{
	destroy_all(t);
	while (i > 0)
	{
		kill(t->philos[i].pid, SIGKILL);
		i--;
	}
}

void	start(t_table *t)
{
	int	i;

	i = -1;
	t->start = get_the_current(MAIL);
	while (++i < t->num_ph)
	{
		t->philos[i].pid = fork();
		if (t->philos[i].pid == -1)
			(write(2, "fork failed \n", 14), remove_orphan(t, i), exit(1));
		if (t->philos[i].pid == 0)
		{
			routine(&t->philos[i]);
			exit(0);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	philo[200];

	fill_that(argc, argv, &table, philo);
	start(&table);
	exit_function(&table);
}
