/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 09:01:53 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/02 11:50:28 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_all_eating(t_table *t)
{
    int i;

    i = 0;
    if (t->the_number_of_meals)
    {
        while(i < t->number_of_philos)
        {
            if (t->the_number_of_meals != t->philos[i].counter)
            {
                return (0);
            }
            i++;
        }
        return (1);
    }
    return (0);
}

long get_the_current()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void destory(t_philos *p, t_fork *forks, int numbers)
{
    int i;

    i = 0;
    while (i < numbers)
    {
        pthread_mutex_destroy(&forks[i].forks);
        pthread_mutex_destroy(&p->meal);
        i++;
    }
    pthread_mutex_destroy(&p->table->meal_lock);   
}

void join_threads(t_table *table)
{
    int i;
    i = 0;
    while (i < table->number_of_philos)
    {
        pthread_join(table->philos[i].treads, NULL);
        i++;
    }
    pthread_join(table->tabel_thread,NULL);
    
}

void create_pthread(t_philos *phil)
{
    int i;

    i = 0;
    while(i < phil->table->number_of_philos)
    {
        pthread_create(&phil[i].treads, NULL, routine, (void *)phil[i].table->philos);
        i++;
    }
    pthread_create(&phil->table->tabel_thread,NULL, monitor, (void *)phil->table);
}