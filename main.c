/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:47:08 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 14:25:35 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mail = 0;

void	*routine(void *ptr)
{
	for (int i = 0; i < 1000000; i++)
		mail++;
	return (ptr);
}

int	main(void)
{
	pthread_t	t1, t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	printf("Mail: %i\n", mail);
	return (0);
}
