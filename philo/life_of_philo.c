/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   life_of_philo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/23 15:45:19 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/30 17:45:56 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_to_sleep_and_think(t_philo *philo, t_info *info)
{
	if (!still_running(info))
		return (-1);
	print_actions(philo, &(info->print_mutex), SLEEPING);
	sleep_nicely(info->t_sleep);
	if (!still_running(info))
		return (-1);
	print_actions(philo, &(info->print_mutex), THINKING);
	return (0);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->info->t_eat * 1000);
	while (true)
	{
		if (!still_running(philo->info))
			return (NULL);
		have_diner(philo, philo->info);
		if (go_to_sleep_and_think(philo, philo->info) == -1)
			return (NULL);
	}
	return (NULL);
}
