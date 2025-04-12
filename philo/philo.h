/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:50:49 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/10 15:58:55 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_philos
{
	pthread_t		threads;
	long			last_meal;
	int				right_f;
	int				left_f;
	int				philo_id;
	int				counter;
	struct s_table	*table;
}					t_philos;

typedef enum s_time
{
	MAIL,
	MICRO
}	t_time;

typedef struct s_table
{
	pthread_t		tabel_thread;
	int				death;
	int				number_of_philos;
	t_philos		*philos;
	long long		sesstion_start;
	pthread_mutex_t	array_of_f[200];
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	check_death;
	pthread_mutex_t	print;
	pthread_mutex_t	start;
	int				full;
	int				number_meals;
	long			time_of_eat;
	long			time_of_die;
	long			time_of_sleep;
}					t_table;

long long	get_the_current(t_time time);
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);
void		print(char *s, t_philos *p, long long start);
void		fill_philos(t_philos *p, t_table *t);
void		prcise_usleep(long time_wait, t_philos *p);
int			fill_table(t_table *table, char **args, int argc);
void		*routine(void *philos);
void		eating(t_philos *p, t_table *t);
void		monitor(t_philos *p, t_table *t);
void		joined_thread(t_table *t, t_philos *p);

#endif