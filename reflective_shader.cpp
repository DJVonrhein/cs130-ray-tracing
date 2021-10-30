#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 c_o;   //object's color
    vec3 c_r;   //color that the reflected ray gets

    c_o = this->shader->Shade_Surface(ray, intersection_point, normal, recursion_depth); //color of object
    if (reflectivity <= small_t || recursion_depth >= world.recursion_depth_limit){
        return c_o * (1 - reflectivity);        //ambient of reflective object
    }

    //reflected ray (direction)  see https://www.cs.ucr.edu/~craigs/courses/2021-fall-cs-130/lectures/raytracing-falloff-reflection.pdf
    vec3 r = ((2 * dot(normal, ray.direction*-1) * normal) + ray.direction);    // r = 2 (i * n)n - i     where i = -(ray.direction)
    Ray reflecting_ray = Ray(intersection_point, r.normalized());       // the actual reflected ray

    c_r = world.Cast_Ray(reflecting_ray, recursion_depth + 1);     //casts reflection of the reflect ray

    // see https://www.cs.ucr.edu/~craigs/courses/2021-fall-cs-130/lectures/raytracing-shadow-reflect-transmit.pdf
    color = c_o + reflectivity * (c_r - c_o);       //color = c_o + Beta(c_r - c_o)

    return color;
}
