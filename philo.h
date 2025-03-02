/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:50:49 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/02 11:41:51 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_fork
{
    pthread_mutex_t forks;
}t_fork;

typedef struct s_philos
{
    pthread_t treads;
    
    pthread_mutex_t meal;
    long the_last_meal;
    int right_frok;
    int left_frok;
    int the_philo_id;
    int counter;
    t_table *table;
}   t_philos;

typedef struct s_table
{
    pthread_t tabel_thread;
    int similation_runing;
    int number_of_philos;
    t_philos *philos;
    int sesstion_start;
    t_fork *array_of_fork;
    pthread_mutex_t print_die;
    pthread_mutex_t meal_lock;
    int the_number_of_meals;
    int time_of_eat;
    int time_of_die;
    int time_of_sleep;
}   t_table;

long get_the_current();
void fill_struct(t_table *t, t_philos *p, t_fork *f);
void destory(t_philos *p, t_fork *forks, int numbers);
void join_threads(t_table *table);
void create_pthread(t_philos *phil);
void *routine(void *t);
int check_all_eating(t_table *t);
void *monitor(void *t);