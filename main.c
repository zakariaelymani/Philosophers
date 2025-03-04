/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:25 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/04 14:28:23 by zel-yama         ###   ########.fr       */
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
		printf("this is the leftfork %d \n",t->philos[i].left_frok);
		printf("this is the right fork %d \n", t->philos[i].right_frok)	;
		printf("this the phil id %d \n",t->philos[i].the_philo_id);
		printf("this is the counter %d \n", t->philos[i].counter);
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
	init_struct(table->number_of_philos, &phils, table);
	//print_struct(table);
	 create_pthread(phils); //this the hard part in my code 
	join_threads(table);
	 destory(phils,table->number_of_philos);
}
