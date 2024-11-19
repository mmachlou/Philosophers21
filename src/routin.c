/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:13:44 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/19 13:01:00 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	think(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->table->print_lock);
	current_time = get_time(philo->table->start_time);
	printf("%ld Philosopher %d is thinking\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

static void	eat(t_philo *philo)
{
	long	current_time;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	pthread_mutex_lock(&philo->table->print_lock);
	current_time = get_time(philo->table->start_time);
	printf("%ld Philosopher %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	precise_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	sleep_philo(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->table->print_lock);
	current_time = get_time(philo->table->start_time);
	printf("%ld Philosopher %d is sleeping\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
	precise_sleep(philo->table->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo == NULL || philo->table == NULL)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->is_dead)
		{
			printf("%ld Philosopher %d has died\n",
				get_time(philo->table->start_time),
				philo->id);
			pthread_mutex_unlock(&philo->table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		think(philo);
		eat(philo);
		sleep_philo(philo);
		check_meals(philo);
	}
	return (NULL);
}
