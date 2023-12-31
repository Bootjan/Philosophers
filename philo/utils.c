/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/20 11:17:52 by bootjan       #+#    #+#                 */
/*   Updated: 2023/12/30 16:37:41 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*g_actions[] = {TAKEN_FORK_STR, EATING_STR, SLEEPING_STR, \
THINKING_STR, DIED_STR, SUCCESS_STR};

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

void	print_actions(t_philo *philo, pthread_mutex_t *print_mutex, int action)
{
	t_time	time;

	if (philo)
		time = gettime() - philo->info->start_time;
	pthread_mutex_lock(print_mutex);
	if (philo)
		printf("%lld %i", time, philo->id);
	printf("%s\n", g_actions[action - 1]);
	pthread_mutex_unlock(print_mutex);
}
