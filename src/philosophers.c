/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:13:44 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/18 12:38:50 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	validate_arguments(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo num_philosophers	time_to_die ");
		printf("time_to_eat time_to_sleep meals_req\n");
		return (1);
	}
	return (0);
}

static int	parse_arguments(char **av, t_config *config, int ac)
{
	config->num_philosophers = atoi(av[1]);
	config->time_to_die = atoi(av[2]);
	config->time_to_eat = atoi(av[3]);
	config->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		config->meals_req = atoi(av[5]);
	else
		config->meals_req = -1;
	if (config->num_philosophers <= 0 || config->time_to_die <= 0
		|| config->time_to_eat <= 0 || config->time_to_sleep <= 0
		|| (ac == 6 && config->meals_req <= 0))
	{
		printf("Error: All arguments must be positive integers.\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_config	config;
	t_table		*table;
	t_philo		*philosophers;

	if (validate_arguments(ac) || parse_arguments(av, &config, ac))
		return (1);
	if (initialize_simulation(&config, &table, &philosophers))
		return (1);
	start_simulation(table, philosophers);
	cleanup_philo(philosophers);
	clean_table(table);
	return (0);
}
