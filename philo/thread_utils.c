/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bschaafs <bschaafs@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 19:00:01 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/30 16:14:40 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_nicely(int time)
{
	t_time	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(1);
}

bool	still_running(t_info *info)
{
	bool	ret;

	pthread_mutex_lock(&(info->running_mutex));
	ret = info->running;
	pthread_mutex_unlock(&(info->running_mutex));
	return (ret);
}

t_time	gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	free_philos_forks(t_info *info)
{
	if (info->forks_mutex)
		free(info->forks_mutex);
	if (info->philos)
		free(info->philos);
}

int	life_of_one_philo(t_info info)
{
	printf("0 1 has taken a fork\n");
	printf("%i 1 died\n", info.t_die);
	return (0);
}
