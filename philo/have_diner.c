/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   have_dinner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 16:15:21 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/30 17:46:08 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks_even(t_philo *philo, t_info *info)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*output;

	forks = info->forks_mutex;
	output = &(info->print_mutex);
	pthread_mutex_lock(&(forks[philo->lfork]));
	print_actions(philo, output, TAKEN_FORK);
	pthread_mutex_lock(&(forks[philo->rfork]));
	print_actions(philo, output, TAKEN_FORK);
	print_actions(philo, output, EATING);
}

static void	take_forks_uneven(t_philo *philo, t_info *info)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*output;

	forks = info->forks_mutex;
	output = &(info->print_mutex);
	pthread_mutex_lock(&(forks[philo->rfork]));
	print_actions(philo, output, TAKEN_FORK);
	pthread_mutex_lock(&(forks[philo->lfork]));
	print_actions(philo, output, TAKEN_FORK);
	print_actions(philo, output, EATING);
}

static void	update_done_eating(t_philo *philo, t_info *info)
{
	philo->n_diners++;
	pthread_mutex_lock(&(info->eat_mutex));
	philo->t_post_diner = gettime();
	pthread_mutex_unlock(&(info->eat_mutex));
}

void	have_diner(t_philo *philo, t_info *info)
{
	if (philo->id % 2 == 0)
		take_forks_even(philo, info);
	else
		take_forks_uneven(philo, info);
	sleep_nicely(info->t_eat);
	pthread_mutex_unlock(&(info->forks_mutex[philo->lfork]));
	pthread_mutex_unlock(&(info->forks_mutex[philo->rfork]));
	update_done_eating(philo, info);
}
