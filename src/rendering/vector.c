#include "minirt.h"

t_vector    vec_plus(t_vector vec1, t_vector vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    return (vec1);
}

t_vector    vec_plus_(t_vector vec1, double t)
{
    vec1.x += t;
    vec1.y += t;
    vec1.z += t;
    return (vec1);
}
t_vector    vec_minus(t_vector vec1, t_vector vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    return (vec1);

}

t_vector    vec_minus_(t_vector vec1, double t)
{
    vec1.x -= t;
    vec1.y -= t;
    vec1.z -= t;
    return (vec1);
}

t_vector    vec_mult(t_vector vec1, t_vector vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    return (vec1);

}

t_vector    vec_mult_(t_vector vec1, double t)
{
    vec1.x *= t;
    vec1.y *= t;
    vec1.z *= t;
    return (vec1);
}

t_vector    vec_div(t_vector vec1, t_vector vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    return (vec1);

}

t_vector    vec_div_(t_vector vec1, double t)
{
    vec1.x /= t;
    vec1.y /= t;
    vec1.z /= t;
    return (vec1);

}

t_vector    vec_unit(t_vector vec)
{
    double  len;
    
    len = vec_len(vec);
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

double      vec_len(t_vector vec)
{
    return (vec_dot(vec, vec));
}
