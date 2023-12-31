/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stop_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 18:54:09 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/30 16:09:29 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_running(t_info *info)
{
	pthread_mutex_lock(&(info->running_mutex));
	info->running = false;
	pthread_mutex_unlock(&(info->running_mutex));
}

static int	check_philos(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->eat_mutex));
	if (gettime() - philo->t_post_diner >= info->t_die)
	{
		pthread_mutex_unlock(&(info->eat_mutex));
		stop_running(info);
		print_actions(philo, &(info->print_mutex), DIED);
		return (-1);
	}
	else if (info->n_eat != -1 && philo->n_diners >= info->n_eat)
		info->n_full++;
	pthread_mutex_unlock(&(info->eat_mutex));
	if (info->n_full == info->n_philos)
	{
		stop_running(info);
		print_actions(NULL, &(info->print_mutex), SUCCESS);
		return (-1);
	}
	return (0);
}

static void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
		pthread_join((info->philos)[i++].thread_id, NULL);
	i = 0;
	while (i < info->n_philos)
		pthread_mutex_destroy(&(info->forks_mutex[i++]));
	pthread_mutex_destroy(&(info->print_mutex));
	pthread_mutex_destroy(&(info->running_mutex));
	pthread_mutex_destroy(&(info->eat_mutex));
	free_philos_forks(info);
}

void	watch_life_go_by(t_info *info)
{
	int		i;
	bool	living;

	living = true;
	while (living)
	{
		i = info->n_philos;
		info->n_full = 0;
		while (living && i-- > 0)
			if (check_philos(info, &(info->philos[i])) != 0)
				living = false;
		if (!living)
			break ;
		usleep(10);
	}
	join_threads(info);
}
