#include "../../include/exec.h"

static bool	check_echo_flag(char *argv);

void	bi_echo(t_exec exec, t_config *config)
{
	int		i;
	bool	nflag;

	i = 1;
	nflag = false;
	while (exec.argv[i] && check_echo_flag(exec.argv[i]))
	{
		nflag = true;
		i++;
	}
	while (exec.argv[i])
	{
		ft_putstr_fd(exec.argv[i], STDOUT_FILENO);
		i++;
		if (exec.argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!nflag)
		ft_putchar_fd('\n', STDOUT_FILENO);
    config->exit_status = EXIT_SUCCESS;
}

static bool	check_echo_flag(char *argv)
{
	if (!argv)
		return (false);
	if (*argv++ != '-')
		return (false);
	if (*argv++ != 'n')
		return (false);
	while (*argv)
	{
		if (*argv != 'n')
			return (false);
		argv++;
	}
	return (true);
}
