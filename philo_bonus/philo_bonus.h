/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:38:22 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/06 20:33:34 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef enum s_time
{
	MAIL,
	MICRO
}	t_time;
typedef struct s_philo
{
	int		philo_id;
	long	last_meal;
	int		count;
}	t_philo;

typedef struct s_table
{
    long    	time_d;
	long		time_e;
	long		time_s;
	int			num_ph;
	int			num_me;
	sem_t		*semaph;
	char		*name_s;
	t_philo		*philos;
	int			falg_d;
	int			flag_f;
	pthread_t	routing;
	pthread_t	monitor;
	
}	t_table;

long	    ft_atoi(const char *str);
long long	get_the_current(t_time time);
void	    prcise_usleep(long time_wait);

#endif