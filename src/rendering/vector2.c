#include "../../include/minirt.h"

t_vector    vec_unit(t_vector vec)
{
    double  len;
    
    len = sqrt(vec_len2(vec));
    return (vec_div_(vec, len));
}

double      vec_dot(t_vector vec1, t_vector vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vector    vec_cross(t_vector vec1, t_vector vec2)
{
    t_vector    new;

    new.x = vec1.y * vec2.z - vec1.z * vec2.y;
    new.y = vec1.z * vec2.x - vec1.x * vec2.z;
    new.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return (new);
}

double      vec_len2(t_vector vec)
{
    return (vec_dot(vec, vec));
}

t_vector    vec_max(t_vector vec, double max)
{
    if (vec.x > max)
        vec.x = max;
    if (vec.y > max)
        vec.y = max;
    if (vec.z > max)
        vec.z = max;
    return (vec);
}