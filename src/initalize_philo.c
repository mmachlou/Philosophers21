/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:14:01 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/18 12:33:58 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	init_philo_data(t_philo *philosophers, t_table *table, int id)
{
	philosophers->id = id + 1;
	philosophers->state = 0;
	philosophers->meals_eaten = 0;
	philosophers->last_meal_time = table->start_time;
	philosophers->left_fork = &table->forks[id];
	philosophers->right_fork = &table->forks[(id + 1)
		% table->num_philosophers];
	philosophers->table = table;
}

t_philo	*init_philo(t_table *table)
{
	int		i;
	t_philo	*philosophers;

	philosophers = malloc(sizeof(t_philo) * table->num_philosophers);
	if (!philosophers)
	{
		perror("Failed to allocate memory for philosophers");
		free(table->forks);
		free(table);
		return (NULL);
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		init_philo_data(&philosophers[i], table, i);
		i++;
	}
	table->philosophers = philosophers;
	return (philosophers);
}
