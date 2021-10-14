#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    // TODO;
    vec3 u = ray.direction;
    vec3 e_minus_c = ray.endpoint - center;
    double sqrt_part = sqrt(pow((dot(u, e_minus_c)),2) - (e_minus_c.magnitude_squared()- pow(radius, 2)));
    double t_plus,t_minus = -(dot(u, e_minus_c));

    t_plus += sqrt_part;
    t_minus -= sqrt_part;

    if(t_minus > small_t)
        return {this,t_minus,part};
    else if(t_plus > small_t)
        return {this,t_plus,part};
    return {0,0,0};
    
    


}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    // TODO; // compute the normal direction
    normal = (point - center )/ radius;


    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}

