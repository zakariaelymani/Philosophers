/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-yama <zel-yama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:16:59 by zel-yama          #+#    #+#             */
/*   Updated: 2025/04/29 11:25:29 by zel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	res;

	(1) && (i = 0, res = 0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (-1);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	if (!str[i])
		return (-1);
	while (str[i])
	{
		res *= 10;
		res += (str[i] - '0');
		if (ft_isdigit(str[i]) == 0 || res > INT_MAX)
			return (-1);
		i++;
	}
	return (res);
}
