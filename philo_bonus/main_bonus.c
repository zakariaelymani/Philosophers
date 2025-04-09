/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/09 15:21:26 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void exit_function(t_table *t)
{
	int i;
	int status;
	pid_t dead_pid;

	i = 0;
	dead_pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) &&  WEXITSTATUS(status) == 1)
	{
		i = 0;
		while (i < t->num_ph)
		{
			if (t->philos[i].pid != dead_pid)
				kill(t->philos[i].pid, SIGTERM);
			i++;
		}
	}
	sem_close(t->eating);
	sem_close(t->death);
	sem_close(t->meal);
	sem_close(t->semaph);
	sem_unlink("/eating");
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
