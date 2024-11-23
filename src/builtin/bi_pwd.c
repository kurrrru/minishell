#include "../../include/exec.h"

void bi_pwd(void)
{
    char cwd[PATH_MAX];

    if(getcwd(cwd, PATH_MAX))
        ft_putendl_fd(cwd, STDOUT_FILENO);
    else    
        perror_exit("getcwd", EXIT_FAILURE);
}
