/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 09:01:53 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/09 11:49:52 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_all_eating(t_table *t)
{
    int i;

    i = 0;
    if (t->number_meals)
    {
        while(i < t->number_of_philos)
        {
            if (t->number_meals != t->philos[i].counter)
            {
                return (0);
            }
            i++;
        }
        return (1);
    }
    return (0);
}

void prcise_usleep(long time_wait)
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


