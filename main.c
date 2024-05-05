/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:54:39 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 14:27:59 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_initialize_args(t_args *args, char **argv)
{
	int i;

	i = 0;
	while (argv[++i])
		if (!is_int(argv[i]))
			return (printf("Invalid arguments\n"), -1);
 	args->philo_count = ft_atoi(argv[1]);
	if (args->philo_count > 200 || args->philo_count < 1 )
		return (0);
	args->time2die = ft_atoi(argv[2]);
	args->time2eat = ft_atoi(argv[3]);
	args->time2sleep = ft_atoi(argv[4]);
	args->max_meals = -1;
	args->philo_finish = 0;
	if (argv[5])
		args->max_meals = ft_atoi(argv[5]);
	pthread_mutex_init(&args->mutex, NULL);
	args->start_time = ft_timer();
	return (1);
}

bool	ft_initialize_philosophers(t_args *args)
{
	int i;

	i = -1;
	if (args->philo_count == 1)
	{
		printf("   0   1 has taken the fork\n");
		printf(RED BOLD "   %llu  1 died\n",
				(unsigned long long)args->time2die);
		return (false);	
	}
	while (++i < args->philo_count)
	{
		args->philo[i].num = i + 1;
		args->philo[i].last_meal = args->start_time;
		if (pthread_mutex_init (&args->philo[i].l_fork, NULL) != 0)
			return (false);
		else if (i + 1 == args->philo_count)
			args->philo[i].r_fork = &args->philo[0].l_fork;
		else 
			args->philo[i].r_fork = &args->philo[i +1].l_fork;
		args->philo[i].args = args;
		args->philo[i].meals_count = 0;
	}
	return (true);
}

void	*ft_waiter(void *hinder)
{
	t_args	*args;
	static int		i;

	args = (t_args *) hinder;
	while (1)
	{
		pthread_mutex_lock(&args->mutex);
		if (ft_timer() - args->philo[i].last_meal
			>= (unsigned long long)args->time2die
			|| args->philo_finish == args->philo_count)
		{
			if (args->philo_count == args->philo_finish)
			{
				args->everyphilo_full = true;
				pthread_mutex_unlock(&args->philo[i].l_fork);
				printf(BOLD MAGENTA "Every philosopher has eaten %d times\n", args->max_meals);
			}
			else
			{
				args->someone_die = true;
				pthread_mutex_unlock(&args->philo[i].l_fork);
				printf(RED BOLD "   %llu   %d died\n",
					ft_timer() - args->start_time, args->philo[i].num);
			}
			pthread_mutex_unlock(&args->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&args->mutex);
	}
}

int	main(int argc, char **argv)
{
	t_args		args;
	int			i;
	pthread_t	waiter;

	i = -1;
	memset(&args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6 || ft_initialize_args(&args, argv) != 1)
		return (printf(BOLD CYAN "philo_count time2die time2eat time2sleep [meals_count]\n"), 1);
	if (!ft_initialize_philosophers(&args))
		return (0);
 	while (++i < args.philo_count)
		if (pthread_create(&args.philo[i].thread, NULL, philos_working, &args.philo[i])!= 0)
			return (printf("problems in pthread_create\n"), -1);
	if (pthread_create(&waiter, NULL, ft_waiter, &args)!= 0)
		return (printf("problems in pthread_create\n"), -1);		
	i = 0;
	while (!should_stop(&args.philo[i]))
	{
		if (pthread_join(args.philo[i].thread, NULL) != 0)
			return (printf("problems in pthread_join philos\n"), -1);
		if (pthread_join(waiter, NULL) != 0)
			return (printf("problems in pthread_join waiter\n"), -1);
		if (i + 1 == args.philo_count)
			i = -1;
		i++;
	}
	i = -1;
	while (++i < args.philo_count)
		if (pthread_mutex_destroy(&args.philo[i].l_fork) != 0)
			return (printf("problems in pthread_mutex_destroy\n"), -1);
	if (pthread_mutex_destroy(&args.mutex) != 0)
			return (printf("problems in pthread_mutex_destroy\n"), -1);
	return (0);
}
