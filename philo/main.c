/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 16:57:45 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/30 16:35:18 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	info->n_full = 0;
	info->running = true;
	info->start_time = gettime();
	return (0);
}

static int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	info->forks_mutex = ft_calloc(info->n_philos, sizeof(pthread_mutex_t));
	if (!info->forks_mutex)
		return (-1);
	info->philos = ft_calloc(info->n_philos, sizeof(t_philo));
	if (!info->philos)
		return (free(info->forks_mutex), -1);
	while (i < info->n_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].t_post_diner = info->start_time;
		info->philos[i].info = info;
		info->philos[i].lfork = i;
		info->philos[i].rfork = (i + 1) % info->n_philos;
		info->philos[i].n_diners = 0;
		i++;
	}
	return (0);
}

static int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
		if (pthread_mutex_init(&(info->forks_mutex[i++]), NULL) != 0)
			return (free_philos_forks(info), -1);
	if (pthread_mutex_init(&(info->print_mutex), NULL) != 0)
		return (free_philos_forks(info), -1);
	if (pthread_mutex_init(&(info->eat_mutex), NULL) != 0)
		return (free_philos_forks(info), -1);
	if (pthread_mutex_init(&(info->running_mutex), NULL) != 0)
		return (free_philos_forks(info), -1);
	return (0);
}

static int	init_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
	{
		if (pthread_create(&(info->philos[i].thread_id), NULL, life_of_philo,
				(void *)&(info->philos[i])) != 0)
			return (free_philos_forks(info), -1);
		i++;
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
	if (info.n_philos == 1)
		return (life_of_one_philo(info));
	if (init_philos(&info) == -1)
		return (print_error(ERR_MALLOC), 1);
	if (init_mutex(&info) == -1)
		return (print_error(ERR_MUTEX), 1);
	if (init_threads(&info) == -1)
		return (print_error(ERR_THREAD), 1);
	watch_life_go_by(&info);
	return (0);
}
