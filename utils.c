/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 09:01:53 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/10 15:27:54 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void prcise_usleep(long time_wait, t_philos *p)
{
    long long start;
    
    
    start = get_the_current(MICRO);
    while ((start - get_the_current(MICRO)) < time_wait)
    {
       usleep(300);
    }
}



long long get_the_current(t_time time)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    if (time == MAIL)
        return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    else if (time == MICRO)
        return ((tv.tv_sec * 1000000) + tv.tv_usec);
    return (tv.tv_sec + (tv.tv_usec / 1e6));
}


