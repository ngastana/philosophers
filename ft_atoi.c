/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:51:28 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/04 11:31:36 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if (c != '\t' && c != '\n' && c != '\v' \
		&& c != '\f' && c != '\r' && c != ' ')
		return (0);
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	sum;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	sum = 0;
	while (ft_isdigit(str[i]))
	{
		sum = sum * 10 + (str[i] - '0');
		if (sum < 0)
			return ((sign != -1) * -1);
		i++;
	}
	return (sum * sign);
}
