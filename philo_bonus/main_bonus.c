/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/16 17:01:01 by zel-yama         ###   ########.fr       */
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
		if (t->philos[i].pid == 0)
		{
			routine(&t->philos[i]);
			exit(0);
		}
	}
}
void print_struct(t_table *t)
{
	int i = 0;
	printf(" this time died %ld\n", t->time_d);
	printf(" this time aeting %ld\n", t->time_e);
	printf("this time to sleep %ld \n", t->time_s);
	printf("this number of philo%d\n", t->num_ph);
	printf("this number of meals%d\n",t->num_me);
	while (i < t->num_ph)
	{
		printf("this phid id %d\n", t->philos[i].philo_id);
		printf("this count	%d\n", t->philos[i].count);
		i++;
	}
	
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo *philo = malloc(sizeof(t_philo) * 20);
	
	fill_that(argc, argv, &table, philo);
	start(&table);
	
	exit_function(&table);
}
