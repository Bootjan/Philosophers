/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:04:41 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/30 23:20:28 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_info *info)
{
	int	i;

	i = 0;
	if (!info->pids)
		return ;
	while (i < info->n_philos && info->pids[i] != 0)
		kill(info->pids[i++], SIGKILL);
}

void	close_semaphores(t_info *info)
{
	sem_close(info->print_sem);
	sem_close(info->forks_sem);
	sem_close(info->eat_sem);
}

void	watch_life_go_by(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i++ < info->n_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_processes(info);
			break ;
		}
	}
	if (status == 0)
		print_actions(NULL, info, SUCCESS);
	close_semaphores(info);
	free_pids_philos(info);
}
