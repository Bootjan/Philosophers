/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handling_args.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 17:14:46 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/21 14:46:21 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
		result = result * 10 + str[i++] - '0';
	return (result);
}

static int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static bool	correct_entry(const char *str)
{
	int	len;

	len = 0;
	if (!str[0])
		return (false);
	while (str[len])
	{
		if (str[len] < '0' || str[len] > '9')
			return (false);
		len++;
	}
	if (len > 10)
		return (false);
	if (len < 10)
		return (true);
	if (ft_strcmp(str, INT_MAX_STR) > 0)
		return (false);
	return (true);
}

int	not_int(int argc, const char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
		if (!correct_entry(argv[i++]))
			return (1);
	return (0);
}
