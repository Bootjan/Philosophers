/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:29:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/30 23:24:48 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>

# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_ZERO "One of the arguments was zero"
# define ERR_MALLOC "Malloc error"
# define ERR_SEM "Semaphore error"
# define ERR_THREAD "Thread error"
# define ERR_FORK "Fork error"

# define INT_MAX_STR "2147483647"

# define FORKS_SEM "1"
# define PRINT_SEM "2"
# define EAT_SEM "3"

# define TAKEN_FORK 1
# define TAKEN_FORK_STR " has taken a fork"

# define EATING 2
# define EATING_STR " is eating"

# define SLEEPING 3
# define SLEEPING_STR " is sleeping"

# define THINKING 4
# define THINKING_STR " is thinking"

# define DIED 5
# define DIED_STR " died"

# define SUCCESS 6
# define SUCCESS_STR "All philosophers have eaten!"

typedef long long	t_time;

typedef struct s_info
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				*pids;
	bool			running;
	t_time			start_time;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*eat_sem;
	struct s_philo	*philos;
}	t_info;

typedef struct s_philo
{
	int		id;
	int		n_diners;
	bool	is_eating;
	t_time	t_post_diner;
	t_info	*info;
}	t_philo;

// ### LIFE OF PHILO ###########################################################
void	watch_life_go_by(t_info *info);
void	life_of_philo(t_philo *philo);
void	kill_processes(t_info *info);
void	close_semaphores(t_info *info);

// ### HANDLING ARGUMENTS ######################################################
int		ft_atoi(const char *str);
int		not_int(int argc, const char **argv);

// ### PROCESS UTILS ###########################################################
t_time	gettime(void);
void	print_actions(t_philo *philo, t_info *info, int action);
void	sleep_nicely(int time);

// ### UTILS ###################################################################
void	print_error(const char *str);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	free_pids_philos(t_info *info);
void	clean_up(t_info *info);

#endif