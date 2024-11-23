#ifndef BUILTIN_H
# define BUILTIN_H

# include "config.h"
# include "include.h"
# include "macro.h"
# include "util.h"

struct s_exec;
typedef struct s_exec	t_exec;

void					bi_pwd(t_config *config);
void					bi_unset(t_exec exec, t_config *config);
bool					is_builtin_fxn(t_node *node);
void					exec_bi_command(t_exec exec, t_config *config);

void					bi_cd(t_exec exec, t_config *config);

void	bi_echo(t_exec exec, t_config *config);

void					bi_env(t_config *config);

void					bi_exit(t_exec exec, t_config *config);

void					bi_export(t_exec exec, t_config *config);

void	set_builtin_path(t_exec *exec, t_node *node);

#endif
