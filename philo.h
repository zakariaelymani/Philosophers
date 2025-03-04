/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:50:49 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/04 14:16:47 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_philos
{
	pthread_t treads;
	pthread_mutex_t	meal;
	long			the_last_meal;
	int				right_frok;
	int				left_frok;
	int				the_philo_id;
	int				counter;
	struct s_table *table;
}   t_philos;

typedef enum s_time
{
	MAIL,
	MICRO
}	t_time;

typedef struct s_table
{
	pthread_t		tabel_thread;
	int				similation_runing;
	int         	number_of_philos;
	t_philos		*philos;
	long long		sesstion_start;
	pthread_mutex_t	*array_of_fork;
	pthread_mutex_t	print_die;
	pthread_mutex_t	meal_lock;
	long			the_number_of_meals;
	long			time_of_eat;
	long			time_of_die;
	long			time_of_sleep;
}   				t_table;
void print_struct(t_table *t);
long long	get_the_current(t_time time);
void		fill_struct(t_table **table, t_philos **p, char **args, int argc);
void		destory(t_philos *p, int numbers);
void		join_threads(t_table *table);
void		create_pthread(t_philos *phil);
void		*routine(void *t);
int			check_all_eating(t_table *t);
void		*monitor(void *t);
void		init_struct(int numbs, t_philos **philos, t_table *table);
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*routine(void *t);
void		*monitor(void *t);
void		ft_putstr_fd(char *s, int fd);
void		*ft_malloc(size_t size);
void		ft_free(void *ptr, int flag);
void		print(char *s, int id, long long start);
void		error_exit(char *s);
void		prcise_usleep(long time_wait);