/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:38:22 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/08 16:29:03 by zel-yama         ###   ########.fr       */
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
# include <signal.h>

typedef enum s_time
{
	MAIL,
	MICRO
}	t_time;
typedef struct s_philo
{
	int				philo_id;
	long			last_meal;
	int				count;
	pid_t			pid;
	pthread_t		monitor;
	struct s_table	*t;
}	t_philo;

typedef struct s_table
{
	long		start;
    long    	time_d;
	long		time_e;
	long		time_s;
	int			num_ph;
	int			num_me;
	sem_t		*semaph;
	sem_t		*meal;
	sem_t		*death;
	char		*name_s;
	t_philo		*philos;
	int			falg_d;
	int			flag_f;
	
}	t_table;

long	    ft_atoi(const char *str);
long 		get_the_current(t_time time);
void	    prcise_usleep(long time_wait);
void		fill_that(int argc, char **argv, t_table *t, t_philo *p);
void		print(char *s,int id ,long long start, t_table *t);
void		routine(t_philo *p);

#endif