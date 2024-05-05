/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:00:33 by ngastana          #+#    #+#             */
/*   Updated: 2024/05/05 14:00:59 by ngastana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h> // for memset
# include <stdint.h> // to store miliseconds
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef COLORS_H
#  define COLORS_H

#  define BOLD       "\001\033[1m\002"
#  define UNDERLINE  "\001\033[4m\002"
#  define BLACK      "\001\033[30m\002"
#  define RED        "\001\033[31m\002"
#  define GREEN      "\001\033[32m\002"
#  define YELLOW     "\001\033[33m\002"
#  define BLUE       "\001\033[34m\002"
#  define MAGENTA    "\001\033[35m\002"
#  define CYAN       "\001\033[36m\002"
#  define WHITE      "\001\033[37m\002"
#  define RESET      "\001\033[0m\002"

# endif

typedef struct s_philo 
{
	int				num;
	uint64_t		last_meal;
	int				meals_count;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;	
	pthread_t		thread;	
	struct s_args	*args;
}	t_philo;

typedef struct s_args 
{
	int					philo_count;
	bool				everyphilo_full;
	bool				someone_die;
	int					time2die;
	int					time2eat;
	int					max_meals;
	int					time2sleep;
	pthread_mutex_t		mutex;
	uint64_t			start_time;
	int					philo_finish;
	struct s_philo		philo[200];
}	t_args;

/*MAIN*/
int			main(int argc, char **argv);
int			ft_initialize_args(t_args *args, char **argv);
bool		ft_initialize_philosophers(t_args *args);
bool		ft_waiter(t_args *args, int i);

/*ATOI*/
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
int			ft_isdigit(int c);

/*UTILS*/
bool		is_int(char *str);
size_t		ft_timer(void);
void		ft_usleep(size_t milli);

/*PHILOS_WORKING*/
void		*philos_working(void *hinder);
bool		get_fork(t_philo *philo);
bool		philos_sleep_think(t_philo *philo);
bool		philos_state(t_philo *philo, char *str);
bool		should_stop(t_philo *philo);

#endif
