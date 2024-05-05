/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:22:58 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 13:45:02 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_int(char *str)
{
	char	*max_int;
	size_t	len;

	max_int = "2147483647";
	if (*str == '+')
		str++;
	len = ft_strlen(str);
	if (len > 10)
		return (false);
	if (len == 10)
		while (ft_isdigit(*str) && *str <= *max_int++)
			str++;
	else
		while (ft_isdigit(*str))
			str++;
	return (!*str && true); //si str esta al final de la cadena '\0' es true, sino false
}

size_t	ft_timer(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return(tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL); //para tene el tiempo en milisegundos, la ULL para indicar que el resultado debe ser un entero sin signo de 64 bits
}

void	ft_usleep(size_t milli)
{
	size_t	start;

	start = ft_timer();
	while (ft_timer() - start < milli)
		usleep(500);
}