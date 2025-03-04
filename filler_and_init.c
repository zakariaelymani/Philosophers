/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 07:18:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/04 16:36:31 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void creat_threads(pthread_t t, void*fucn(void *), void *argument ,t_thread enm)
{
    if (enm =  CREATE)
    {
        if (pthread_create(&t, NULL, fucn, argument) != 0)
            error_exit("error in creat threads \n");
    }
    else if (enm = JOIN)
    {
        if (pthread_join(t,NULL) != 0)
            error_exit("error in join threads \n");
    }
    
    
}

void create_pthread(t_philos *phil)
{
    int i;

    i = 0;
    phil->table->sesstion_start = get_the_current(MAIL);
    while(i < phil->table->number_of_philos)
    {
        creat_threads(phil[i].treads, routine, (void *)phil[i].table->philos, CREATE);
        i++;
    }
    creat_threads(phil->table->tabel_thread, monitor,(void *)phil->table, CREATE);
}

void    init_struct(int numbs, t_philos **philos, t_table *table)
{
    int i;

    i = 0;
    while(i < numbs)
    {
        (*philos)[i].counter = 0;
        manage_locks(INIT, (*philos)[i].meal);
        ((*philos)[i].table) = table;
        (*philos)[i].right_frok = i;
        (*philos)[i].the_philo_id = i + 1;
        if (i + 1 == numbs)
            (*philos)[i].left_frok = 0;
        else
            (*philos)[i].left_frok = i + 1 ;
        i++;   
    }
    i = 0;
    while (i < numbs)
    {
        manage_locks(INIT,table->array_of_fork[i]);
        i++;
    }
}



void fill_struct(t_table **table, t_philos **p, char **args, int argc)
{
    if (argc != 5 && argc != 6)
        error_exit("invalid arguments");

    *table = (t_table *)ft_malloc(sizeof(t_table));
    (*table)->similation_runing = 1;
    manage_locks(INIT,(*table)->meal_lock);
    manage_locks(INIT, (*table)->print_die);
    (*table)->number_of_philos = ft_atoi(args[1]);
    (*table)->time_of_die = ft_atoi(args[2]);
    (*table)->time_of_eat = ft_atoi(args[3]);
    (*table)->time_of_sleep = ft_atoi(args[4]);
    if (argc == 6)
        (*table)->the_number_of_meals = ft_atoi(args[5]);
    else
        (*table)->the_number_of_meals = 0;
    if ((*table)->number_of_philos < 0 || (*table)->time_of_die < 0 || 
        (*table)->time_of_sleep < 0 || (*table)->time_of_eat < 0 || 
        (*table)->the_number_of_meals < 0)
        error_exit("this is invalid input");
    *p = (t_philos *)ft_malloc(sizeof(t_philos) * (*table)->number_of_philos);
    (*table)->philos = *p;
    (*table)->array_of_fork = (pthread_mutex_t *)ft_malloc(sizeof(pthread_mutex_t)
         * (*table)->number_of_philos);
    
}
