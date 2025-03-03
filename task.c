/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:10:59 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/03 08:25:52 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




void *routine(void *t)
{
	t_philos *philos = (t_philos *)t;
	while (philos->table->similation_runing)
	{
		pthread_mutex_lock(&philos->table->array_of_fork[philos->right_frok]);
		print("take right fork\n", philos->the_philo_id, philos->table->sesstion_start);
		pthread_mutex_unlock(&philos->table->array_of_fork[philos->left_frok]);
		print("take left fork\n", philos->the_philo_id, philos->table->sesstion_start);
		pthread_mutex_lock(&philos->meal);
		philos->the_last_meal = get_the_current();
		pthread_mutex_unlock(&philos->meal);
		print("is eating\n", philos->the_philo_id, philos->table->sesstion_start);
		philos->counter++;
		usleep(philos->table->time_of_eat );
		pthread_mutex_unlock(&philos->table->array_of_fork[philos->right_frok]);
		pthread_mutex_unlock(&philos->table->array_of_fork[philos->left_frok]);
		print("is sleeping\n", philos->the_philo_id, philos->table->sesstion_start);
		usleep(philos->table->time_of_sleep);
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
