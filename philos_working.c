/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_working.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:11:11 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 13:55:56 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex);
	if (philo->args->someone_die || philo->args->everyphilo_full)
	{
		pthread_mutex_unlock(&philo->args->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->mutex);
	return (false);
}

bool philos_state(t_philo *philo, char *str)
{
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(&philo->args->mutex);
	printf(CYAN "   %llu   " RESET, ft_timer() - philo->args->start_time);
	printf("%d %s\n" RESET, philo->num, str);
	pthread_mutex_unlock(&philo->args->mutex);	
	return (true);
}

bool philos_sleep_think(t_philo *philo)
{
	if (!philos_state(philo, "is sleeping"))
		return (false);
	ft_usleep(philo->args->time2sleep);
	if (!philos_state(philo, "is thinking"))
		return (false);
	return (true);
}

bool	get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	if (!philos_state(philo, "has taken the fork"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	pthread_mutex_lock(philo->r_fork);
	if (!philos_state(philo, "has taken the fork"))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
}

void *philos_working(void *hinder)
{
	t_philo	*philos;

	philos = (t_philo *)hinder;
	if (philos->num % 2 == 0)
		ft_usleep(1);
 	while (!should_stop(philos))
	{
		if (!get_fork(philos))
			break;
		pthread_mutex_lock(&philos->args->mutex);	
		philos->meals_count++;
		philos->last_meal = ft_timer();
		pthread_mutex_unlock(&philos->args->mutex);
		philos_state(philos, GREEN "is eating");
		ft_usleep(philos->args->time2eat);
		pthread_mutex_lock(&philos->args->mutex);
		if (philos->meals_count == philos->args->max_meals)
			philos->args->philo_finish += 1;
		pthread_mutex_unlock(&philos->args->mutex);
		pthread_mutex_unlock(&philos->l_fork);
		pthread_mutex_unlock(philos->r_fork);
		if (!philos_sleep_think(philos))
			break;
	}
	return (NULL);
}
