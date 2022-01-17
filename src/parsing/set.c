#include "../../include/minirt.h"

int check_int(char *str)
{
    if(*str == '-')
        str++;
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return (FALSE);
        str++;
    }
    return (TRUE);
}

int check_double(char *str)
{
    int i;
    int dot_flag;

    i = 0;
    dot_flag = FALSE;
    if (str[i] == '-')
        i++;
    while (str[i])
    {
        if (!dot_flag && str[i] == '.')
            dot_flag = TRUE;
        else if (dot_flag && str[i] == '.')
            return (FALSE);
        else if (!is_digit(str[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int set_ambient(t_canvas *canvas, char **split)
{
    char    **element;

    if ()
    canvas->ambient = split[0];
    element = ft_split(split[1], ',');
    canvas->ambient_color = ;
}

//check_int 체크
//check_double 체크
//split[0]가 range안인지 옳으면 담고, 틀리면 error
//split[1]가 vector인지, 0~255인지
//split[i] != 0는 에러

int set_camara(t_canvas *canvas, char **split)
{
    
}

int set_light(t_canvas *canvas, char **split)
{}

int set_plane(t_info *info, char **split)
{}

int set_sphere(t_info *info, char **split)
{}

int set_cylinder(t_info *info, char **split)
{}