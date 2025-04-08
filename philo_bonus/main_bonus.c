/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/08 18:43:11 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void exit_function(t_table *t)
{
	int i;
	int status;

	i = 0;
	while (i < t->num_ph)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < t->num_ph)
			{
				kill(t->philos[i].pid, SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(t->death);
	sem_close(t->meal);
	sem_close(t->semaph);
	sem_unlink("/semaphore");
	sem_unlink("/death");
	sem_unlink("/meal");
}

int main(int argc, char *argv[])
{
    t_table table;
    t_philo philo[200];
	int		i;
	
    
	i = 0;
    fill_that(argc, argv, &table, philo);
	//printf("%d \n %ld \n %ld \n %ld \n", table.num_ph, table.time_d, table.time_s, table.time_e);
	table.semaph = sem_open("/semaphore", O_CREAT, 0644, table.num_ph);
	if (table.semaph == SEM_FAILED)
		(write(2, "sem_open fails \n", 17), exit(1));
	table.start = get_the_current(MAIL);
	while(i < table.num_ph)
	{
		
		table.philos[i].pid = fork();
		if (table.philos[i].pid == -1)
		(write(2, "fork failed \n", 14), exit(1));
		if (table.philos[i].pid == 0)
		{
			routine(&table.philos[i]);
		}
			
			
		i++;
	}
	exit_function(&table);
}
