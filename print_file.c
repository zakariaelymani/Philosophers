/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:39 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/03 09:31:16 by zel-yama         ###   ########.fr       */
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

void print(char *s, int id, long simli_time)
{
	long	current_time;

	current_time = get_the_current() - simli_time;
	printf("the philo %d at time %ld : %s",id, current_time, s);
}
