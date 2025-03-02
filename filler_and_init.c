/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 07:18:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/02 11:36:56 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void init(int numbs, t_philos *philos, t_fork *forks, t_table *table)
{
    int i;

    i = 0;
    while(i < numbs)
    {
        philos[i].counter = 0;
        pthread_mutex_init(&philos[i].meal, NULL);
        philos[i].table = table;
        philos[i].right_frok = i;
        philos[i].the_philo_id = i;
        if (i + 1 == numbs)
            philos[i].left_frok = 0;
        else
            philos[i].left_frok = i + 1;
        i++;
    }
    i = 0;
    while (i < numbs)
    {
        pthread_mutex_init(&forks[i].forks, NULL);
        i++;
    }
}

void fill_struct(t_table *t, t_philos *p, t_fork *f)
{
    t->similation_runing = 1;
    pthread_mutex_init(&t->meal_lock, NULL);
    pthread_mutex_init(&t->print_die, NULL);
    t->the_number_of_meals = 3;
    t->number_of_philos = 2;
    t->time_of_die = 10 * 1000;
    t->time_of_eat = 5 * 1000;
    t->time_of_sleep =  5 * 1000;
    t->array_of_fork = f;
    t->philos = p;
}