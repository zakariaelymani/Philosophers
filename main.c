/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:25 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/02 11:41:36 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
monitor to check is all philos is eating or some of them is die or 
os this will sparated thread  and joine that after this join the other 
*/
void *monitor(void *t)
{
    t_table *table = (t_table *)t;
    int i;
    long time_since_last_meal;

    while(table->similation_runing)
    {
        i = 0;
        while (i < table->number_of_philos)
        {
            pthread_mutex_lock(&table->meal_lock);
            time_since_last_meal = get_the_current() - table->philos[i].the_last_meal;
            pthread_mutex_unlock(&table->meal_lock);
            if (table->time_of_die < time_since_last_meal)
            {
                pthread_mutex_lock(&table->print_die);
                printf("the philos id %d die\n", table->philos[i].the_philo_id);
                pthread_mutex_unlock(&table->print_die);
                table->similation_runing = 0;
            }
            else if (check_all_eating(table) == 1)
                table->similation_runing = 0;
            i++;
        }
    }
    return (NULL);
}


void *routine(void *t)
{
    t_philos *philos = (t_philos *)t;
    while (philos->table->similation_runing)
    {
        pthread_mutex_lock(&philos->table->array_of_fork[philos->right_frok].forks);
        printf("the philos %d take fork\n", philos->the_philo_id);
        pthread_mutex_lock(&philos->table->array_of_fork[philos->left_frok].forks);
        printf("the philos %d take fork\n", philos->the_philo_id);
        pthread_mutex_lock(&philos->meal);
        philos->the_last_meal = get_the_current();
        pthread_mutex_unlock(&philos->meal);
        printf("the philos id %d is eating \n", philos->the_philo_id);
        philos->counter++;
        usleep(philos->table->time_of_eat * 1000);
        pthread_mutex_unlock(&philos->table->array_of_fork[philos->right_frok].forks);
        pthread_mutex_unlock(&philos->table->array_of_fork[philos->left_frok].forks);
        printf("the philos id %d is sleeping\n", philos->the_philo_id);
        usleep(philos->table->time_of_sleep * 1000);
        printf("the philos id %d is thinking\n", philos->the_philo_id);        
    }
    return (NULL);
}


int main()
{
    t_table *table = malloc(sizeof(t_table) * 1);
    t_fork *forks = malloc(sizeof(t_fork) * 2);
    t_philos *phils = malloc(sizeof(t_philos) * 2);
    init(2, phils, forks, table);
    fill_struct(table,phils,forks);
    create_pthread(table);
    join_threads(table);
    destory(phils, forks, table->number_of_philos);
}
