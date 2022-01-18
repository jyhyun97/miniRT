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

int check_vector(char **element)
{
    int i;

    i = 0;
    while (element[i] != 0)
    {   
        if (!check_double(element[i]))
            return (FALSE);
        i++;
    }
    if (i != 3)
        return (FALSE);
    return (TRUE);
}

int check_color(t_color color)
{
    if (0.0 > color.x || color.x > 255.0)
        return (FALSE);
    else if (0.0 > color.y || color.y > 255.0)
        return (FALSE);
    else if (0.0 > color.z || color.z > 255.0)
        return (FALSE);
    return (TRUE);
}

int check_normal(t_vector normal)
{
    if (-1.0 > normal.x || normal.x > 1.0)
        return (FALSE);
    else if (-1.0 > normal.y || normal.y > 1.0)
        return (FALSE);
    else if (-1.0 > normal.z || normal.z > 1.0)
        return (FALSE);
    return (TRUE);
}