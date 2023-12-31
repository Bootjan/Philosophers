/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:31:11 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/30 23:24:59 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_info(t_info *info, int argc, const char **argv)
{
	memset(info, 0, sizeof(t_info));
	info->n_philos = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_eat = -1;
	if (argc == 6)
		info->n_eat = ft_atoi(argv[5]);
	if (!info->n_philos || !info->t_die || !info->t_eat || !info->t_sleep
		|| !info->n_eat)
		return (-1);
	info->running = true;
	return (0);
}

static int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	info->pids = ft_calloc(info->n_philos, sizeof(int));
	if (!info->pids)
		return (-1);
	info->philos = ft_calloc(info->n_philos, sizeof(t_philo));
	if (!info->philos)
		return (free(info->pids), -1);
	while (i < info->n_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].n_diners = 0;
		info->philos[i].info = info;
		info->philos[i].t_post_diner = gettime();
		info->philos[i].is_eating = false;
		i++;
	}
	return (0);
}

static void	init_sem(t_info *info)
{
	info->forks_sem = sem_open(FORKS_SEM, O_CREAT, 0644, info->n_philos);
	sem_unlink(FORKS_SEM);
	info->print_sem = sem_open(PRINT_SEM, O_CREAT, 0644, 1);
	sem_unlink(PRINT_SEM);
	info->eat_sem = sem_open(EAT_SEM, O_CREAT, 0644, 1);
	sem_unlink(EAT_SEM);
}

static int	init_processes(t_info *info)
{
	int	i;
	int	pid;

	i = 0;
	pid = 1;
	info->start_time = gettime();
	while (pid > 0 && i < info->n_philos)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			life_of_philo(&(info->philos[i]));
		else
			info->pids[i++] = pid;
	}
	return (0);
}

int	main(int argc, const char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6 || not_int(argc, argv))
		return (print_error(ERR_INPUT), 1);
	if (init_info(&info, argc, argv) == -1)
		return (print_error(ERR_ZERO), 1);
	init_sem(&info);
	if (init_philos(&info) == -1)
		return (print_error(ERR_MALLOC), clean_up(&info), 1);
	if (init_processes(&info) == -1)
		return (print_error(ERR_FORK), clean_up(&info), 1);
	watch_life_go_by(&info);
}
