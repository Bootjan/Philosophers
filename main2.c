/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:05:48 by bootjan           #+#    #+#             */
/*   Updated: 2023/11/23 13:23:48 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*roll_dice()
{
	int	*ret;
	int	value = (rand() % 6) + 1;

	ret = malloc(sizeof(int *));
	if (!ret)
		return (NULL);
	*ret = value;
	// printf("Value: %i\n", value);
	return ((void *)ret);
}

int	main(void)
{
	pthread_t	t1;
	int			*ret;

	srand(time(NULL));
	if (pthread_create(&t1, NULL, &roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(t1, (void **)&ret) != 0)
		return (2);
	printf("Result: %i\n", *ret);
	if (ret)
		free(ret);
	return (0);
}
