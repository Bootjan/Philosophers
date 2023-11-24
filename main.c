/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:47:08 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/22 18:39:44 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mail = 0;

void	*routine(void *ptr)
{
	pthread_mutex_t	*mutex = ptr;
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(mutex);
		mail++;
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t		ths[8];
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 8; i++)
	{
		if (pthread_create(&(ths[i]), NULL, &routine, &mutex) != 0)
			return (1);
		printf("Started thread %i\n", i);
	}
	for (int i = 0; i < 8; i++)
	{
		if (pthread_join(ths[i], NULL) != 0)
			return (1);
		printf("Ended thread %i\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Mail: %i\n", mail);
	return (0);
}
