#include "../../include/exec.h"
#include "builtin.h"

static bool	is_valid_env_name(char *name);
static void	add_or_update_env(t_config *config, const char *key,
				const char *value);
static void	print_invalid_identifier(char *arg);
static void	update_key_value(char *arg, char *equal_sign, t_config *config);
static void	export_no_argv(t_config *config);

void	bi_export(t_exec exec, t_config *config)
{
	int		i;
	char	*arg;
	char	*equal_sign;

	i = 1;
	if (!exec.argv[i])
		return (export_no_argv(config));
	while (exec.argv[i])
	{
		arg = exec.argv[i++];
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			update_key_value(arg, equal_sign, config);
		}
		else
		{
			if (is_valid_env_name(arg))
				add_or_update_env(config, arg, "");
			else
				print_invalid_identifier(arg);
		}
	}
}

static void	update_key_value(char *arg, char *equal_sign, t_config *config)
{
	char	*key;
	char	*value;

	key = strndup(arg, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (is_valid_env_name(key))
		add_or_update_env(config, key, value);
	free(key);
	free(value);
}

static void	print_invalid_identifier(char *arg)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	export_no_argv(t_config *config)
{
	int	j;

	j = -1;
	while (++j < config->envp_num)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(config->envp[j].key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putendl_fd(config->envp[j].value, STDOUT_FILENO);
	}
	return ;
}

static bool	is_valid_env_name(char *name)
{
	int	i;

	i = 1;
	if (!name || !(ft_isalpha(name[0]) || name[0] == '_'))
		return (false);
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

static void	add_or_update_env(t_config *config, const char *key,
		const char *value)
{
	int	i;

	i = 0;
	while (i < config->envp_num)
	{
		if (ft_strncmp(config->envp[i].key, key, ft_strlen(key)) == 0)
		{
			free(config->envp[i].value);
			config->envp[i].value = ft_strdup(value);
			return ;
		}
		i++;
	}
	if (config->envp_num >= config->envp_capacity)
	{
		config->envp_capacity *= 2;
		config->envp = realloc(config->envp, config->envp_capacity
				* sizeof(t_env));
	}
	config->envp[config->envp_num].key = strdup(key);
	config->envp[config->envp_num].value = strdup(value);
	config->envp_num++;
}
