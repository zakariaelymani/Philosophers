/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbagecollecter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:38:11 by zel-yama          #+#    #+#             */
/*   Updated: 2025/03/03 09:37:32 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(void *ptr, int flag)
{
	static void	*collecter[100000];
	static int	i;
	int			j;

	if (flag)
	{
		j = 0;
		while (collecter[j])
			free(collecter[j++]);
	}
	else
		collecter[i++] = ptr;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		(ft_putstr_fd("Error\nmalloc failed\n", 1), ft_free(NULL, 1), exit(2));
	ft_free(ptr, 0);
	return (ptr);
}