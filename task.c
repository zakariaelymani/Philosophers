/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:59 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/04 16:53:57 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void manage_locks(t_thread thread, pthread_mutex_t mtx)
{
	if (thread == LOCK)
	{
		if (pthread_mutex_lock(&mtx) != 0)
			error_exit("error in lock mutex \n");
	}
	if (thread  == UNLOCK)
	{
		if (pthread_mutex_unlock(&mtx) != 0)
			error_exit("error in unlock mutex \n");
	}
	if (thread == INIT)
	{
		if (pthread_mutex_init(&mtx, NULL) != 0)
			error_exit("error in init mutex \n");
	}
	if (thread == DESTROY)
	{
		if (pthread_mutex_destroy(&mtx ) != 0)
			error_exit("error in destroy mutex \n");
	}
	else
		error_exit("error input to manage locks \n");
		
}

void *routine(void *t)
{
	t_philos *philos = (t_philos *)t;
	while (philos->table->similation_runing)
	{
		manage_locks(LOCK, philos->table->array_of_fork[philos->right_frok]);
		print("take right fork\n", philos->the_philo_id, philos->table->sesstion_start);
		manage_locks(LOCK, philos->table->array_of_fork[philos->left_frok]);
		print("take left fork\n", philos->the_philo_id, philos->table->sesstion_start);
		manage_locks(LOCK,philos->meal);
		philos->the_last_meal = get_the_current(MICRO);
		manage_locks(UNLOCK,philos->meal);
		print("is eating\n", philos->the_philo_id, philos->table->sesstion_start);
		philos->counter++;
		prcise_usleep(philos->table->time_of_eat * 1000);
		manage_locks(UNLOCK, philos->table->array_of_fork[philos->right_frok]);
		manage_locks(UNLOCK, philos->table->array_of_fork[philos->left_frok]);
		print("is sleeping\n", philos->the_philo_id, philos->table->sesstion_start);
		prcise_usleep(philos->table->time_of_sleep * 1000);
		print("is thinking\n", philos->the_philo_id, philos->table->sesstion_start);     
	}
	return (NULL);
}

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
			manage_locks(LOCK, table->meal_lock);
			time_since_last_meal = get_the_current(MICRO) - table->philos[i].the_last_meal;
			manage_locks(UNLOCK, table->meal_lock);
			if ((table->time_of_die * 1000) < time_since_last_meal)
			{
				manage_locks(LOCK, table->print_die);
				print("the philo die", table->philos[i].the_philo_id, table->sesstion_start);
				manage_locks(UNLOCK, table->print_die);
				table->similation_runing = 0;
				return (NULL);
			}
			else if (check_all_eating(table) == 1)
			{
				table->similation_runing = 0;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
