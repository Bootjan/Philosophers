/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:17:52 by bootjan           #+#    #+#             */
/*   Updated: 2023/12/30 23:18:01 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_error(const char *str)
{
	if (!str)
		return ;
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total_size;

	total_size = size * nmemb;
	result = malloc(total_size);
	if (!result)
		return (NULL);
	if (size > 0)
		memset(result, 0, total_size);
	return (result);
}

void	free_pids_philos(t_info *info)
{
	if (info->philos)
		free(info->philos);
	if (info->pids)
		free(info->pids);
}

void	clean_up(t_info *info)
{
	close_semaphores(info);
	free_pids_philos(info);
	kill_processes(info);
}
