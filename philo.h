/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:37:23 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/19 12:59:04 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				state;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				num_philosophers;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_req;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_t		*threads;
	t_philo			*philosophers;
}					t_table;

typedef struct s_config
{
	int		num_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		meals_req;
}				t_config;

t_table	*init_table(t_config *config);
t_philo	*init_philo(t_table *table);
long	get_current_time(void);
long	get_time(long start_time);
void	precise_sleep(long duration_ms);
void	clean_table(t_table *table);
void	cleanup_philo(t_philo *philosophers);
void	*philosopher_routine(void *arg);
void	check_meals(t_philo *philo);
void	start_simulation(t_table *table, t_philo *philosophers);
int		initialize_simulation(t_config *config, t_table **table,
			t_philo **philosopherse);
#endif