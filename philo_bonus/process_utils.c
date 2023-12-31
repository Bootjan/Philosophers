/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:06:03 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/30 23:07:48 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static const char	*g_actions[] = {TAKEN_FORK_STR, EATING_STR, SLEEPING_STR, \
THINKING_STR, DIED_STR, SUCCESS_STR};

t_time	gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	sleep_nicely(int time)
{
	t_time	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(1);
}

void	print_actions(t_philo *philo, t_info *info, int action)
{
	t_time	time;

	if (philo)
		time = gettime() - info->start_time;
	sem_wait(info->print_sem);
	if (philo)
		printf("%lld %i", time, philo->id);
	printf("%s\n", g_actions[action - 1]);
	sem_post(info->print_sem);
}
