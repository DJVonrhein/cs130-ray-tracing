#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    // TODO;
    double t1 = (-2 + sqrt(4-(4*dot(ray.endpoint - center, ray.endpoint - center))))/2;
    // double t2 = (-2 - sqrt(4-(4*dot(ray.endpoint - center, ray.endpoint - center))))/2;

    if(t1 < small_t)
        return {0,0,0};
    else
        return {this,t1,part};
    
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

