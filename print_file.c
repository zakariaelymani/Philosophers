/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/04 14:28:03 by zel-yama         ###   ########.fr       */
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

void	print(char *s, int id, long long start)
{
	long long	current_time;

	current_time = (get_the_current(MAIL) - start);
	//printf("thie current time %lld and this is the time of start %lld\n", current_time, start);
	printf("the philo %d at %lld : %s\n",id, current_time, s);
}

void error_exit(char *s)
{
    ft_putstr_fd(s, 2);
    ft_free(NULL, 1);
    exit(1);
    
}