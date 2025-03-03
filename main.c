/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:25 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/03 11:02:03 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
monitor to check is all philos is eating or some of them is die or 
os this will sparated thread  and joine that after this join the other 
*/
void print_struct(t_philos *t)
{
	int  i = 0;
	// printf("this time to 5eating %ld \n", t->table->time_of_eat);
	// printf("time to4 die %ld \n", t->table->time_of_die);
	// printf("time to4 seelp %ld\n", t->table->time_of_sleep);
	// printf("numbe of 4filo sofu %d\n", t->table->number_of_philos);
	// printf("the number 5of meals %ld \n", t->table->the_number_of_meals);
	while (i < t->table->number_of_philos)
	{
		printf("this is counter %d \n", t[i].counter);
		printf(" this is the id of filo %d\n ", t[i].the_philo_id);
		printf(" this left frok %d \n", t[i].left_frok);
		printf(" this right frok %d \n", t[i].right_frok);
		printf("time of %ld eating \n",  t[i].table->time_of_eat);
		i++;
	}

	
}

int main(int argc, char *arg[])
{
	t_table *table;
	t_philos *phils;
	
	table = NULL;
	phils = NULL;
	fill_struct(&table,&phils, arg, argc);
	init_struct(table->number_of_philos, phils, table);
	//print_struct(table);
	// create_pthread(phils);
	// join_threads(table);
	// destory(phils,table->number_of_philos);
}
