/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:36:23 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/30 23:10:46 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	have_diner(t_philo *philo, t_info *info)
{
	sem_wait(info->forks_sem);
	print_actions(philo, info, TAKEN_FORK);
	sem_wait(info->forks_sem);
	print_actions(philo, info, TAKEN_FORK);
	print_actions(philo, info, EATING);
	philo->is_eating = true;
	sleep_nicely(info->t_eat);
	sem_post(info->forks_sem);
	sem_post(info->forks_sem);
	sem_wait(info->eat_sem);
	philo->t_post_diner = gettime();
	philo->n_diners++;
	sem_post(info->eat_sem);
	philo->is_eating = false;
}

static void	go_to_sleep_and_think(t_philo *philo, t_info *info)
{
	print_actions(philo, info, SLEEPING);
	sleep_nicely(info->t_sleep);
	print_actions(philo, info, THINKING);
}

static void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		sem_wait(philo->info->eat_sem);
		if (!philo->is_eating && \
		gettime() - philo->t_post_diner >= philo->info->t_die)
		{
			sem_post(philo->info->eat_sem);
			print_actions(philo, philo->info, DIED);
			sem_wait(philo->info->print_sem);
			exit(1);
		}
		if (philo->info->n_eat != -1 && philo->n_diners >= philo->info->n_eat)
		{
			sem_post(philo->info->eat_sem);
			exit(0);
		}
		sem_post(philo->info->eat_sem);
		usleep(1000);
	}
}

void	life_of_philo(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &check_death, philo);
	if (philo->id % 2 == 0)
		usleep(philo->info->t_eat * 1000);
	while (true)
	{
		have_diner(philo, philo->info);
		go_to_sleep_and_think(philo, philo->info);
	}
	pthread_join(thread, NULL);
	exit(0);
}
