#include "../include/minirt.h"

void    put_err(char *str, t_info *info)
{
    printf("%s\n", str);
    free_info(&info);
    exit(ERROR);
}

t_info  *init_info(void)
{
    t_info *info;

    info = malloc(sizeof(t_info));
    info->canvas = NULL;
    info->object = NULL;
    return (info);
}

int parsing(char *file, t_info *info)
{
    int     fd;
    char    *line;
    char    **split;
    
    fd = open(file, O_RDONLY);
    if (fd == -1)
        put_err("File open error", &info);
    while (get_next_line(fd, &line) > 0)
    {
        split = ft_split(line, ' ');
        
        //split을 info에 담는 함수
        allo_free(split);
    }
    
    close(fd);
    return (TRUE);
}

void    free_info(t_info **info)
{
    t_object    *curr;
    t_object    *prev;
    
    if ((*info)->canvas)
        free((*info)->canvas);
    if ((*info)->object)
    {
        curr = (*info)->object;
        while (curr != NULL)
        {
            prev = curr;
            curr = prev->next;
            free(prev);
        }
    }
    free(*info);
}

int main(int argc, char **argv)
{
    t_info  *info;

    if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt") != 0)
        put_err("Input Error\n", &info);
    info = init_info();
    if (!parsing(argv[1], info))
        put_err("Parsing Error", &info);
    //rendering
    free_info(&info);

    
    return (SUCCESS);
}