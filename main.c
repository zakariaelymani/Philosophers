/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:25 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/10 15:35:39 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
monitor to check is all philos is eating or some of them is die or 
os this will sparated thread  and joine that after this join the other 
*/
void print_struct(t_table *t)
{
	int  i = 0;
	while (i < t->number_of_philos)
	{
		printf("this is the leftfork %d \n",t->philos[i].left_f);
		printf("this is the right fork %d \n", t->philos[i].right_f)	;
		printf("this the phil id %d \n",t->philos[i].philo_id);
		printf("this is the counter %d \n", t->philos[i].counter);
		printf("this ths similatiruning %d \n", t->similation_runing);
		printf("this the number of philos %d, \n", t->number_of_philos);
		printf ("this is the number of meals that ihav%d \n", t->number_meals);
		
		i++;
	}
	
}
void joined_thread(t_table *t, t_philos *p)
{
	int i;

	i = 0;
	while (i < t->number_of_philos)
	{
		pthread_join(p[i].threads,NULL);
		i++;
	}
}
void destroy_mutex(t_table *t)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&t->meal_lock);
	while (i < t->number_of_philos)
	{
		pthread_mutex_destroy(&t->array_of_f[i]);
		i++;
	}
}

int main(int argc, char *arg[])
{
	t_table		table;
	t_philos	philo[200];
	int 		i;
	
	if (fill_table(&table, arg, argc) == 1)
		return (1);
	fill_philos(philo, &table);
	i = 0;
	table.sesstion_start = get_the_current(MAIL);
	while (i < table.number_of_philos)
	{
		
		if (pthread_create(&philo[i].threads,NULL, routine,&philo[i]))
		
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
	destroy_mutex(&table);
	return (0);
}
