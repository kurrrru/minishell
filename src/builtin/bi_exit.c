#include "../../include/exec.h"

static bool	is_num(const char *str);

void	bi_exit(t_exec exec, t_config *config)
{
	int	exit_code;

	exit_code = config->exit_status;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (exec.argv[1])
	{
		if (is_num(exec.argv[1]))
		{
			exit_code = ft_atoi(exec.argv[1]);
			if (exec.argv[2])
				perror_exit("exit: too many arguments", EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(exec.argv[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit_code = 255;
		}
	}
	exit(exit_code);
}

static bool	is_num(const char *str)
{
	if (!str || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
