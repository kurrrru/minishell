#include "../../include/exec.h"

void bi_pwd(t_config *config)
{
    char cwd[PATH_MAX];

    if(getcwd(cwd, PATH_MAX))
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        config->exit_status = EXIT_SUCCESS;
    }
    else    
    {
        ft_putendl_fd("getcwd", EXIT_FAILURE);
        config->exit_status = EXIT_INVALID_INPUT;
    }    
}
