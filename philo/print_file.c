/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/29 11:47:27 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print(char *s, t_philos *p, long long start)
{
	long long	current_time;

	pthread_mutex_lock(&p->table->print);
	if (!p->table->death && !p->table->full)
	{
		current_time = (get_the_current(MAIL) - start);
		printf("%lld [%d] %s\n", current_time, p->philo_id, s);
	}
	pthread_mutex_unlock(&p->table->print);
}
