/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:13:56 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/18 12:31:41 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
}

static t_table	*allocate_table(int num_philosophers)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		perror("Failed to allocate memory for table");
		return (NULL);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);
	if (!table->forks)
	{
		perror("Failed to allocate memory for forks");
		free(table);
		return (NULL);
	}
	return (table);
}

static t_table	*allocate_init_table(t_config *config)
{
	t_table	*table;

	table = allocate_table(config->num_philosophers);
	if (!table)
		return (NULL);
	table->num_philosophers = config->num_philosophers;
	table->time_to_die = config->time_to_die;
	table->time_to_eat = config->time_to_eat;
	table->time_to_sleep = config->time_to_sleep;
	table->meals_req = config->meals_req;
	table->is_dead = 0;
	table->start_time = get_current_time();
	return (table);
}

t_table	*init_table(t_config *config)
{
	t_table	*table;

	table = allocate_init_table(config);
	if (!table)
		return (NULL);
	table->threads = malloc(sizeof(pthread_t) * config->num_philosophers);
	if (!table->threads)
	{
		perror("Failed to allocate memory for threads");
		free(table->forks);
		free(table);
		return (NULL);
	}
	init_forks(table);
	table->philosophers = init_philo(table);
	if (!table->philosophers)
	{
		printf("Error: philosophers array failed to initialize\n");
		return (NULL);
	}
	return (table);
}
