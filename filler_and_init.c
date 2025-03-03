/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_and_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 07:18:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/03 15:41:25 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void init_struct(int numbs, t_philos *philos, t_table *table)
{
    int i;

    i = 0;
    while(i < numbs)
    {
        philos[i].counter = 0;
        pthread_mutex_init(&philos[i].meal, NULL);
        philos[i].table = table;
        philos[i].right_frok = i;
        philos[i].the_philo_id = i + 1;
		printf("%d \n",philos[i].the_philo_id = i + 1);
	
        if (i + 1 > numbs)
            philos[i].left_frok = 0;
        else
            philos[i].left_frok = i + 1;
        i++;
        
    }
    i = 0;
	print_struct(philos);
    while (i < numbs)
    {
        pthread_mutex_init(&table->array_of_fork[i], NULL);
        i++;
    }
  
}
void error_exit(char *s)
{
    ft_putstr_fd(s, 2);
    ft_free(NULL, 1);
    exit(1);
    
}

void fill_struct(t_table **table, t_philos **p, char **args, int argc)
{

    *table = ft_malloc(sizeof(*table));    
    if (argc != 5 && argc != 6)
        error_exit("invalid arguments\n");
    (*table)->similation_runing = 1;
    pthread_mutex_init(&(*table)->meal_lock, NULL);
    pthread_mutex_init(&(*table)->print_die, NULL);
    (*table)->number_of_philos = ft_atoi(args[1]);
    printf(" this number of philos %d \n",(*table)->number_of_philos);
    (*table)->time_of_die = ft_atoi(args[2]);
    printf("this is the time to die %ld \n",(*table)->time_of_die );
    (*table)->time_of_eat = ft_atoi(args[3]);
    printf("this time of eating %ld \n",(*table)->time_of_eat );
    (*table)->time_of_sleep = ft_atoi(args[4]);
    printf("time of sleep %ld \n", (*table)->time_of_sleep);
    if (argc == 6)
        (*table)->the_number_of_meals = ft_atoi(args[5]);
    else
        (*table)->the_number_of_meals = 0;
    if ((*table)->number_of_philos < 0 || (*table)->time_of_die < 0 || (*table)->time_of_sleep < 0
        || (*table)->time_of_eat < 0 || (*table)->the_number_of_meals < 0)
            error_exit("this is invalid input");
    *p = ft_malloc(sizeof(t_philos) * (*table)->number_of_philos);
    (*table)->philos = *p;
    (*table)->array_of_fork = ft_malloc(sizeof(pthread_mutex_t) *(*table)->number_of_philos);
    (*table)->sesstion_start = get_the_current();
}
