/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustafa-machlouch <mustafa-machlouch@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:13:50 by mustafa-mac       #+#    #+#             */
/*   Updated: 2024/11/19 12:59:24 by mustafa-mac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	return ((ts.tv_sec * 1000) + (ts.tv_nsec / 1000000));
}

long	get_time(long start_time)
{
	long			current_time;
	struct timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	current_time = (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
	return (current_time - start_time);
}

void	precise_sleep(long duration_ms)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < duration_ms)
		usleep(1000);
}

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->threads);
	free(table);
}

void	cleanup_philo(t_philo *philosophers)
{
	free(philosophers);
}
