/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:41:26 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/06 19:44:06 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_the_current(t_time time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time == MAIL)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time == MICRO)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (tv.tv_sec + (tv.tv_usec / 1e6));
}

void	prcise_usleep(long time_wait)
{
	long long	start;

	start = get_the_current(MICRO);
	while ((get_the_current(MICRO) - start) < time_wait)
	{
		
		usleep(100);
	}
}