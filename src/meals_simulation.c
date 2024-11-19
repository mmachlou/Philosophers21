/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:13:44 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/19 13:00:43 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	monitor_simulation(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->is_dead)
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);
		usleep(1000);
	}
}

int	initialize_simulation(t_config *config, t_table **table,
									t_philo **philosopherse)
{
	*table = init_table(config);
	if (!*table)
		return (1);
	*philosopherse = init_philo(*table);
	if (!*philosopherse)
	{
		clean_table(*table);
		return (1);
	}
	return (0);
}

void	start_simulation(t_table *table, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_create(&table->threads[i],
			NULL, philosopher_routine, &philosophers[i]);
		i++;
	}
	monitor_simulation(table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}

static int	check_all_philosophers_ate(t_table *table)
{
	int	i;

	if (table == NULL)
	{
		printf("Error: table is NULL in check_all_philosophers_ate\n");
		return (1);
	}
	if (table->philosophers == NULL)
	{
		printf("Error: philosophers array is NULL in ");
		printf("check_all_philosophers_ate\n");
		return (1);
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		if (table->philosophers[i].meals_eaten < table->meals_req)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_meals(t_philo *philo)
{
	int		i;
	long	current_time;

	current_time = get_time(philo->table->start_time);
	if (philo->table->meals_req > 0 && check_all_philosophers_ate(philo->table))
	{
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->is_dead = 1;
		i = 0;
		while (i < philo->table->num_philosophers)
		{
			if (philo->table->philosophers[i].meals_eaten
				< philo->table->meals_req)
			{
				printf("%ld Philosopher %d has died\n",
					current_time, philo->table->philosophers[i].id);
			}
			i++;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
	}
}
