/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bootjan <bootjan@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 16:58:58 by bschaafs      #+#    #+#                 */
/*   Updated: 2023/12/30 17:46:02 by bschaafs      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>

# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_ZERO "One of the arguments was zero"
# define ERR_MALLOC "Malloc error"
# define ERR_MUTEX "Mutex error"
# define ERR_THREAD "Thread error"

# define INT_MAX_STR "2147483647"

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
	int				n_full;
	bool			running;
	t_time			start_time;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	running_mutex;
	struct s_philo	*philos;
}	t_info;

typedef struct s_philo
{
	int				id;
	t_time			t_post_diner;
	int				lfork;
	int				rfork;
	int				n_diners;
	t_info			*info;
	pthread_t		thread_id;
}	t_philo;

// ### UTILS ###################################################################
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	print_error(const char *str);
void	print_actions(t_philo *philo, pthread_mutex_t *print_mutex, int action);

// ### THREAD UTILS ############################################################
void	free_philos_forks(t_info *info);
bool	still_running(t_info *info);
void	sleep_nicely(int time);
t_time	gettime(void);
int		life_of_one_philo(t_info info);

// ### HANDELING ARGS ##########################################################
int		ft_atoi(const char *str);
int		not_int(int argc, const char **argv);

// ### LIFE OF PHILO ###########################################################
void	watch_life_go_by(t_info *info);
void	have_diner(t_philo *philo, t_info *info);
void	*life_of_philo(void *arg);

#endif